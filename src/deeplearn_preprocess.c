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
 * @param random_seed Random number generator seed
 * @returns zero on success
 */
int preprocess_init(int no_of_layers,
                    int inputs_across,
                    int inputs_down,
                    int inputs_depth,
                    int max_features,
                    int reduction_factor,
                    int pooling_factor,
                    deeplearn_preprocess * preprocess,
                    float error_threshold[],
                    unsigned int * random_seed)
{
    int across = inputs_across;
    int down = inputs_down;

    rand_num(random_seed);
    preprocess->random_seed = *random_seed;

    preprocess->current_layer = 0;
    preprocess->training_complete = 0;
    preprocess->itterations = 0;
    preprocess->error_threshold =
        (float*)malloc(no_of_layers*sizeof(float));
    preprocess->BPerror = -1;
    memcpy((void*)preprocess->error_threshold,
           error_threshold, no_of_layers*sizeof(float));
    preprocess->enable_learning = 0;
    preprocess->enable_convolution = 1;
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

        preprocess->layer[i].autocoder = (bp*)malloc(sizeof(bp));
        if (!preprocess->layer[i].autocoder) return -3;

        int patch_pixels =
            preprocess_patch_radius(i,preprocess)*
            preprocess_patch_radius(i,preprocess)*4;

        /* ensure that the random seed is different for each
           convolutional neural net */
        rand_num(random_seed);

        if (i == 0) {
            bp_init(preprocess->layer[i].autocoder,
                    patch_pixels*inputs_depth, max_features, 1,
                    patch_pixels*inputs_depth,
                    random_seed);
        }
        else {
            bp_init(preprocess->layer[i].autocoder,
                    patch_pixels*max_features, max_features, 1,
                    patch_pixels*max_features,
                    random_seed);
        }

        across /= pooling_factor;
        down /= pooling_factor;
        preprocess->layer[i].pooling =
            (float*)malloc(sizeof(float)*across*down*
                           max_features);
        if (!preprocess->layer[i].pooling) return -4;
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
    free(preprocess->error_threshold);
}

/**
 * @brief Returns the input layer patch radius for the given layer number
 * @param layer_index Index number of the convolution layer
 * @param preprocess Preprocessing object
 * @return Patch radius
 */
int preprocess_patch_radius(int layer_index,
                            deeplearn_preprocess * preprocess)
{
    if (layer_index == 0) {
        return preprocess->inputs_across/preprocess->layer[0].units_across;
    }

    int prev_pooling_factor = preprocess->layer[layer_index-1].pooling_factor;
    return (preprocess->layer[layer_index-1].units_across/prev_pooling_factor) /
        preprocess->layer[layer_index].units_across;
}

/**
 * @brief Returns the width of the layer
 * @param layer_index Index number of the convolution layer
 * @param preprocess Preprocessing object
 * @param after_pooling Whether to return the value before or after pooling
 * @return Layer width
 */
int preprocess_layer_width(int layer_index,
                           deeplearn_preprocess * preprocess,
                           int after_pooling)
{
    if (after_pooling == 0) {
        return preprocess->layer[layer_index].units_across;
    }

    return preprocess->layer[layer_index].units_across /
        preprocess->layer[layer_index].pooling_factor;
}

/**
 * @brief Returns the height of the layer
 * @param layer_index Index number of the convolution layer
 * @param preprocess Preprocessing object
 * @param after_pooling Whether to return the value before or after pooling
 * @return Layer height
 */
int preprocess_layer_height(int layer_index,
                            deeplearn_preprocess * preprocess,
                            int after_pooling)
{
    if (after_pooling == 0) {
        return preprocess->layer[layer_index].units_down;
    }
    return preprocess->layer[layer_index].units_down /
        preprocess->layer[layer_index].pooling_factor;
}

/**
 * @brief Returns the number of units in a convolution layer
 * @param layer_index Index number of the convolution layer
 * @param preprocess Preprocessing object
 * @return Number of units in the convolution layer
 */
int convolution_layer_units(int layer_index,
                            deeplearn_preprocess * preprocess)
{
    return preprocess->layer[layer_index].units_across*
        preprocess->layer[layer_index].units_down*
        preprocess->max_features;
}

/**
* @brief Convolution between the input image and the first layer
* @param img Input image
* @param preprocess Preprocessing object
* @param BPerror Returned total backprop error from feature learning
* @return zero on success
*/
static int preprocess_image_initial(unsigned char img[],
                                    deeplearn_preprocess * preprocess,
                                    float * BPerror)
{
    float currBPerror=0;
    int retval;
    int patch_radius = preprocess_patch_radius(0, preprocess);

    if (preprocess->enable_learning != 0) {
        /* do feature learning */
        retval =
            features_learn_from_image(preprocess_layer_width(0,preprocess,0),
                                      preprocess_layer_height(0,preprocess,0),
                                      patch_radius,
                                      preprocess->inputs_across,
                                      preprocess->inputs_down,
                                      preprocess->inputs_depth, img,
                                      convolution_layer_units(0,preprocess),
                                      preprocess->layer[0].autocoder,
                                      &currBPerror);

        if (retval != 0) {
            return -1;
        }
        *BPerror = *BPerror + currBPerror;
    }

    if (preprocess->enable_convolution != 0) {
        /* do the convolution for this layer */
        retval =
            features_convolve_image_to_floats(preprocess_layer_width(0,preprocess,0),
                                              preprocess_layer_height(0,preprocess,0),
                                              patch_radius,
                                              preprocess->inputs_across,
                                              preprocess->inputs_down,
                                              preprocess->inputs_depth, img,
                                              convolution_layer_units(0,preprocess),
                                              preprocess->layer[0].convolution,
                                              preprocess->layer[0].autocoder);
        if (retval != 0) {
            return -2;
        }
    }
    return 0;
}

