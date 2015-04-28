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

#ifndef DEEPLEARN_FEATURES_H
#define DEEPLEARN_FEATURES_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>
#include "globals.h"
#include "deeplearn_random.h"
#include "backprop_neuron.h"
#include "encoding.h"
#include "backprop.h"

/* learning of features */
int features_learn_from_image(int samples_across,
                              int samples_down,
                              int patch_radius,
                              int image_width,
                              int image_height,
                              int image_depth,
                              unsigned char * img,
                              int layer0_units,
                              bp * feature_autocoder,
                              float * BPerror);

int features_learn_from_floats(int samples_across,
                               int samples_down,
                               int patch_radius,
                               int inputs_width,
                               int inputs_height,
                               int inputs_depth,
                               float * img,
                               int layer0_units,
                               bp * feature_autocoder);

int features_convolve_image_to_neurons(int samples_across,
                                       int samples_down,
                                       int patch_radius,
                                       int image_width,
                                       int image_height,
                                       int image_depth,
                                       unsigned char * img,
                                       bp * net,
                                       bp * feature_autocoder);

int features_convolve_image_to_floats(int samples_across,
                                      int samples_down,
                                      int patch_radius,
                                      int image_width,
                                      int image_height,
                                      int image_depth,
                                      unsigned char * img,
                                      int layer0_units,
                                      float * layer0,
                                      bp * feature_autocoder);

int features_convolve_floats_to_floats(int samples_across,
                                       int samples_down,
                                       int patch_radius,
                                       int floats_width,
                                       int floats_height,
                                       int floats_depth,
                                       float * layer0,
                                       int layer1_units,
                                       float * layer1,
                                       bp * feature_autocoder);

int features_convolve_floats_to_neurons(int samples_across,
                                        int samples_down,
                                        int patch_radius,
                                        int floats_width,
                                        int floats_height,
                                        int floats_depth,
                                        float * layer0,
                                        bp * net,
                                        bp * feature_autocoder);

#endif
