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

#ifndef DEEPLEARN_IMAGES_H
#define DEEPLEARN_IMAGES_H

#define _SVID_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>


#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#include "lodepng.h"
#include "backprop.h"

int deeplearn_read_png_file(char * filename,
                            unsigned int * width,
                            unsigned int * height,
                            unsigned int * bitsperpixel,
                            unsigned char ** buffer);
int deeplearn_write_png_file(char * filename,
                             unsigned int width, unsigned int height,
                             unsigned int bitsperpixel,
                             unsigned char buffer[]);
int deeplearn_load_training_images(char * images_directory,
                                   unsigned char *** images,
                                   char *** classifications,
                                   int ** classification_number,
                                   int width, int height);
void bp_plot_images(unsigned char **images,
                    int no_of_images,
                    int image_width, int image_height,
                    char * filename);
void deeplearn_downsample(unsigned char img[],
                          int width, int height,
                          unsigned char downsampled[],
                          int downsampled_width,
                          int downsampled_height);

#endif