/**
* @brief Convolution between the input image and the first layer
* @param preprocess Preprocessing object
* @param layer_index Index of the convolution layer
* @param BPerror Returned total backprop error from feature learning
* @return zero on success
*/
static int preprocess_subsequent(deeplearn_preprocess * preprocess,
                                 int layer_index,
                                 float * BPerror)
{
    float currBPerror=0;
    int retval;
    int patch_radius = preprocess_patch_radius(layer_index, preprocess);

    if (layer_index < 1) {
        return -3;
    }

    if (preprocess->enable_learning != 0) {
        /* do feature learning */
        retval =
            features_learn_from_floats(preprocess_layer_width(layer_index,preprocess,0),
                                       preprocess_layer_height(layer_index,preprocess,0),
                                       patch_radius,
                                       preprocess_layer_width(layer_index-1,preprocess,1),
                                       preprocess_layer_height(layer_index-1,preprocess,1),
                                       preprocess->max_features,
                                       preprocess->layer[layer_index-1].pooling,
                                       convolution_layer_units(layer_index,preprocess),
                                       preprocess->layer[layer_index].autocoder,
                                       &currBPerror);

        if (retval != 0) {
            return -4;
        }
        *BPerror = *BPerror + currBPerror;
    }

    if (preprocess->enable_convolution != 0) {
        /* do the convolution for this layer */
        retval =
            features_convolve_floats_to_floats(preprocess_layer_width(layer_index,preprocess,0),
                                               preprocess_layer_height(layer_index,preprocess,0),
                                               patch_radius,
                                               preprocess_layer_width(layer_index-1,preprocess,1),
                                               preprocess_layer_height(layer_index-1,preprocess,1),
                                               preprocess->max_features,
                                               preprocess->layer[layer_index-1].pooling,
                                               convolution_layer_units(layer_index,preprocess),
                                               preprocess->layer[layer_index].convolution,
                                               preprocess->layer[layer_index].autocoder);
        if (retval != 0) {
            return -5;
        }
    }
    return 0;
}

/**
* @brief Returns the current layer being trained
* @param preprocess Preprocessing object
* @return Current maximum layer
*/
static int get_max_layer(deeplearn_preprocess * preprocess)
{
    if (preprocess->training_complete == 0) {
        return preprocess->current_layer+1;
    }
    return preprocess->no_of_layers;
}

/**
* @brief Enable or disable learning depending upon the given layer
*        and training state
* @param layer_index Index number of the convolution layer
* @param preprocess Preprocessing object
*/
static void preprocess_enable_learning(int layer_index,
                                       deeplearn_preprocess * preprocess)
{
    int max_layer = get_max_layer(preprocess);

    if (preprocess->training_complete == 0) {
        /* enable learning on the current layer only */
        preprocess->enable_learning = 0;
        preprocess->enable_convolution = 0;
        if (layer_index == max_layer-1) {
            preprocess->enable_learning = 1;
        }
        else {
            preprocess->enable_convolution = 1;
        }
    }
    else {
        preprocess->enable_convolution = 1;
        /* NOTE: there could be some residual learning probability
           for use with online systems */
        preprocess->enable_learning = 0;
    }
}

/**
* @brief Updates the current training error and moves to the next
*        convolution layer if the error is low enough
* @param layer_index The given layer index
* @param BPerror Backpropogation error for this layer
* @param preprocess Preprocessing object
*/
void preprocess_update_training_error(int layer_index,
                                      float BPerror,
                                      deeplearn_preprocess * preprocess)
{
    if (preprocess->training_complete != 0) {
        return;
    }

    int max_layer = get_max_layer(preprocess);
    if (layer_index < max_layer-1) {
        return;
    }

    if (preprocess->BPerror < 0) {
        preprocess->BPerror = BPerror;
        return;
    }

    /* update training error as a running average */
    preprocess->BPerror =
        (preprocess->BPerror*0.99f) + (BPerror*0.01f);

    /* has the training for this layer been completed? */
    if (preprocess->BPerror <
        preprocess->error_threshold[layer_index]) {

        /* reset the error and move to the next layer */
        preprocess->BPerror = -1;
        preprocess->current_layer++;

        /* if this is the final layer */
        if (preprocess->current_layer >=
            preprocess->no_of_layers) {
            preprocess->training_complete = 1;
        }
    }
}

/**
* @brief Performs preprocessing on an image as a series of
*        convolutions and poolings
* @param img Input image
* @param preprocess Preprocessing object
* @returns zero on success
*/
int preprocess_image(unsigned char img[],
                     deeplearn_preprocess * preprocess)
{
    int retval = -1;
    int max_layer = get_max_layer(preprocess);
    float BPerror;

    for (int i = 0; i < max_layer; i++) {
        preprocess_enable_learning(i, preprocess);

        BPerror = 0;
        if (i == 0) {
            retval = preprocess_image_initial(img, preprocess, &BPerror);
        }
        else {
            retval = preprocess_subsequent(preprocess, i, &BPerror);
        }
        if (retval != 0) {
            return retval;
        }
        preprocess_update_training_error(i, BPerror, preprocess);

        /* pooling */
        retval =
            pooling_from_floats_to_floats(preprocess->max_features,
                                          preprocess_layer_width(i,preprocess,0),
                                          preprocess_layer_height(i,preprocess,0),
                                          preprocess->layer[i].convolution,
                                          preprocess_layer_width(i,preprocess,1),
                                          preprocess_layer_height(i,preprocess,1),
                                          preprocess->layer[i].pooling);
        if (retval != 0) {
            return -6;
        }
    }
    return 0;
}
