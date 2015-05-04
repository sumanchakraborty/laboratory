/*
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

#include "tests_preprocess.h"

static void test_preprocess_init()
{
    printf("test_preprocess_init...");

    unsigned int image_width = 512;
    unsigned int image_height = 512;
    unsigned int bitsperpixel = 24;
    int no_of_layers = 3;
    int max_features = 20;
    int reduction_factor = 4;
    int pooling_factor = 2;
    float error_threshold[] = {0.0, 0.0, 0.0};
    unsigned int random_seed = 648326;
    deeplearn_preprocess preprocess;

    assert(preprocess_init(no_of_layers,
                           image_width, image_height,
                           bitsperpixel/8, max_features,
                           reduction_factor, pooling_factor,
                           &preprocess, error_threshold,
                           &random_seed) == 0);
    preprocess_free(&preprocess);

    printf("Ok\n");
}

static void test_preprocess_image()
{
    printf("test_preprocess_image...");

    unsigned int image_width = 10;
    unsigned int image_height = 10;
    unsigned int bitsperpixel = 0;
    int no_of_layers = 3;
    int max_features = 20;
    int reduction_factor = 4;
    int pooling_factor = 2;
    float error_threshold[] = {0.0, 0.0, 0.0};
    unsigned int random_seed = 648326;
    unsigned char * img;
    deeplearn_preprocess preprocess;
    float BPerror = -1;

    /* load image from file */
    assert(deeplearn_read_png_file((char*)"Lenna.png", &image_width, &image_height, &bitsperpixel, &img)==0);

    assert(preprocess_init(no_of_layers,
                           image_width, image_height,
                           bitsperpixel/8, max_features,
                           reduction_factor, pooling_factor,
                           &preprocess, error_threshold,
                           &random_seed) == 0);
    for (int i = 0; i < 3; i++) {
        assert(preprocess_image(img, &preprocess) == 0);
        /* error should be >= 0 */
        assert(preprocess.BPerror >= 0);
        /* error should be reducing */
        if (i > 0) {
            assert(preprocess.BPerror < BPerror);
        }
        BPerror = preprocess.BPerror;
    }
    preprocess_free(&preprocess);
    free(img);

    printf("Ok\n");
}

int run_tests_preprocess()
{
    printf("\nRunning preprocessing tests\n");

    test_preprocess_init();
    test_preprocess_image();

    printf("All preprocessing tests completed\n");
    return 1;
}
