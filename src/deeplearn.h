/*
 libdeep - a library for deep learning
 Copyright (C) 2013-2015  Bob Mottram <bob@robotics.uk.to>

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

#ifndef DEEPLEARN_H
#define DEEPLEARN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "globals.h"
#include "backprop.h"
#include "autocoder.h"
#include "encoding.h"
#include "deeplearn_conv.h"

typedef struct {
    float * inputs;
    char ** inputs_text;
    float * outputs;
    unsigned int flags;
    unsigned int labeled;
    struct deeplearndata * prev;
    struct deeplearndata * next;
} deeplearndata;

typedef struct {
    deeplearndata * sample;
    struct deeplearndata_meta * prev;
    struct deeplearndata_meta * next;
} deeplearndata_meta;

struct deepl {
    bp * net;
    ac ** autocoder;
    int current_hidden_layer;
    float BPerror;
    unsigned int itterations;
    float * error_threshold;
    int training_complete;
    int no_of_input_fields;
    int * field_length;

    deeplearndata * data;
    int data_samples;
    deeplearndata_meta * training_data;
    int training_data_samples;
    deeplearndata_meta * training_data_labeled;
    int training_data_labeled_samples;
    deeplearndata_meta * test_data;
    int test_data_samples;

    float * input_range_min;
    float * input_range_max;
    float * output_range_min;
    float * output_range_max;

    unsigned int training_ctr;
    unsigned int history_plot_interval;
    char history_plot_filename[256];
    char history_plot_title[256];

    float history[DEEPLEARN_HISTORY_SIZE];
    int history_index, history_ctr, history_step;
};
typedef struct deepl deeplearn;

int deeplearn_init(deeplearn * learner,
                   int no_of_inputs,
                   int no_of_hiddens,
                   int hidden_layers,
                   int no_of_outputs,
                   float error_threshold[],
                   unsigned int * random_seed);
void deeplearn_feed_forward(deeplearn * learner);
void deeplearn_update(deeplearn * learner);
void deeplearn_free(deeplearn * learner);
void deeplearn_set_input_text(deeplearn * learner, char * text);
void deeplearn_set_input(deeplearn * learner, int index, float value);
int deeplearn_set_input_field(deeplearn * learner, int fieldindex, float value);
int deeplearn_set_input_field_text(deeplearn * learner, int fieldindex, char * text);
void deeplearn_set_inputs(deeplearn * learner, deeplearndata * sample);
void deeplearn_set_output(deeplearn * learner, int index, float value);
void deeplearn_set_outputs(deeplearn * learner, deeplearndata * sample);
void deeplearn_get_outputs(deeplearn * learner, float * outputs);
float deeplearn_get_output(deeplearn * learner, int index);
int deeplearn_get_class(deeplearn * learner);
void deeplearn_set_class(deeplearn * learner, int class);
int deeplearn_save(FILE * fp, deeplearn * learner);
int deeplearn_load(FILE * fp, deeplearn * learner,
                   unsigned int * random_seed);
int deeplearn_compare(deeplearn * learner1,
                      deeplearn * learner2);
int deeplearn_plot_history(deeplearn * learner,
                           char * filename, char * title,
                           int image_width, int image_height);
void deeplearn_inputs_from_image_patch(deeplearn * learner,
                                       unsigned char * img,
                                       int image_width, int image_height,
                                       int tx, int ty);
void deeplearn_inputs_from_image(deeplearn * learner,
                                 unsigned char * img,
                                 int image_width, int image_height);
void deeplearn_set_learning_rate(deeplearn * learner, float rate);
void deeplearn_set_dropouts(deeplearn * learner, float dropout_percent);
int deeplearn_export(deeplearn * learner, char * filename);
float deeplearn_get_error_threshold(deeplearn * learner, int index);
void deeplearn_set_error_threshold(deeplearn * learner, int index, float value);
void deeplearn_update_continuous(deeplearn * learner);
int deeplearn_training_last_layer(deeplearn * learner);
void copy_autocoder_to_hidden_layer(deeplearn * learner, int hidden_layer);
void deeplearn_pretrain(bp * net, ac * autocoder, int current_layer);

#endif
