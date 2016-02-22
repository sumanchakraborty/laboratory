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

#include "backprop_neuron.h"

/**
* @brief Randomly initialises the weights within the given range
* @param n Backprop neuron object
* @param minVal The minimum weight value
* @param maxVal The maximum weight value
* @param random_seed Random number generator seed
*/
static void bp_neuron_init_weights(bp_neuron * n,
                                   float minVal, float maxVal,
                                   unsigned int * random_seed)
{
    float min, max;
    int i;

    min = minVal;
    max = maxVal;

    n->min_weight = 9999;
    n->max_weight = -9999;

    /* do the weights */
    for (i = 0; i < n->NoOfInputs; i++) {
        n->weights[i] =
            min + (((rand_num(random_seed)%10000)/10000.0f) *
                   (max - min));
        n->lastWeightChange[i] = 0;
        if (n->weights[i] < n->min_weight) {
            n->min_weight = n->weights[i];
        }
        if (n->weights[i] > n->max_weight) {
            n->max_weight = n->weights[i];
        }
    }

    /* dont forget the bias value */
    n->bias =
        min + (((rand_num(random_seed)%10000)/10000.0f) *
               (max - min));
    n->lastBiasChange = 0;
}

/**
* @brief Copy weights from one neuron to another
* @param source The neuron to copy from
* @param dest The neuron to copy to
*/
void bp_neuron_copy(bp_neuron * source,
                    bp_neuron * dest)
{
    /* check that the source and destination have the same
        number of inputs */
    if (source->NoOfInputs !=
        dest->NoOfInputs) {
        printf("Warning: neurons have different numbers of inputs\n");
        return;
    }

    /* copy the connection weights */
    memcpy(dest->weights,source->weights,source->NoOfInputs*sizeof(float));

    /* copy the bias */
    dest->bias = source->bias;

    /* copy the weight range */
    dest->min_weight = source->min_weight;
    dest->max_weight = source->max_weight;

    /* clear the previous weight changes */
    memset(dest->lastWeightChange,'\0',dest->NoOfInputs*sizeof(float));
}

/**
* @brief Initialises the neuron
* @param n Backprop neuron object
* @param no_of_inputs The number of input connections
* @param random_seed Random number generator seed
*/
int bp_neuron_init(bp_neuron * n,
                   int no_of_inputs,
                   unsigned int * random_seed)
{
    /* should have more than zero inpyts */
    assert(no_of_inputs > 0);

    n->NoOfInputs = no_of_inputs;

    /* create some weights */
    n->weights = (float*)malloc(no_of_inputs*sizeof(float));
    if (!n->weights) {
        return -1;
    }
    n->lastWeightChange = (float*)malloc(no_of_inputs*sizeof(float));
    if (!n->lastWeightChange) {
        return -2;
    }

    bp_neuron_init_weights(n, -0.1f, 0.1f, random_seed);
    n->desiredValue = -1;
    n->value = 0;
    n->value_reprojected = 0;
    n->BPerror = 0;
    n->excluded = 0;

    /* pointers to input neurons */
    n->inputs = (struct bp_n **)malloc(no_of_inputs*
                                       sizeof(struct bp_n *));
    if (!n->inputs) {
        return -3;
    }
    memset(n->inputs,'\0',no_of_inputs*sizeof(struct bp_n *));
    return 0;
}

/**
* @brief Compares two neurons and returns a non-zero value
*        if they are the same
* @param n1 First backprop neuron object
* @param n2 Second backprop neuron object
* @return 1 if they are the same, 0 otherwise
*/
int bp_neuron_compare(bp_neuron * n1, bp_neuron * n2)
{
    int i;

    if ((n1->NoOfInputs != n2->NoOfInputs) ||
        (n1->bias != n2->bias)) {
        return 0;
    }

    for (i = 0; i < n1->NoOfInputs; i++) {
        if ((n1->weights[i] != n2->weights[i]) ||
            (n1->lastWeightChange[i] != n2->lastWeightChange[i])) {
            return 0;
        }
    }
    return 1;
}

