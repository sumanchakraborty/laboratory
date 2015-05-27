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

#include "tests_autocoder.h"

static void test_autocoder_init()
{
    ac autocoder;
    int no_of_inputs = 32;
    int no_of_hiddens = 24;
    unsigned int random_seed = 5322;

    printf("test_autocoder_init...");

    assert(autocoder_init(&autocoder,
                          no_of_inputs,
                          no_of_hiddens,
                          random_seed) == 0);
    autocoder_free(&autocoder);

    printf("Ok\n");
}

static void test_autocoder_save_load()
{
    ac autocoder, autocoder_loaded;
    int no_of_inputs = 32;
    int no_of_hiddens = 24;
    unsigned int random_seed = 5322;
    unsigned int random_seed_loaded = 7269;
    FILE * fp;

    printf("test_autocoder_save_load...");

    assert(autocoder_init(&autocoder,
                          no_of_inputs,
                          no_of_hiddens,
                          random_seed) == 0);

    fp = fopen("/tmp/autocoder_test.dat","w");
    assert(fp);
    assert(autocoder_save(fp, &autocoder)==0);
    fclose(fp);

    assert(autocoder_init(&autocoder_loaded,
                          no_of_inputs,
                          no_of_hiddens,
                          random_seed_loaded) == 0);

    fp = fopen("/tmp/autocoder_test.dat","r");
    assert(fp);
    assert(autocoder_load(fp, &autocoder_loaded)==0);
    fclose(fp);

    for (int i = 0; i < no_of_inputs*no_of_hiddens; i++) {
        assert(autocoder.weights[i] ==
               autocoder_loaded.weights[i]);
    }
    for (int i = 0; i < no_of_hiddens; i++) {
        assert(autocoder.bias[i] ==
               autocoder_loaded.bias[i]);
    }

    autocoder_free(&autocoder);
    autocoder_free(&autocoder_loaded);

    printf("Ok\n");
}

int run_tests_autocoder()
{
    printf("\nRunning autocoder tests\n");

    test_autocoder_init();
    test_autocoder_save_load();

    printf("All autocoder tests completed\n");
    return 1;
}
