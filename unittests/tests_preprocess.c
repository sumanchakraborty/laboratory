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
    int reduction_factor = 6;
    int pooling_factor = 2;
    float error_threshold[] = {0.0, 0.0, 0.0};
    unsigned int random_seed = 648326;
    unsigned char * img, * img2;
    deeplearn_preprocess preprocess;
    float BPerror = -1;
    char plot_filename[256];
    char plot_title[256];

    /* load image from file */
    assert(deeplearn_read_png_file((char*)"Lenna.png", &image_width, &image_height, &bitsperpixel, &img)==0);

	img2 = (unsigned char*)malloc(128*128*3*sizeof(unsigned char));
	assert(img2);
	deeplearn_downsample(img, image_width, image_height,
						 img2, 128, 128);
	free(img);
	img = img2;
	image_width = 128;
	image_height = 128;

    assert(preprocess_init(no_of_layers,
                           image_width, image_height,
                           bitsperpixel/8, max_features,
                           reduction_factor, pooling_factor,
                           &preprocess, error_threshold,
                           &random_seed) == 0);
    for (int i = 0; i < 4; i++) {
        assert(preprocess_image(img, &preprocess) == 0);
        /* error should be >= 0 */
        assert(preprocess.BPerror >= 0);
        /* error should be reducing */
        if (i > 0) {
            assert(preprocess.BPerror < BPerror);
        }
        BPerror = preprocess.BPerror;
    }

    sprintf(plot_filename,"/tmp/%s","libdeep_conv.png");
    sprintf(plot_title,"%s","Convolution Training Error");

    assert(preprocess_plot_history(&preprocess, plot_filename,
                                   plot_title,
                                   1024, 640) == 0);
    preprocess_free(&preprocess);
    free(img);

    printf("Ok\n");
}

static void test_preprocess_save_load()
{
    printf("test_preprocess_save_load...");

    unsigned int image_width = 512;
    unsigned int image_height = 512;
    unsigned int bitsperpixel = 24;
    int i, no_of_layers = 3;
    int max_features = 20;
    int reduction_factor = 4;
    int pooling_factor = 2;
    float error_threshold[] = {0.1, 0.2, 0.3};
    float error_threshold2[] = {0.6, 0.7, 0.8};
    unsigned int random_seed = 648326;
    deeplearn_preprocess preprocess1;
    deeplearn_preprocess preprocess2;
    FILE * fp;
    char filename[256];

    assert(preprocess_init(no_of_layers,
                           image_width, image_height,
                           bitsperpixel/8, max_features,
                           reduction_factor, pooling_factor,
                           &preprocess1, error_threshold,
                           &random_seed) == 0);

    sprintf(filename, "/tmp/%s", "libdeep_conv.dat");

    /* save */
    fp = fopen(filename,"w");
    assert(fp);
    assert(preprocess_save(fp, &preprocess1) == 0);
    fclose(fp);

    /* set some different values */
    preprocess2.reduction_factor = 45;
    preprocess2.pooling_factor = 8;
    preprocess2.inputs_across = 100;
    preprocess2.inputs_down = 200;
    preprocess2.inputs_depth = 16;
    preprocess2.no_of_layers = 2;
    preprocess2.max_features = 15;
    preprocess2.error_threshold = error_threshold2;
    preprocess2.random_seed = 20313;
    preprocess2.enable_learning = 0;
    preprocess2.enable_convolution = 0;
    preprocess2.current_layer = 4577;
    preprocess2.training_complete = 3;
    preprocess2.itterations = 642;

    /* load */
    fp = fopen(filename,"r");
    assert(fp);
    assert(preprocess_load(fp, &preprocess2) == 0);
    fclose(fp);

    /* compare the results */
    assert(preprocess1.reduction_factor == preprocess2.reduction_factor);
    assert(preprocess1.pooling_factor == preprocess2.pooling_factor);
    assert(preprocess1.random_seed != preprocess2.random_seed);
    assert(preprocess1.inputs_across == preprocess2.inputs_across);
    assert(preprocess1.inputs_down == preprocess2.inputs_down);
    assert(preprocess1.inputs_depth == preprocess2.inputs_depth);
    assert(preprocess1.max_features == preprocess2.max_features);
    assert(preprocess1.no_of_layers == preprocess2.no_of_layers);
    assert(preprocess1.enable_learning == preprocess2.enable_learning);
    assert(preprocess1.enable_convolution == preprocess2.enable_convolution);
    assert(preprocess1.current_layer == preprocess2.current_layer);
    assert(preprocess1.training_complete == preprocess2.training_complete);
    assert(preprocess1.itterations == preprocess2.itterations);
    for (i = 0; i < preprocess1.no_of_layers; i++) {
        assert(preprocess1.error_threshold[i] == preprocess2.error_threshold[i]);
        assert(bp_compare(&preprocess1.layer[i].autocoder,
                          &preprocess2.layer[i].autocoder) == 1);
        assert(preprocess1.layer[i].units_across == preprocess2.layer[i].units_across);
        assert(preprocess1.layer[i].units_down == preprocess2.layer[i].units_down);
        assert(preprocess1.layer[i].pooling_factor == preprocess2.layer[i].pooling_factor);
    }

    preprocess_free(&preprocess1);
    preprocess_free(&preprocess2);

    printf("Ok\n");
}

int run_tests_preprocess()
{
    printf("\nRunning preprocessing tests\n");

    test_preprocess_init();
    test_preprocess_image();
    test_preprocess_save_load();

    printf("All preprocessing tests completed\n");
    return 1;
}
