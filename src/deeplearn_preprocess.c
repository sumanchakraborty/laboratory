/*
  libdeep - a library for deep learning
  Copyright (C) 2015  Bob Mottram <bob@robotics.uk.to>

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  3. Neither the name of the University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
  .
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE HOLDERS OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "deeplearn_preprocess.h"

/**
 * @brief Initialise a preprocessing system
 * @param no_of_layers The number of convolutional layers
 * @param inputs_across Number of units across in the input layer or image
 * @param inputs_down The number of units down in the input layer or image
 * @param inputs_depth The depth of the input layer or image
 * @param max_features The maximum number of features per layer
 * @param reduction_factor Reduction factor for successive convolution layers
 * @param pooling_factor The reduction factor used for pooling
 * @param preprocess Preprocessing object
 * @returns zero on success
 */
int preprocess_init(int no_of_layers,
                    int inputs_across,
                    int inputs_down,
                    int inputs_depth,
                    int max_features,
                    int reduction_factor,
                    int pooling_factor,
                    deeplearn_preprocess * preprocess)
{
    int across = inputs_across;
    int down = inputs_down;

    preprocess->enable_learning = 0;
    preprocess->no_of_layers = no_of_layers;
    preprocess->inputs_across = inputs_across;
    preprocess->inputs_down = inputs_down;
    preprocess->inputs_depth = inputs_depth;
    preprocess->max_features = max_features;
    preprocess->layer =
        (deeplearn_preprocess_layer*)
        malloc(sizeof(deeplearn_preprocess_layer));
    if (!preprocess->layer) return -1;

    for (int i = 0; i < no_of_layers; i++) {
        across /= reduction_factor;
        down /= reduction_factor;
        preprocess->layer[i].units_across = across;
        preprocess->layer[i].units_down = down;
        preprocess->layer[i].pooling_factor = pooling_factor;
        preprocess->layer[i].convolution =
            (float*)malloc(sizeof(float)*across*down*max_features);
        if (!preprocess->layer[i].convolution) return -2;

        across /= pooling_factor;
        down /= pooling_factor;
        preprocess->layer[i].pooling =
            (float*)malloc(sizeof(float)*across*down*
                           max_features);
        if (!preprocess->layer[i].pooling) return -3;

        preprocess->layer[i].autocoder = (bp*)malloc(sizeof(bp));
        if (!preprocess->layer[i].autocoder) return -4;
    }
    return 0;
}

/**
 * @brief Frees memory for a preprocessing pipeline
 * @param preprocess Preprocessing object
 */
void preprocess_free(deeplearn_preprocess * preprocess)
{
    for (int i = 0; i < preprocess->no_of_layers; i++) {
        free(preprocess->layer[i].convolution);
        free(preprocess->layer[i].pooling);
        free(preprocess->layer[i].autocoder);
    }
    free(preprocess->layer);
}

/**
 * @brief Performs preprocessing on an image as a series of
 *        convolutions and poolings
 * @param image_width
 * @param image_height
 * @param image_depth
 * @param img Input image
 * @param preprocess Preprocessing object
 * @param BPerror Returned total backprop error from feature learning
 * @returns zero on success
 */
int preprocess_image(int image_width,
                     int image_height,
                     int image_depth,
                     unsigned char * img,
                     deeplearn_preprocess * preprocess,
                     float * BPerror)
{
    int retval = -1;
    int prev_pooling_factor, current_pooling_factor;
    int patch_radius;
    float currBPerror;

    *BPerror = 0;
    for (int i = 0; i < preprocess->no_of_layers; i++) {
        currBPerror = 0;
        if (i == 0) {
            patch_radius =
                image_width/preprocess->layer[i].units_across;

            if (preprocess->enable_learning != 0) {
                /* do feature learning */
                retval =
                    features_learn_from_image(preprocess->layer[i].units_across,
                                              preprocess->layer[i].units_down,
                                              patch_radius,
                                              image_width, image_height,
                                              image_depth, img,
                                              preprocess->layer[i].units_across*
                                              preprocess->layer[i].units_down,
                                              preprocess->layer[i].autocoder,
                                              &currBPerror);

                if (retval != 0) {
                    return -1;
                }
                *BPerror = *BPerror + currBPerror;
            }
                
            /* do the convolution for this layer */
            retval =
                features_convolve_image_to_floats(preprocess->layer[i].units_across,
                                                  preprocess->layer[i].units_down,
                                                  patch_radius,
                                                  image_width, image_height,
                                                  image_depth, img,
                                                  preprocess->layer[i].units_across*
                                                  preprocess->layer[i].units_down,
                                                  preprocess->layer[i].convolution,
                                                  preprocess->layer[i].autocoder);
            if (retval != 0) {
                return -2;
            }
        }
        else {
            prev_pooling_factor = preprocess->layer[i-1].pooling_factor;

            patch_radius =
                (preprocess->layer[i-1].units_across/prev_pooling_factor)/
                preprocess->layer[i].units_across;
                
            if (preprocess->enable_learning != 0) {
                /* do feature learning */
                retval =
                    features_learn_from_floats(preprocess->layer[i].units_across,
                                               preprocess->layer[i].units_down,
                                               patch_radius,
                                               preprocess->layer[i-1].units_across/prev_pooling_factor,
                                               preprocess->layer[i-1].units_down/prev_pooling_factor,
                                               preprocess->max_features,
                                               preprocess->layer[i-1].pooling,
                                               preprocess->layer[i].units_across*
                                               preprocess->layer[i].units_down,
                                               preprocess->layer[i].autocoder,
                                               &currBPerror);

                if (retval != 0) {
                    return -3;
                }
                *BPerror = *BPerror + currBPerror;
            }
            /* do the convolution for this layer */
            retval =
                features_convolve_floats_to_floats(preprocess->layer[i].units_across,
                                                   preprocess->layer[i].units_down,
                                                   patch_radius,
                                                   preprocess->layer[i-1].units_across/prev_pooling_factor,
                                                   preprocess->layer[i-1].units_down/prev_pooling_factor,
                                                   preprocess->max_features,
                                                   preprocess->layer[i-1].pooling,
                                                   preprocess->layer[i].units_across*
                                                   preprocess->layer[i].units_down,
                                                   preprocess->layer[i].convolution,
                                                   preprocess->layer[i].autocoder);
            if (retval != 0) {
                return -4;
            }
        }

        /* pooling */
        current_pooling_factor = preprocess->layer[i].pooling_factor;
        retval =
            pooling_from_floats_to_floats(preprocess->max_features,
                                          preprocess->layer[i].units_across,
                                          preprocess->layer[i].units_down,
                                          preprocess->layer[i].convolution,
                                          preprocess->layer[i].units_across/current_pooling_factor,
                                          preprocess->layer[i].units_down/current_pooling_factor,
                                          preprocess->layer[i].pooling);
        
    }
    return 0;
}
