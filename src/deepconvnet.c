/*
 libdeep - a library for deep learning
 Copyright (C) 2015  Bob Mottram <bob@robotics.uk.to>

 A deep convolution network combines a convolutional net as a
 preprocessing stage together with a deep learning system as the
 final stage. The use of convolution greatly reduces the
 dimensionality of the problem for image processing, since the
 neural nets at each convolution layer only handle a small patch
 of the input surface.

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

#include "deepconvnet.h"

/**
* @brief Initialise a deep convnet
* @param no_of_convolutions Number of layers in the convolution
*        preprocessing stage
* @param no_of_deep_layers Number of layers in the deep learner
* @param inputs_across Horizontal resolution of input images
* @param inputs_down Vertical resolution of input images
* @param inputs_depth Depth of input images in bytes
* @param max_features The number of features learned at each convolution layer
* @param reduction_factor Reduction factor for convolution layers
* @param no_of_outputs Number of outputs of the deep learner
* @param convnet Deep convnet object
* @param error_threshold Array containing learning thresholds (percent error)
*        for each layer of both the convolution stage and the deep learner
* @param random_seed Random number generator seed
* @return zero on success
*/
int deepconvnet_init(int no_of_convolutions,
                     int no_of_deep_layers,
                     int inputs_across,
                     int inputs_down,
                     int inputs_depth,
                     int max_features,
                     int reduction_factor,
                     int no_of_outputs,
                     deepconvnet * convnet,
                     float error_threshold[],
                     unsigned int * random_seed)
{
    convnet->convolution = (deeplearn_conv*)malloc(sizeof(deeplearn_conv));
    if (!convnet->convolution) return -1;
    if (conv_init(no_of_convolutions,
                  inputs_across,
                  inputs_down,
                  inputs_depth,
                  max_features,
                  reduction_factor, 2,
                  convnet->convolution,
                  error_threshold,
                  random_seed) != 0) {
        return -2;
    }

    convnet->learner = (deeplearn*)malloc(sizeof(deeplearn));
    if (!convnet->learner) return -3;
    if (deeplearn_init(convnet->learner,
                       conv_outputs(convnet->convolution),
                       conv_outputs(convnet->convolution)*8/10,
                       no_of_deep_layers,
                       no_of_outputs,
                       &error_threshold[no_of_convolutions],
                       random_seed) != 0) {
        return -4;
    }

    return 0;
}

/**
* @brief Frees memory
* @param convnet Deep convnet object
*/
void deepconvnet_free(deepconvnet * convnet)
{
    conv_free(convnet->convolution);
    free(convnet->convolution);

    deeplearn_free(convnet->learner);
    free(convnet->learner);
}

/**
* @brief Saves the given deep convnet object to a file
* @param fp File pointer
* @param convnet Deep convnet object
* @return zero value on success
*/
int deepconvnet_save(FILE * fp, deepconvnet * convnet)
{
    if (conv_save(fp, convnet->convolution) != 0) return -1;
    if (deeplearn_save(fp, convnet->learner) != 0) return -2;
    return 0;
}

/**
* @brief Loads a deep convnet object from file
* @param fp File pointer
* @param convnet Deep convnet object
* @param random_seed Random number generator seed
* @return zero value on success
*/
int deepconvnet_load(FILE * fp, deepconvnet * convnet,
                     unsigned int * random_seed)
{
    if (conv_load(fp, convnet->convolution) != 0) return -1;
    if (deeplearn_load(fp, convnet->learner, random_seed) != 0) {
        return -2;
    }
    return 0;
}

/**
* @brief Sets the input values to the outputs of convolutional net.
*        This provides the glue sticking the preprocessing convolutional
*        stage together with the final deep learning stage.
* @param learner Deep learner object
* @param conv Convolution object
* @return zero on success
*/
static int deepconvnet_set_inputs_conv(deeplearn * learner, deeplearn_conv * conv)
{
    int layer_index = conv->no_of_layers-1;
    int width = conv_layer_width(layer_index, conv, 1);
    int height = conv_layer_height(layer_index, conv, 1);

    if (learner->net->NoOfInputs !=
        width * height * conv->max_features) {
        return -1;
    }
    for (int i = 0; i < learner->net->NoOfInputs; i++) {
        deeplearn_set_input(learner, i, conv->layer[layer_index].pooling[i]);
    }

    return 0;
}

/**
* @brief Update routine for training the system
* @param learner Deep learner object
* @param img Array containing input image
* @return Zero on success
*/
int deepconvnet_update_img(deepconvnet * convnet, unsigned char img[])
{
	if (conv_img(img, convnet->convolution) != 0) {
		return -1;
	}

	if (convnet->convolution->training_complete == 0) {
		return 0;
	}

	if (deepconvnet_set_inputs_conv(convnet->learner,
									convnet->convolution) != 0) {
		return -3;
	}

	deeplearn_update(convnet->learner);
	return 0;
}
