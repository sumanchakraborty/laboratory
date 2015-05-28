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
    autocoder->lastBiasChange =
        (float*)malloc(no_of_hiddens*sizeof(float));
    if (!autocoder->lastBiasChange) return -8;
    memset((void*)autocoder->inputs,'\0',no_of_inputs*sizeof(float));
    memset((void*)autocoder->outputs,'\0',no_of_inputs*sizeof(float));
    memset((void*)autocoder->hiddens,'\0',
           no_of_hiddens*sizeof(float));
    memset((void*)autocoder->lastWeightChange,'\0',
           no_of_hiddens*no_of_inputs*sizeof(float));
    memset((void*)autocoder->bperr,'\0',
           autocoder->NoOfHiddens*sizeof(float));
    memset((void*)autocoder->lastBiasChange,'\0',
           autocoder->NoOfHiddens*sizeof(float));
    autocoder->BPerror = AUTOCODER_UNKNOWN;
    autocoder->BPerrorAverage = AUTOCODER_UNKNOWN;
    autocoder->learningRate = 0.2f;
    autocoder->noise = 0;
    autocoder->random_seed = random_seed;
    autocoder->itterations = 0;
    autocoder->DropoutPercent = 0.01f;

    /* initial small random values */
    for (int h = 0; h < no_of_hiddens; h++) {
        autocoder->bias[h] =
            (0.2f*(rand_num(&autocoder->random_seed)%10000/10000.0f))-0.1f;
        for (int i = 0; i < no_of_inputs; i++) {
            autocoder->weights[h*no_of_inputs + i] =
                (0.2f*(rand_num(&autocoder->random_seed)%10000/10000.0f))-0.1f;
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
    free(autocoder->lastBiasChange);
}

/**
* @brief Encodes the inputs to a given array
* @param autocoder Autocoder object
* @param encoded Array to store the encoded values
* @param use_dropouts If non-zero then allow dropouts in the returned results
*/
void autocoder_encode(ac * autocoder, float * encoded, unsigned char use_dropouts)
{
    for (int h = 0; h < autocoder->NoOfHiddens; h++) {
		if (use_dropouts != 0) {
			if (rand_num(&autocoder->random_seed)%10000 <
				autocoder->DropoutPercent*100) {
				autocoder->hiddens[h] = (int)AUTOCODER_DROPPED_OUT;
				continue;
			}
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
        encoded[h] = 1.0f / (1.0f + exp(-adder));
    }
}

/**
* @brief Decodes the encoded (hidden) units to a given output array
* @param autocoder Autocoder object
* @param decoded Array to store the decoded output values
*/
void autocoder_decode(ac * autocoder, float * decoded)
{
    for (int i = 0; i < autocoder->NoOfInputs; i++) {
        /* weighted sum of hidden inputs */
        float adder = 0;
        for (int h = 0; h < autocoder->NoOfHiddens; h++) {
            if ((autocoder->hiddens[h] < AUTOCODER_DROPPED_OUT-1) &&
                (autocoder->hiddens[h] > AUTOCODER_DROPPED_OUT+1))
                continue;
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
        decoded[i] = 1.0f / (1.0f + exp(-adder));
    }
}

/**
* @brief Feed forward
* @param autocoder Autocoder object
*/
void autocoder_feed_forward(ac * autocoder)
{
	autocoder_encode(autocoder, autocoder->hiddens,1);
	autocoder_decode(autocoder, autocoder->outputs);
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
            if ((autocoder->hiddens[h] < AUTOCODER_DROPPED_OUT-1) &&
                (autocoder->hiddens[h] > AUTOCODER_DROPPED_OUT+1))
                continue;
            autocoder->bperr[h] +=
                BPerror * afact * autocoder->weights[h*autocoder->NoOfInputs + i];
        }
    }

    /* error percentage assuming an encoding range
       of 0.25 -> 0.75 */
    errorPercent = errorPercent * 100 / (0.6f*autocoder->NoOfInputs);

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

/**
* @brief Adjusts weights and biases
* @param autocoder Autocoder object
*/
void autocoder_learn(ac * autocoder)
{
    /* weights between outputs and hiddens */
    float e = autocoder->learningRate / (1.0f + autocoder->NoOfHiddens);
    for (int i = 0; i < autocoder->NoOfInputs; i++) {
        float afact = autocoder->outputs[i] * (1.0f - autocoder->outputs[i]);
        float BPerror = autocoder->inputs[i] - autocoder->outputs[i];
        float gradient = afact * BPerror;
        for (int h = 0; h < autocoder->NoOfHiddens; h++) {
            if ((autocoder->hiddens[h] < AUTOCODER_DROPPED_OUT-1) &&
                (autocoder->hiddens[h] > AUTOCODER_DROPPED_OUT+1))
                continue;
            int n = h*autocoder->NoOfInputs + i;
            autocoder->lastWeightChange[n] =
                e * (autocoder->lastWeightChange[n] + 1) *
                gradient * autocoder->hiddens[h];
            autocoder->weights[n] += autocoder->lastWeightChange[n];
        }
    }

    /* weights between hiddens and inputs */
    e = autocoder->learningRate / (1.0f + autocoder->NoOfInputs);
    for (int h = 0; h < autocoder->NoOfHiddens; h++) {
        if ((autocoder->hiddens[h] < AUTOCODER_DROPPED_OUT-1) &&
            (autocoder->hiddens[h] > AUTOCODER_DROPPED_OUT+1))
            continue;
        float afact = autocoder->hiddens[h] * (1.0f - autocoder->hiddens[h]);
        float BPerror = autocoder->bperr[h];
        float gradient = afact * BPerror;
        autocoder->lastBiasChange[h] = e * (autocoder->lastBiasChange[h] + 1.0f) * gradient;
        autocoder->bias[h] += autocoder->lastBiasChange[h];
        for (int i = 0; i < autocoder->NoOfInputs; i++) {
            int n = h*autocoder->NoOfInputs + i;
            autocoder->lastWeightChange[n] =
                e * (autocoder->lastWeightChange[n] + 1) *
                gradient * autocoder->inputs[i];
            autocoder->weights[n] += autocoder->lastWeightChange[n];
        }
    }
}

/**
* @brief Save an autocoder to file
* @param fp Pointer to the file
* @param autocoder Autocoder object
* @return zero on success
*/
int autocoder_save(FILE * fp, ac * autocoder)
{
    if (fwrite(&autocoder->NoOfInputs, sizeof(int), 1, fp) == 0) {
        return -1;
    }
    if (fwrite(&autocoder->NoOfHiddens, sizeof(int), 1, fp) == 0) {
        return -2;
    }
    if (fwrite(&autocoder->DropoutPercent, sizeof(float), 1, fp) == 0) {
        return -3;
    }
    if (fwrite(autocoder->weights, sizeof(float),
               autocoder->NoOfInputs*autocoder->NoOfHiddens, fp) == 0) {
        return -4;
    }
    if (fwrite(autocoder->lastWeightChange, sizeof(float),
               autocoder->NoOfInputs*autocoder->NoOfHiddens, fp) == 0) {
        return -5;
    }
    if (fwrite(autocoder->bias, sizeof(float),
               autocoder->NoOfHiddens, fp) == 0) {
        return -6;
    }
    if (fwrite(autocoder->lastBiasChange, sizeof(float),
               autocoder->NoOfHiddens, fp) == 0) {
        return -7;
    }
    if (fwrite(&autocoder->learningRate, sizeof(float), 1, fp) == 0) {
        return -8;
    }
    if (fwrite(&autocoder->noise, sizeof(float), 1, fp) == 0) {
        return -9;
    }
    if (fwrite(&autocoder->random_seed, sizeof(unsigned int), 1, fp) == 0) {
        return -10;
    }
    if (fwrite(&autocoder->itterations, sizeof(unsigned int), 1, fp) == 0) {
        return -11;
    }
    return 0;
}

/**
* @brief Load an autocoder from file
* @param fp Pointer to the file
* @param autocoder Autocoder object
* @return zero on success
*/
int autocoder_load(FILE * fp, ac * autocoder)
{
    if (fread(&autocoder->NoOfInputs, sizeof(int), 1, fp) == 0) {
        return -1;
    }
    if (fread(&autocoder->NoOfHiddens, sizeof(int), 1, fp) == 0) {
        return -2;
    }
    if (fread(&autocoder->DropoutPercent, sizeof(float), 1, fp) == 0) {
        return -3;
    }
    if (fread(autocoder->weights, sizeof(float),
              autocoder->NoOfInputs*autocoder->NoOfHiddens, fp) == 0) {
        return -4;
    }
    if (fread(autocoder->lastWeightChange, sizeof(float),
              autocoder->NoOfInputs*autocoder->NoOfHiddens, fp) == 0) {
        return -5;
    }
    if (fread(autocoder->bias, sizeof(float),
              autocoder->NoOfHiddens, fp) == 0) {
        return -6;
    }
    if (fread(autocoder->lastBiasChange, sizeof(float),
              autocoder->NoOfHiddens, fp) == 0) {
        return -7;
    }
    if (fread(&autocoder->learningRate, sizeof(float), 1, fp) == 0) {
        return -8;
    }
    if (fread(&autocoder->noise, sizeof(float), 1, fp) == 0) {
        return -9;
    }
    if (fread(&autocoder->random_seed, sizeof(unsigned int), 1, fp) == 0) {
        return -10;
    }
    if (fread(&autocoder->itterations, sizeof(unsigned int), 1, fp) == 0) {
        return -11;
    }
    return 0;
}

/**
* @brief Sets the input of an autocoder
* @param autocoder Autocoder object
* @param index Array index of the input
* @param value The value to set the input to
*/
void autocoder_set_input(ac * autocoder, int index, float value)
{
    autocoder->inputs[index] = value;
}

/**
* @brief Sets autocoder inputs from an array
* @param autocoder Autocoder object
* @param inputs Array containing input values
*/
void autocoder_set_inputs(ac * autocoder, float inputs[])
{
    memcpy((void*)autocoder->inputs, inputs, autocoder->NoOfInputs*sizeof(float));
}

/**
* @brief Returns the value of a hidden unit
* @param autocoder Autocoder object
* @param index Array index of the hidden (encoder) unit
* @return Value of the hidden (encoder) unit
*/
float autocoder_get_hidden(ac * autocoder, int index)
{
    return autocoder->hiddens[index];
}

/**
* @brief Main update routine for training
* @param autocoder Autocoder object
*/
void autocoder_update(ac * autocoder)
{
    autocoder_feed_forward(autocoder);
    autocoder_backprop(autocoder);
    autocoder_learn(autocoder);
}

/**
* @brief Normalises the inputs to the autocoder
* @param autocoder Autocoder object
*/
void autocoder_normalise_inputs(ac * autocoder)
{
    float min = autocoder->inputs[0];
    float max = autocoder->inputs[0];

    for (int i = 1; i < autocoder->NoOfInputs; i++) {
        if (autocoder->inputs[i] < min)
            min = autocoder->inputs[i];
        if (autocoder->inputs[i] > max)
            max = autocoder->inputs[i];
    }

    float range = max - min;
    if (range <= 0) return;

    for (int i = 0; i < autocoder->NoOfInputs; i++) {
        autocoder->inputs[i] =
            0.25f + (((autocoder->inputs[i] - min)/range)*0.5f);
    }
}

/**
* @brief Returns zero if two autocoders are the same
* @param autocoder0 The first autocoder
* @param autocoder1 The second autocoder
* @return zero on success
*/
int autocoder_compare(ac * autocoder0, ac * autocoder1)
{
    if (autocoder0->NoOfInputs != autocoder1->NoOfInputs) {
        return -1;
    }
    if (autocoder0->NoOfHiddens != autocoder1->NoOfHiddens) {
        return -2;
    }
    for (int h = 0; h < autocoder0->NoOfHiddens; h++) {
        if (autocoder0->bias[h] != autocoder1->bias[h]) {
            return -3;
        }
        for (int i = 0; i < autocoder0->NoOfInputs; i++) {
            if (autocoder0->inputs[h*autocoder0->NoOfInputs + i] != autocoder1->inputs[h*autocoder1->NoOfInputs + i]) {
                return -4;
            }
        }
    }
    return 0;
}

/**
* @brief Plots weight matrices within an image
* @param autocoder Autocoder object
* @param filename Filename of the image to save as
* @param image_width Width of the image in pixels
* @param image_height Height of the image in pixels
* @param input_image_width When displaying all inputs as an image this
         is the number of inputs across.  Set this to zero for the
         inputs image to be square.
*/
int autocoder_plot_weights(ac * autocoder,
                           char * filename,
                           int image_width, int image_height,
                           int input_image_width)
{
    unsigned char * img;

    /* allocate memory for the image */
    img = (unsigned char*)malloc(image_width*image_height*3*
                                 sizeof(unsigned char));
    if (!img) {
        return -1;
    }

    /* clear the image with a white background */
    memset((void*)img,'\255',image_width*image_height*3*
           sizeof(unsigned char));

    /* TODO */

    /* write the image to file */
    deeplearn_write_png_file(filename,
                             (unsigned int)image_width,
                             (unsigned int)image_height,
                             24, img);

    /* free the image memory */
    free(img);
    return 0;
}
