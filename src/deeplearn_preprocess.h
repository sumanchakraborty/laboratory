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

#ifndef DEEPLEARN_PREPROCESS_H
#define DEEPLEARN_PREPROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>
#include "globals.h"
#include "deeplearn_random.h"
#include "backprop_neuron.h"
#include "encoding.h"
#include "backprop.h"
#include "deeplearn_features.h"
#include "deeplearn_pooling.h"

#define PREPROCESS_MAX_LAYERS 100

typedef struct {
    bp * autocoder;
    int units_across, units_down;
    float * convolution;
    int pooling_factor;
    float * pooling;
} deeplearn_preprocess_layer;

typedef struct {
	int reduction_factor, pooling_factor;
    unsigned int random_seed;
    int inputs_across, inputs_down;
    int inputs_depth;
    int max_features;
    int no_of_layers;
    unsigned char enable_learning;
    unsigned char enable_convolution;
    deeplearn_preprocess_layer layer[PREPROCESS_MAX_LAYERS];

    /* keep track of training progress */
    int current_layer;
    float error_threshold[PREPROCESS_MAX_LAYERS];
    unsigned char training_complete;
    unsigned int itterations;
    float BPerror;

    /* training history */
    unsigned int training_ctr;
    unsigned int history_plot_interval;
    char history_plot_filename[256];
    char history_plot_title[256];

    float history[DEEPLEARN_HISTORY_SIZE];
    int history_index, history_ctr, history_step;
} deeplearn_preprocess;

int preprocess_patch_radius(int layer_index,
                            deeplearn_preprocess * preprocess);
int preprocess_layer_width(int layer_index,
                           deeplearn_preprocess * preprocess,
                           int after_pooling);
int preprocess_layer_height(int layer_index,
                            deeplearn_preprocess * preprocess,
                            int after_pooling);
int convolution_layer_units(int layer_index,
                            deeplearn_preprocess * preprocess);
int preprocess_init(int no_of_layers,
                    int inputs_across,
                    int inputs_down,
                    int inputs_depth,
                    int max_features,
                    int reduction_factor,
                    int pooling_factor,
                    deeplearn_preprocess * preprocess,
                    float error_threshold[],
                    unsigned int * random_seed);

void preprocess_free(deeplearn_preprocess * preprocess);
int preprocess_image(unsigned char img[],
                     deeplearn_preprocess * preprocess);
int preprocess_plot_history(deeplearn_preprocess * preprocess,
                            char * filename, char * title,
                            int image_width, int image_height);
int preprocess_save(FILE * fp, deeplearn_preprocess * preprocess);
int preprocess_load(FILE * fp, deeplearn_preprocess * preprocess);

#endif
