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

#include "autocoder.h"

#define AUTOCODER_UNKNOWN      -9999
#define AUTOCODER_DROPPED_OUT  -9999

/**
* @brief Initialise an autocoder
* @param autocoder Autocoder object
* @param no_of_inputs The number of inputs
* @param no_of_hiddens The number of hidden (encoder) units
* @param random_seed Random number generator seed
* @return zero on success
*/
int autocoder_init(ac * autocoder,
                   int no_of_inputs,
                   int no_of_hiddens,
                   unsigned int random_seed)
{
    autocoder->NoOfInputs = no_of_inputs;
    autocoder->NoOfHiddens = no_of_hiddens;
    autocoder->inputs =
        (float*)malloc(no_of_inputs*sizeof(float));
    if (!autocoder->inputs) return -1;
    autocoder->hiddens =
        (float*)malloc(no_of_hiddens*sizeof(float));
    if (!autocoder->hiddens) return -2;
    autocoder->bias =
        (float*)malloc(no_of_hiddens*sizeof(float));
    if (!autocoder->bias) return -3;
    autocoder->weights =
        (float*)malloc(no_of_hiddens*no_of_inputs*sizeof(float));
    if (!autocoder->weights) return -4;
    autocoder->lastWeightChange =
        (float*)malloc(no_of_hiddens*no_of_inputs*sizeof(float));
    if (!autocoder->lastWeightChange) return -5;
    autocoder->outputs =
        (float*)malloc(no_of_inputs*sizeof(float));
    if (!autocoder->outputs) return -6;
    autocoder->bperr =
        (float*)malloc(no_of_hiddens*sizeof(float));
    if (!autocoder->bperr) return -7;
    memset((void*)autocoder->inputs,'\0',no_of_inputs*sizeof(float));
    memset((void*)autocoder->hiddens,'\0',
           no_of_hiddens*sizeof(float));
    memset((void*)autocoder->lastWeightChange,'\0',
           no_of_hiddens*no_of_inputs*sizeof(float));
    memset((void*)autocoder->bperr,'\0',
           autocoder->NoOfHiddens*sizeof(float));
    autocoder->lastBiasChange = 0;
    autocoder->BPerror = 0;
    autocoder->BPerrorAverage = AUTOCODER_UNKNOWN;
    autocoder->learningRate = 0.2f;
    autocoder->noise = 0;
    autocoder->random_seed = random_seed;
    autocoder->itterations = 0;
    autocoder->dropoutsPercent = 2;

    /* initial small random values */
    for (int h = 0; h < no_of_hiddens; h++) {
        autocoder->bias[h] =
            (0.2f*(rand_num(&autocoder->random_seed)%10000/10000.0))-0.1f;
        for (int i = 0; i < no_of_inputs; i++) {
            autocoder->weights[h*no_of_inputs + i] =
                (0.2f*(rand_num(&autocoder->random_seed)%10000/10000.0))-0.1f;
        }
    }
    return 0;
}

/**
* @brief frees memory for an autocoder
* @param autocoder Autocoder object
*/
void autocoder_free(ac * autocoder)
{
    free(autocoder->inputs);
    free(autocoder->outputs);
    free(autocoder->hiddens);
    free(autocoder->bias);
    free(autocoder->weights);
    free(autocoder->lastWeightChange);
    free(autocoder->bperr);
}

/**
* @brief Feed forward
* @param autocoder Autocoder object
*/
void autocoder_feed_forward(ac * autocoder)
{
    for (int h = 0; h < autocoder->NoOfHiddens; h++) {
        if (rand_num(&autocoder->random_seed)%10000 <
            autocoder->dropoutsPercent*100) {
            autocoder->hiddens[h] = AUTOCODER_DROPPED_OUT;
            continue;
        }

        /* weighted sum of inputs */
        float adder = autocoder->bias[h];
        for (int i = 0; i < autocoder->NoOfInputs; i++) {
            adder +=
                autocoder->weights[h*autocoder->NoOfInputs + i] *
                autocoder->inputs[i];
        }

        /* add some random noise */
        if (autocoder->noise > 0) {
            adder = ((1.0f - autocoder->noise) * adder) +
                (autocoder->noise * ((rand_num(&autocoder->random_seed)%10000)/10000.0f));
        }

        /* activation function */
        autocoder->hiddens[h] = 1.0f / (1.0f + exp(-adder));
    }

    for (int i = 0; i < autocoder->NoOfInputs; i++) {
        /* weighted sum of hidden inputs */
        float adder = 0;
        for (int h = 0; h < autocoder->NoOfHiddens; h++) {
            if (autocoder->hiddens[h] == AUTOCODER_DROPPED_OUT) continue;
            adder +=
                autocoder->weights[h*autocoder->NoOfInputs + i] *
                autocoder->hiddens[h];
        }

        /* add some random noise */
        if (autocoder->noise > 0) {
            adder = ((1.0f - autocoder->noise) * adder) +
                (autocoder->noise * ((rand_num(&autocoder->random_seed)%10000)/10000.0f));
        }

        /* activation function */
        autocoder->outputs[i] = 1.0f / (1.0f + exp(-adder));
    }
}

/**
* @brief Back propogate the error
* @param autocoder Autocoder object
*/
void autocoder_backprop(ac * autocoder)
{
    /* clear the backptop error for each hidden unit */
    memset((void*)autocoder->bperr,'\0',autocoder->NoOfHiddens*sizeof(float));

    /* backprop from outputs to hiddens */
    autocoder->BPerror = 0;
    float errorPercent = 0;
    for (int i = 0; i < autocoder->NoOfInputs; i++) {
        float BPerror = autocoder->inputs[i] - autocoder->outputs[i];
        autocoder->BPerror += BPerror;
        errorPercent += fabs(BPerror);
        float afact = autocoder->outputs[i] * (1.0f - autocoder->outputs[i]);
        for (int h = 0; h < autocoder->NoOfHiddens; h++) {
            autocoder->bperr[h] +=
                BPerror * afact * autocoder->weights[h*autocoder->NoOfInputs + i];
        }
    }

    /* error percentage assuming an encoding range
       of 0.25 -> 0.75 */
    errorPercent = errorPercent * 100 / (0.5f*autocoder->NoOfInputs);

    /* update the running average */
    if (autocoder->BPerrorAverage == AUTOCODER_UNKNOWN) {
        autocoder->BPerrorAverage = autocoder->BPerror;
        autocoder->BPerrorPercent = errorPercent;
    }
    else {
        autocoder->BPerrorAverage =
            (autocoder->BPerrorAverage*0.999f) +
            (autocoder->BPerror*0.001f);
        autocoder->BPerrorPercent =
            (autocoder->BPerrorPercent*0.999f) +
            (errorPercent*0.001f);
    }
}