/**
* @brief Deallocates memory for a neuron
* @param n Backprop neuron object
*/
void bp_neuron_free(bp_neuron * n)
{
    int i;

    /* free the weights */
    free(n->weights);
    free(n->lastWeightChange);

    /* clear the pointers to input neurons */
    for (i = 0; i < n->NoOfInputs; i++) {
        n->inputs[i]=0;
    }

    /* free the inputs */
    free(n->inputs);
}

/**
* @brief Activation function
* @param x The weighted sum of inputs
* @return Result of the activation function
*/
static float af(float x)
{
    return x * (1.0f - x);
}


/**
* @brief Adds a connection to a neuron
* @param dest Destination backprop neuron object
* @param index Index number of the input connection
* @param source Incoming backprop neuron object
*/
void bp_neuron_add_connection(bp_neuron * dest,
                              int index, bp_neuron * source)
{
    dest->inputs[index] = source;
}

/**
* @brief Feed forward
* @param n Backprop neuron object
* @param noise Noise in the range 0.0 to 1.0
* @param random_seed Random number generator seed
*/
void bp_neuron_feedForward(bp_neuron * n,
                           float noise,
                           unsigned int * random_seed)
{
    float adder;
    int i;

    /* if the neuron has dropped out then set its output to zero */
    if (n->excluded > 0) {
        n->value = 0;
        return;
    }

    /* Sum with initial bias */
    adder = n->bias;

    /* calculate weighted sum of inputs */
    for (i = 0; i < n->NoOfInputs; i++) {
        if (n->inputs[i] != 0) {
            adder += n->weights[i] * n->inputs[i]->value;
        }
    }

    /* add some random noise */
    if (noise > 0) {
        adder = ((1.0f - noise) * adder) +
            (noise * ((rand_num(random_seed)%10000)/10000.0f));
    }

    /* activation function */
    n->value = 1.0f / (1.0f + exp(-adder));
}

/**
* @brief back-propagate the error
* @param n Backprop neuron object
*/
void bp_neuron_backprop(bp_neuron * n)
{
    int i;
    bp_neuron * nrn;
    float afact;

    /* if the neuron has dropped out then don't continue */
    if (n->excluded > 0) return;

    if (n->desiredValue > -1) {
        /* output unit */
        n->BPerror = n->desiredValue - n->value;
    }

    /* activation function */
    afact = af(n->value);

    /* back-propogate the error */
    for (i = 0; i < n->NoOfInputs; i++) {
        nrn = n->inputs[i];
        if (nrn != 0) {
            nrn->BPerror +=
                (n->BPerror * afact * n->weights[i]);
        }
    }
}

/**
* @brief Reprojects a neuron value back into the previous layer
* @param n Backprop neuron object
*/
void bp_neuron_reproject(bp_neuron * n)
{
    int i;
    bp_neuron * nrn;

    for (i = 0; i < n->NoOfInputs; i++) {
        nrn = n->inputs[i];
        if (nrn != 0) {
            nrn->value_reprojected +=
                (n->value_reprojected * n->weights[i]);
        }
    }
}

/**
* @brief Adjust the weights of a neuron
* @param n Backprop neuron object
* @param learningRate Learning rate in the range 0.0 to 1.0
*/
void bp_neuron_learn(bp_neuron * n,
                     float learningRate)
{
    int i;
    float afact,e,gradient;

    if (n->excluded > 0) return;

    e = learningRate / (1.0f + n->NoOfInputs);
    afact = af(n->value);
    gradient = afact * n->BPerror;
    n->lastBiasChange = e * (n->lastBiasChange + 1.0f) * gradient;
    n->bias += n->lastBiasChange;
    n->min_weight = 9999;
    n->max_weight = -9999;

    /* for each input */
    for (i = 0; i < n->NoOfInputs; i++) {
        if (n->inputs[i] != 0) {
            n->lastWeightChange[i] =
                e * (n->lastWeightChange[i] + 1) *
                gradient * n->inputs[i]->value;
            n->weights[i] += n->lastWeightChange[i];

            /* limit weights within range */
            if (n->weights[i] < n->min_weight) {
                n->min_weight = n->weights[i];
            }
            if (n->weights[i] > n->max_weight) {
                n->max_weight = n->weights[i];
            }
        }
    }
}

