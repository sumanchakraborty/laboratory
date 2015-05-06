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

#include "tests_features.h"

static void test_learn_from_image()
{
    printf("test_learn_from_image...");

    bp net;
    bp feature_autocoder;
    unsigned int image_width = 10;
    unsigned int image_height = 10;
    int image_depth = 24/8;
    int result,i = 0;
    unsigned int random_seed = 123;
    int no_of_hiddens = 4*4;
    int hidden_layers = 2;
    int no_of_outputs = 2*2;
    float error_value[10];
    unsigned int bitsperpixel = 0;
    unsigned char * img, * img2;
    float BPerror=0;

    /* load image from file */
    assert(deeplearn_read_png_file((char*)"Lenna.png", &image_width, &image_height, &bitsperpixel, &img)==0);

    assert(image_width == 512);
    assert(image_height == 512);
    assert(bitsperpixel == 24);

	img2 = (unsigned char*)malloc(128*128*3*sizeof(unsigned char));
	assert(img2);
	deeplearn_downsample(img, image_width, image_height,
						 img2, 128, 128);
	free(img);
	img = img2;
	image_width = 128;
	image_height = 128;

    int samples_across = image_width/20;
    int samples_down = image_height/20;
    int patch_radius = 4;
    int no_of_features = 6*6;
    int no_of_inputs = samples_across*samples_down*no_of_features;

    /* create a network */
    bp_init(&feature_autocoder,
            patch_radius*patch_radius*4*image_depth,
            no_of_features,1,
            patch_radius*patch_radius*4*image_depth,
            &random_seed);
    assert((&feature_autocoder)->inputs!=0);
    assert((&feature_autocoder)->hiddens!=0);
    assert((&feature_autocoder)->outputs!=0);

    for (i = 0; i < 4; i++) {
        result =
            features_learn_from_image(samples_across,
                                      samples_down,
                                      patch_radius,
                                      image_width,
                                      image_height,
                                      image_depth,
                                      img,
                                      no_of_inputs,
                                      &feature_autocoder,
                                      &BPerror);
        if (result != 0) {
            printf("\nresult = %d\n",result);
        }
        assert(result==0);
        error_value[i] = BPerror;
    }

    /* check that the training error reduced */
    assert(error_value[3] < error_value[1]);

    /* create a network */
    bp_init(&net,
            no_of_inputs, no_of_hiddens,
            hidden_layers,
            no_of_outputs, &random_seed);
    assert((&net)->inputs!=0);
    assert((&net)->hiddens!=0);
    assert((&net)->outputs!=0);


    bp_plot_weights(&feature_autocoder,
                    "/tmp/test_features_learn_from_image.png",
                    480,800,8);

    /* free the memory */
    free(img);
    bp_free(&net);
    bp_free(&feature_autocoder);

    printf("Ok\n");
}

int run_tests_features()
{
    printf("\nRunning feature learning tests\n");

    test_learn_from_image();

    printf("All feature learning tests completed\n");
    return 1;
}
