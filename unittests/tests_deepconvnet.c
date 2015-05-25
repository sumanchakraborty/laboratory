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

#include "tests_deepconvnet.h"

static void test_init()
{
	int no_of_convolutions = 2;
	int no_of_deep_layers = 2;
	int inputs_across = 320;
	int inputs_down = 240;
	int inputs_depth = 3;
	int max_features = 20;
	int reduction_factor = 2;
	int no_of_outputs = 10;
	deepconvnet convnet;
	float error_threshold[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	unsigned int random_seed = 7423;

	printf("test_init...");

	assert(deepconvnet_init(no_of_convolutions,
							no_of_deep_layers,
							inputs_across,
							inputs_down,
							inputs_depth,
							max_features,
							reduction_factor,
							no_of_outputs,
							&convnet,
							error_threshold,
							&random_seed) == 0);

	deepconvnet_free(&convnet);

    printf("Ok\n");
}

static void test_update_img()
{
	int no_of_convolutions = 2;
	int no_of_deep_layers = 2;
	int inputs_across = 320;
	int inputs_down = 240;
	int inputs_depth = 3;
	int max_features = 20;
	int reduction_factor = 2;
	int no_of_outputs = 10;
	deepconvnet convnet;
	float error_threshold[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	unsigned int random_seed = 7423;
	unsigned char * img =
		(unsigned char*)malloc(inputs_across*inputs_dowm*
							   inputs_depth*sizeof(unsigned char));

    printf("test_update_img...");

	assert(deepconvnet_init(no_of_convolutions,
							no_of_deep_layers,
							inputs_across,
							inputs_down,
							inputs_depth,
							max_features,
							reduction_factor,
							no_of_outputs,
							&convnet,
							error_threshold,
							&random_seed) == 0);

	/* after training */
	convnet.convolution->training_complete = 1;
	convnet.learner->training_complete = 1;
	convnet.training_complete = 1;

	/* set some input value */
    for (int i = 0; i < inputs_across*inputs_down*inputs_depth; i++) {
		img[i] = 127;
	}

	assert(deepconvnet_update_img(&convnet, img, 1)==0);

	deepconvnet_free(&convnet);
    free(img);

    printf("Ok\n");
}

int run_tests_deepconvnet()
{
    printf("\nRunning deepconvnet tests\n");

	test_init();
	test_update_img();

    printf("All deepconvnet tests completed\n");
    return 1;
}