/**
* @brief Draws a test pattern within the input weights
*        This can be used for debugging purposes
* @param n Backprop neuron object
* @param depth The depth of the image being represented within the weights
*/
void bp_weights_test_pattern(bp_neuron * n, int depth)
{
    int units = n->NoOfInputs/depth;
    int width = (int)sqrt(units);
    int height = units / width;

    /* clear all weights */
    for (int i = 0; i < n->NoOfInputs; i++) {
        n->weights[i] = 0;
    }

    /* draw a cross */
    for (int x = 0; x < width; x++) {
        int y = x*height/width;
        int p = (y*width + x)*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 1.0f;
        }
        y = (width-1-x)*height/width;
        p = (y*width + x)*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 1.0f;
        }
    }

    for (int x = 0; x < width; x++) {
        int p = x*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 2.0f;
        }
        p = ((height-1)*width + x)*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 2.0f;
        }
    }

    for (int y = 0; y < height; y++) {
        int p = y*width*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 2.0f;
        }
        p = (y*width + (width-1))*depth;
        for (int d = 0; d < depth; d++) {
            n->weights[p+d] = 2.0f;
        }
    }
}

/**
* @brief Saves neuron parameters to a file.  Note that there is no need to
         save the connections, since layers are always fully interconnected
* @param fp File pointer
* @param n Backprop neuron object
* @return zero value if saving is successful
*/
int bp_neuron_save(FILE * fp, bp_neuron * n)
{
    if (fwrite(&n->NoOfInputs, sizeof(int), 1, fp) == 0) {
        return -1;
    }

    if (fwrite(n->weights, sizeof(float), n->NoOfInputs, fp) == 0) {
        return -2;
    }

    if (fwrite(n->lastWeightChange, sizeof(float), n->NoOfInputs, fp) == 0) {
        return -3;
    }

    if (fwrite(&n->min_weight, sizeof(float), 1, fp) == 0) {
        return -4;
    }

    if (fwrite(&n->max_weight, sizeof(float), 1, fp) == 0) {
        return -5;
    }

    if (fwrite(&n->bias, sizeof(float), 1, fp) == 0) {
        return -6;
    }

    if (fwrite(&n->lastBiasChange, sizeof(float), 1, fp) == 0) {
        return -7;
    }

    if (fwrite(&n->desiredValue, sizeof(float), 1, fp) == 0) {
        return -8;
    }

    return 0;
}

/**
* @brief Load neuron parameters from file
* @param fp File pointer
* @param n Backprop neuron object
* @return zero value on success
*/
int bp_neuron_load(FILE * fp, bp_neuron * n)
{
    if (fread(&n->NoOfInputs, sizeof(int), 1, fp) == 0) {
        return -1;
    }

    if (fread(n->weights, sizeof(float), n->NoOfInputs, fp) == 0) {
        return -2;
    }

    if (fread(n->lastWeightChange, sizeof(float), n->NoOfInputs, fp) == 0) {
        return -3;
    }

    if (fread(&n->min_weight, sizeof(float), 1, fp) == 0) {
        return -4;
    }

    if (fread(&n->max_weight, sizeof(float), 1, fp) == 0) {
        return -5;
    }

    if (fread(&n->bias, sizeof(float), 1, fp) == 0) {
        return -6;
    }

    if (fread(&n->lastBiasChange, sizeof(float), 1, fp) == 0) {
        return -7;
    }

    if (fread(&n->desiredValue, sizeof(float), 1, fp) == 0) {
        return -8;
    }

    n->value = 0;
    n->BPerror = 0;
    n->excluded = 0;

    return 0;
}
