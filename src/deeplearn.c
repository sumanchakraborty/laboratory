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

#include "deeplearn.h"

/**
* @brief Returns a training error threshold for the given layer
* @param learner Deep learner object
* @param index Layer index
* @returns Training error threshold (percentage value)
*/
float deeplearn_get_error_threshold(deeplearn * learner, int index)
{
    return(learner->error_threshold[index]);
}

/**
* @brief Sets a training error threshold
* @param learner Deep learner object
* @param index Layer index
* @param value Threshold value as a percentage
*/
void deeplearn_set_error_threshold(deeplearn * learner, int index, float value)
{
    learner->error_threshold[index] = value;
}

/**
* @brief Update the learning history
* @param learner Deep learner object
*/
static void deeplearn_update_history(deeplearn * learner)
{
    int i;
    float error_value;

    if (learner->history_step == 0) return;

    learner->history_ctr++;
    if (learner->history_ctr >= learner->history_step) {
        error_value = learner->BPerror;
        if (error_value == DEEPLEARN_UNKNOWN_ERROR) {
            error_value = 0;
        }

        learner->history[learner->history_index] =
            error_value;
        learner->history_index++;
        learner->history_ctr = 0;

        if (learner->history_index >= DEEPLEARN_HISTORY_SIZE) {
            for (i = 0; i < learner->history_index; i++) {
                learner->history[i/2] = learner->history[i];
            }
            learner->history_index /= 2;
            learner->history_step *= 2;
        }
    }
}

/**
* @brief Initialise a deep learner
* @param learner Deep learner object
* @param no_of_inputs The number of input units
* @param no_of_hiddens The number of hidden units within each layer
* @param hidden_layers The number of hidden layers
* @param no_of_outputs The number of output units
* @param error_threshold Minimum training error for each hidden layer plus
*        the output layer
* @param random_seed Random number generator seed
*/
int deeplearn_init(deeplearn * learner,
                   int no_of_inputs,
                   int no_of_hiddens,
                   int hidden_layers,
                   int no_of_outputs,
                   float error_threshold[],
                   unsigned int * random_seed)
{
    int i;

    /* no training/test data yet */
    learner->data = 0;
    learner->data_samples = 0;
    learner->training_data = 0;
    learner->training_data_samples = 0;
    learner->training_data_labeled = 0;
    learner->training_data_labeled_samples = 0;
    learner->test_data = 0;
    learner->test_data_samples = 0;

    learner->training_ctr = 0;
    learner->history_plot_interval = 100000;
    sprintf(learner->history_plot_filename,"%s","training.png");
    sprintf(learner->history_plot_title,"%s","Training History");

    learner->input_range_min = (float*)malloc(no_of_inputs*sizeof(float));
    if (!learner->input_range_min) {
        return -1;
    }
    learner->input_range_max = (float*)malloc(no_of_inputs*sizeof(float));
    if (!learner->input_range_max) {
        return -2;
    }
    learner->output_range_min = (float*)malloc(no_of_outputs*sizeof(float));
    if (!learner->output_range_min) {
        return -3;
    }
    learner->output_range_max = (float*)malloc(no_of_outputs*sizeof(float));
    if (!learner->output_range_max) {
        return -4;
    }

    for (i = 0; i < no_of_inputs; i++) {
        learner->input_range_min[i] = 99999;
        learner->input_range_max[i] = -99999;
    }
    for (i = 0; i < no_of_outputs; i++) {
        learner->output_range_min[i] = 99999;
        learner->output_range_max[i] = -99999;
    }

    /* has not been trained */
    learner->training_complete = 0;

    /* create the error thresholds for each layer */
    learner->error_threshold =
        (float*)malloc((hidden_layers+1)*sizeof(float));
    if (!learner->error_threshold) {
        return -5;
    }
    memcpy((void*)learner->error_threshold,
           (void*)error_threshold,
           (hidden_layers+1)*sizeof(float));

    /* clear history */
    learner->history_index = 0;
    learner->history_ctr = 0;
    learner->history_step = 1;

    /* clear the number of training itterations */
    learner->itterations = 0;

    /* set the current layer being trained */
    learner->current_hidden_layer = 0;

    /* create the network */
    learner->net = (bp*)malloc(sizeof(bp));
    if (!learner->net) {
        return -6;
    }

    /* initialise the network */
    if (bp_init(learner->net,
                no_of_inputs, no_of_hiddens,
                hidden_layers, no_of_outputs,
                random_seed) != 0) {
        return -7;
    }

    /* create the autocoder */
    learner->autocoder = (bp**)malloc(sizeof(bp*)*hidden_layers);
    if (!learner->autocoder) {
        return -8;
    }
    for (i = 0; i < hidden_layers; i++) {
        learner->autocoder[i] = (bp*)malloc(sizeof(bp));
        if (!learner->autocoder[i]) {
            return -9;
        }
        if (bp_create_autocoder(learner->net, i,
                                learner->autocoder[i]) != 0) {
            return -10;
        }
    }

    learner->BPerror = DEEPLEARN_UNKNOWN_ERROR;
    return 0;
}

/**
* @brief Feeds the input values through the network towards the outputs
* @param learner Deep learner object
*/
void deeplearn_feed_forward(deeplearn * learner)
{
    bp_feed_forward(learner->net);
}

/**
* @brief Performs training initially using autocoders for each hidden
*        layer and eventually for the entire network.
* @param learner Deep learner object
*/
void deeplearn_update(deeplearn * learner)
{
    float minimum_error_percent = 0;
    int current_layer = learner->current_hidden_layer;

    /* only continue if training is not complete */
    if (learner->training_complete == 1) return;

    /* get the maximum backprop error after which a layer
        will be considered to have been trained */
    minimum_error_percent =
        learner->error_threshold[current_layer];

    /* pretraining of autocoders */
    if (current_layer < learner->net->HiddenLayers) {

        /* train the autocoder */
        bp_pretrain(learner->net, learner->autocoder[current_layer],
                    current_layer);

        /* update the backprop error value */
        learner->BPerror = learner->autocoder[current_layer]->BPerrorPercent;

        /* If below the error threshold.
           Only do this after a minimum number of itterations
           in order to allow the running average to stabilise */
        if ((learner->BPerror != DEEPLEARN_UNKNOWN_ERROR) &&
            (learner->BPerror < minimum_error_percent) &&
            (learner->autocoder[current_layer]->itterations > 100)) {

            /* copy the hidden units */
            bp_update_from_autocoder(learner->net,
                                     learner->autocoder[current_layer],
                                     current_layer);

            /* advance to the next hidden layer */
            learner->current_hidden_layer++;

            /* reset the error value */
            learner->BPerror = DEEPLEARN_UNKNOWN_ERROR;
        }
    }
    else {
        bp_update(learner->net,0);

        /* update the backprop error value */
        /*learner->BPerror = learner->net->BPerrorAverage;*/
        learner->BPerror = learner->net->BPerrorPercent;

        /* set the training completed flag */
        if (learner->BPerror < minimum_error_percent) {
            learner->training_complete = 1;
        }
    }

    /* record the history of error values */
    deeplearn_update_history(learner);

    /* increment the number of itterations */
    if (learner->net->itterations < UINT_MAX) {
        learner->net->itterations++;
    }
}

/**
 * @brief Perform continuous unsupervised learning
 * @param learner deep learner object
 */
void deeplearn_update_continuous(deeplearn * learner)
{
    int i;

    learner->BPerror = 0;

    for (i = 0; i < learner->net->HiddenLayers; i++) {
        /* train the autocoder */
        bp_pretrain(learner->net, learner->autocoder[i], i);

        /* update the backprop error value */
        learner->BPerror += learner->autocoder[i]->BPerrorPercent;

        /* copy the hidden units */
        bp_update_from_autocoder(learner->net,
                                 learner->autocoder[i], i);
    }

    learner->BPerror /= learner->net->HiddenLayers;

    /* record the history of error values */
    deeplearn_update_history(learner);
}

/**
* @brief Deallocates memory for the given deep learner object
* @param learner Deep learner object
*/
void deeplearn_free(deeplearn * learner)
{
    /* clear any data */
    deeplearndata * sample = learner->data;
    deeplearndata * prev_sample;

    free(learner->input_range_min);
    free(learner->input_range_max);
    free(learner->output_range_min);
    free(learner->output_range_max);

    while (sample != 0) {
        prev_sample = sample;
        sample = (deeplearndata *)sample->next;
        if (prev_sample != 0) {
            free(prev_sample->inputs);
            free(prev_sample->outputs);
            free(prev_sample);
        }
    }

    /* free training samples */
    deeplearndata_meta * training_sample = learner->training_data;
    deeplearndata_meta * prev_training_sample;
    while (training_sample != 0) {
        prev_training_sample = training_sample;
        training_sample = (deeplearndata_meta *)training_sample->next;
        free(prev_training_sample);
    }

    /* free labeled training samples */
    deeplearndata_meta * training_sample_labeled = learner->training_data_labeled;
    deeplearndata_meta * prev_training_sample_labeled;
    while (training_sample_labeled != 0) {
        prev_training_sample_labeled = training_sample_labeled;
        training_sample_labeled = (deeplearndata_meta *)training_sample_labeled->next;
        free(prev_training_sample_labeled);
    }

    /* free test samples */
    deeplearndata_meta * test_sample = learner->test_data;
    deeplearndata_meta * prev_test_sample;
    while (test_sample != 0) {
        prev_test_sample = test_sample;
        test_sample = (deeplearndata_meta *)test_sample->next;
        free(prev_test_sample);
    }

    /* free the error thresholds */
    free(learner->error_threshold);

    /* free the autocoder */
    for (int i = 0; i < learner->net->HiddenLayers; i++) {
        bp_free(learner->autocoder[i]);
        free(learner->autocoder[i]);
        learner->autocoder[i] = 0;
    }
    free(learner->autocoder);

    /* free the learner */
    bp_free(learner->net);
    free(learner->net);
}

/**
* @brief Sets the value of an input to the network
* @param learner Deep learner object
* @param index Index number of the input unit
* @param value Value to set the input unit to in the range 0.0 to 1.0
*/
void deeplearn_set_input(deeplearn * learner, int index, float value)
{
    bp_set_input(learner->net, index, value);
}

/**
* @brief Sets inputs from the given data sample.
* The sample can contain arbitrary floating point values, so these
* need to be normalised into a 0.25-0.75 range
* @param learner Deep learner object
*/
void deeplearn_set_inputs(deeplearn * learner, deeplearndata * sample)
{
    for (int i = 0; i < learner->net->NoOfInputs; i++) {
        float value = sample->inputs[i];
        float range = learner->input_range_max[i] - learner->input_range_min[i];
        if (range > 0) {
            float normalised = (((value - learner->input_range_min[i])/range)*0.5) + 0.25;
            deeplearn_set_input(learner, i, normalised);
        }
    }
}

/**
* @brief Sets the value of an output unit
* @param learner Deep learner object
* @param index Index number of the output unit
* @param value Value to set the output unit to in the range 0.0 to 1.0
*/
void deeplearn_set_output(deeplearn * learner, int index, float value)
{
    bp_set_output(learner->net, index, value);
}

/**
* @brief Sets outputs from the given data sample.
* The sample can contain arbitrary floating point values, so these
* need to be normalised into a 0.25-0.75 range
* @param learner Deep learner object
*/
void deeplearn_set_outputs(deeplearn * learner, deeplearndata * sample)
{
    for (int i = 0; i < learner->net->NoOfOutputs; i++) {
        float value = sample->outputs[i];
        float range = learner->output_range_max[i] - learner->output_range_min[i];
        if (range > 0) {
            float normalised = (((value - learner->output_range_min[i])/range)*0.5) + 0.25;
            deeplearn_set_output(learner, i, normalised);
        }
    }
}

/**
* @brief Returns the values of outputs within their normal range
* @param learner Deep learner object
* @param outputs The returned output values
*/
void deeplearn_get_outputs(deeplearn * learner, float * outputs)
{
    for (int i = 0; i < learner->net->NoOfOutputs; i++) {
        float value = deeplearn_get_output(learner, i);
        float range = learner->output_range_max[i] - learner->output_range_min[i];
        if (range > 0) {
            outputs[i] =
                (((value - 0.25f)/0.5f)*range) + learner->output_range_min[i];
        }
    }
}

/**
* @brief Returns the value of an output unit
* @param learner Deep learner object
* @param index Index number of the output unit
* @return Value of the output unit to in the range 0.0 to 1.0
*/
float deeplearn_get_output(deeplearn * learner, int index)
{
    return bp_get_output(learner->net, index);
}

/**
* @brief Gets the output class as an integer value
* @param learner Deep learner object
* @return output class
*/
int deeplearn_get_class(deeplearn * learner)
{
    int i, class = -9999;
    float max = -1;
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        if (bp_get_output(learner->net, i) > max) {
            max = bp_get_output(learner->net, i);
            class = i;
        }
    }
    return class;
}

/**
* @brief Sets the output class
* @param learner Deep learner object
* @param class The class number
*/
void deeplearn_set_class(deeplearn * learner, int class)
{
    int i;
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        if (i != class) {
            bp_set_output(learner->net, i, 0.25f);
        }
        else {
            bp_set_output(learner->net, i, 0.75f);
        }
    }
}

/**
* @brief Saves the given deep learner object to a file
* @param fp File pointer
* @param learner Deep learner object
* @return Non-zero value on success
*/
int deeplearn_save(FILE * fp, deeplearn * learner)
{
    int retval,i;

    retval = fwrite(&learner->training_complete, sizeof(int), 1, fp);
    retval = fwrite(&learner->itterations, sizeof(unsigned int), 1, fp);
    retval = fwrite(&learner->current_hidden_layer, sizeof(int), 1, fp);
    retval = fwrite(&learner->BPerror, sizeof(float), 1, fp);

    retval = bp_save(fp, learner->net);

    for (i = 0; i < learner->net->HiddenLayers; i++) {
        retval = bp_save(fp, learner->autocoder[i]);
    }

    /* save error thresholds */
    retval = fwrite(learner->error_threshold, sizeof(float),
                    learner->net->HiddenLayers+1, fp);

    /* save ranges */
    retval = fwrite(learner->input_range_min, sizeof(float), learner->net->NoOfInputs, fp);
    retval = fwrite(learner->input_range_max, sizeof(float), learner->net->NoOfInputs, fp);
    retval = fwrite(learner->output_range_min, sizeof(float), learner->net->NoOfOutputs, fp);
    retval = fwrite(learner->output_range_max, sizeof(float), learner->net->NoOfOutputs, fp);

    /* save the history */
    retval = fwrite(&learner->history_index, sizeof(int), 1, fp);
    retval = fwrite(&learner->history_ctr, sizeof(int), 1, fp);
    retval = fwrite(&learner->history_step, sizeof(int), 1, fp);
    retval = fwrite(learner->history, sizeof(float),
                    learner->history_index, fp);

    return retval;
}

/**
* @brief Loads a deep learner object from file
* @param fp File pointer
* @param learner Deep learner object
* @param random_seed Random number generator seed
* @return zero value on success
*/
int deeplearn_load(FILE * fp, deeplearn * learner,
                   unsigned int * random_seed)
{
    int retval,i;

    /* no training/test data yet */
    learner->data = 0;
    learner->data_samples = 0;
    learner->training_data = 0;
    learner->training_data_samples = 0;
    learner->training_data_labeled = 0;
    learner->training_data_labeled_samples = 0;
    learner->test_data = 0;
    learner->test_data_samples = 0;

    retval = fread(&learner->training_complete, sizeof(int), 1, fp);
    if (retval == 0) {
        return -1;
    }
    retval = fread(&learner->itterations, sizeof(unsigned int), 1, fp);
    if (retval == 0) {
        return -2;
    }
    retval = fread(&learner->current_hidden_layer, sizeof(int), 1, fp);
    if (retval == 0) {
        return -3;
    }
    retval = fread(&learner->BPerror, sizeof(float), 1, fp);
    if (retval == 0) {
        return -4;
    }

    learner->net = (bp*)malloc(sizeof(bp));
    if (bp_load(fp, learner->net, random_seed) != 0) {
        return -5;
    }

    learner->autocoder = (bp**)malloc(sizeof(bp*)*learner->net->HiddenLayers);
    if (!learner->autocoder) {
        return -6;
    }
    for (i = 0; i < learner->net->HiddenLayers; i++) {
        learner->autocoder[i] = (bp*)malloc(sizeof(bp));
        if (bp_load(fp, learner->autocoder[i], random_seed) != 0) {
            return -7;
        }
    }

    /* load error thresholds */
    learner->error_threshold =
        (float*)malloc((learner->net->HiddenLayers+1)*
                       sizeof(float));
    retval = fread(learner->error_threshold, sizeof(float),
                   learner->net->HiddenLayers+1, fp);
    if (retval == 0) {
        return -8;
    }

    /* load ranges */
    learner->input_range_min = (float*)malloc(learner->net->NoOfInputs*sizeof(float));
    if (!learner->input_range_min) {
        return -13;
    }
    learner->input_range_max = (float*)malloc(learner->net->NoOfInputs*sizeof(float));
    if (!learner->input_range_max) {
        return -14;
    }
    learner->output_range_min = (float*)malloc(learner->net->NoOfOutputs*sizeof(float));
    if (!learner->output_range_min) {
        return -15;
    }
    learner->output_range_max = (float*)malloc(learner->net->NoOfOutputs*sizeof(float));
    if (!learner->output_range_max) {
        return -16;
    }
    retval = fread(learner->input_range_min, sizeof(float), learner->net->NoOfInputs, fp);
    if (retval == 0) {
        return -17;
    }
    retval = fread(learner->input_range_max, sizeof(float), learner->net->NoOfInputs, fp);
    if (retval == 0) {
        return -18;
    }
    retval = fread(learner->output_range_min, sizeof(float), learner->net->NoOfOutputs, fp);
    if (retval == 0) {
        return -19;
    }
    retval = fread(learner->output_range_max, sizeof(float), learner->net->NoOfOutputs, fp);
    if (retval == 0) {
        return -20;
    }

    /* load the history */
    retval = fread(&learner->history_index, sizeof(int), 1, fp);
    if (retval == 0) {
        return -9;
    }
    retval = fread(&learner->history_ctr, sizeof(int), 1, fp);
    if (retval == 0) {
        return -10;
    }
    retval = fread(&learner->history_step, sizeof(int), 1, fp);
    if (retval == 0) {
        return -11;
    }
    retval = fread(learner->history, sizeof(float),
                   learner->history_index, fp);
    if (retval == 0) {
        return -12;
    }

    return 0;
}

/**
* @brief Compares two deep learners and returns a greater
*        than zero value if they are the same
* @param learner1 First deep learner object
* @param learner2 Second deep learner object
* @return Greater than zero if the two learners are the same
*/
int deeplearn_compare(deeplearn * learner1,
                      deeplearn * learner2)
{
    int retval,i;

    if (learner1->current_hidden_layer !=
        learner2->current_hidden_layer) {
        return -1;
    }
    if (learner1->BPerror != learner2->BPerror) {
        return -2;
    }
    retval = bp_compare(learner1->net,learner2->net);
    if (retval < 1) return -3;
    if (learner1->history_index !=
        learner2->history_index) {
        return -5;
    }
    if (learner1->history_ctr !=
        learner2->history_ctr) {
        return -6;
    }
    if (learner1->history_step !=
        learner2->history_step) {
        return -7;
    }
    for (i = 0; i < learner1->history_index; i++) {
        if (learner1->history[i] !=
            learner2->history[i]) {
            return -8;
        }
    }
    if (learner1->itterations !=
        learner2->itterations) {
        return -9;
    }
    for (i = 0; i < learner1->net->HiddenLayers+1; i++) {
        if (learner1->error_threshold[i] !=
            learner2->error_threshold[i]) {
            return -10;
        }
    }
    for (i = 0; i < learner1->net->NoOfInputs; i++) {
        if (learner1->input_range_min[i] !=
            learner2->input_range_min[i]) {
            return -11;
        }
        if (learner1->input_range_max[i] !=
            learner2->input_range_max[i]) {
            return -12;
        }
    }
    for (i = 0; i < learner1->net->NoOfOutputs; i++) {
        if (learner1->output_range_min[i] !=
            learner2->output_range_min[i]) {
            return -13;
        }
        if (learner1->output_range_max[i] !=
            learner2->output_range_max[i]) {
            return -14;
        }
    }
    return 1;
}

/**
* @brief Uses gnuplot to plot the training error for the given learner
* @param learner Deep learner object
* @param filename Filename for the image to save as
* @param title Title of the graph
* @param image_width Width of the image in pixels
* @param image_height Height of the image in pixels
* @return zero on success
*/
int deeplearn_plot_history(deeplearn * learner,
                           char * filename, char * title,
                           int image_width, int image_height)
{
    int index,retval=0;
    FILE * fp;
    char data_filename[256];
    char plot_filename[256];
    char command_str[256];
    float value;
    float max_value = 0.01f;

    sprintf(data_filename,"%s%s",DEEPLEARN_TEMP_DIRECTORY,"libgpr_data.dat");
    sprintf(plot_filename,"%s%s",DEEPLEARN_TEMP_DIRECTORY,"libgpr_data.plot");

    /* save the data */
    fp = fopen(data_filename,"w");
    if (!fp) return -1;
    for (index = 0; index < learner->history_index; index++) {
        value = learner->history[index];
        fprintf(fp,"%d    %.10f\n",
                index*learner->history_step,value);
        /* record the maximum error value */
        if (value > max_value) {
            max_value = value;
        }
    }
    fclose(fp);

    /* create a plot file */
    fp = fopen(plot_filename,"w");
    if (!fp) return -1;
    fprintf(fp,"%s","reset\n");
    fprintf(fp,"set title \"%s\"\n",title);
    fprintf(fp,"set xrange [0:%d]\n",
            learner->history_index*learner->history_step);
    fprintf(fp,"set yrange [0:%f]\n",max_value*102/100);
    fprintf(fp,"%s","set lmargin 9\n");
    fprintf(fp,"%s","set rmargin 2\n");
    fprintf(fp,"%s","set xlabel \"Time Step\"\n");
    fprintf(fp,"%s","set ylabel \"Training Error Percent\"\n");

    fprintf(fp,"%s","set grid\n");
    fprintf(fp,"%s","set key right top\n");

    fprintf(fp,"set terminal png size %d,%d\n",
            image_width, image_height);
    fprintf(fp,"set output \"%s\"\n", filename);
    fprintf(fp,"plot \"%s\" using 1:2 notitle with lines\n",
            data_filename);
    fclose(fp);

    /* run gnuplot using the created files */
    sprintf(command_str,"gnuplot %s", plot_filename);
    retval = system(command_str); /* I assume this is synchronous */

    /* remove temporary files */
    sprintf(command_str,"rm %s %s", data_filename,plot_filename);
    retval = system(command_str);

    return retval;
}

/**
* @brief Updates the input units from a patch within a larger image
* @param learner Deep learner object
* @param img Image buffer (1 byte per pixel)
* @param image_width Width of the image in pixels
* @param image_height Height of the image in pixels
* @param tx Top left x coordinate of the patch
* @param ty Top left y coordinate of the patch
*/
void deeplearn_inputs_from_image_patch(deeplearn * learner,
                                       unsigned char * img,
                                       int image_width, int image_height,
                                       int tx, int ty)
{
    bp_inputs_from_image_patch(learner->net,
                               img, image_width, image_height,
                               tx, ty);
}

/**
* @brief Updates the input units from an image
* @param learner Deep learner object
* @param img Image buffer (1 byte per pixel)
* @param image_width Width of the image in pixels
* @param image_height Height of the image in pixels
*/
void deeplearn_inputs_from_image(deeplearn * learner,
                                 unsigned char * img,
                                 int image_width, int image_height)
{
    bp_inputs_from_image(learner->net, img, image_width, image_height);
}

/**
* @brief Sets the learning rate
* @param learner Deep learner object
* @param rate the learning rate in the range 0.0 to 1.0
*/
void deeplearn_set_learning_rate(deeplearn * learner, float rate)
{
    learner->net->learningRate = rate;

    for (int i = 0; i < learner->net->HiddenLayers; i++) {
        learner->autocoder[i]->learningRate = rate;
    }
}

/**
* @brief Sets the percentage of units which drop out during training
* @param learner Deep learner object
* @param dropout_percent Percentage of units which drop out in the range 0 to 100
*/
void deeplearn_set_dropouts(deeplearn * learner, float dropout_percent)
{
    learner->net->DropoutPercent = dropout_percent;

    for (int i = 0; i < learner->net->HiddenLayers; i++) {
        learner->autocoder[i]->DropoutPercent = dropout_percent;
    }
}

/**
* @brief Exports a trained network as a standalone C program
* @param learner Deep learner object
* @param filename The C source file to be produced
* @returns zero on success
*/
static int deeplearn_export_c(deeplearn * learner, char * filename)
{
    FILE * fp;
    int i, j, k, no_of_weights;

    fp = fopen(filename,"w");
    if (!fp) {
        return -1;
    }

    fprintf(fp,"%s\n","#include <stdio.h>");
    fprintf(fp,"%s\n","#include <stdlib.h>");
    fprintf(fp,"%s\n","#include <math.h>");
    fprintf(fp,"\n");
    fprintf(fp, "const int no_of_inputs = %d;\n",
            learner->net->NoOfInputs);
    fprintf(fp, "const int no_of_hiddens = %d;\n",
            learner->net->NoOfHiddens);
    fprintf(fp, "const int no_of_outputs = %d;\n",
            learner->net->NoOfOutputs);
    fprintf(fp, "const int hidden_layers = %d;\n",
            learner->net->HiddenLayers);
    fprintf(fp,"\n");

    /* ranges */
    fprintf(fp, "float input_range_min[] = {\n");
    fprintf(fp, "  ");
    for (i = 0; i < learner->net->NoOfInputs; i++) {
        fprintf(fp, "%f", learner->input_range_min[i]);
        if (i < learner->net->NoOfInputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n};\n\n");
    fprintf(fp, "float input_range_max[] = {\n");
    fprintf(fp, "  ");
    for (i = 0; i < learner->net->NoOfInputs; i++) {
        fprintf(fp, "%f", learner->input_range_max[i]);
        if (i < learner->net->NoOfInputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n};\n\n");
    fprintf(fp, "float output_range_min[] = {\n");
    fprintf(fp, "  ");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f", learner->output_range_min[i]);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n};\n\n");
    fprintf(fp, "float output_range_max[] = {\n");
    fprintf(fp, "  ");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f", learner->output_range_max[i]);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n};\n\n");

    /* hidden unit weights */
    for (i = 0; i < learner->net->HiddenLayers; i++) {
        fprintf(fp,
                "float hidden_layer_%d_weights[] = {\n  ", i);
        if (i == 0) {
            no_of_weights = learner->net->NoOfInputs;
        }
        else {
            no_of_weights = bp_hiddens_in_layer(learner->net, i-1);
        }
        for (j = 0; j < bp_hiddens_in_layer(learner->net, i); j++) {
            for (k = 0; k < no_of_weights; k++) {
                fprintf(fp, "%f",
                        learner->net->hiddens[i][j]->weights[k]);
                if (!((j == bp_hiddens_in_layer(learner->net, i)-1) &&
                      (k == no_of_weights-1))) {
                    fprintf(fp, ",");
                }
            }
        }
        fprintf(fp, "\n};\n\n");
    }

    /* hidden unit biases */
    for (i = 0; i < learner->net->HiddenLayers; i++) {
        fprintf(fp,
                "float hidden_layer_%d_bias[] = {\n  ", i);
        for (j = 0; j < bp_hiddens_in_layer(learner->net, i); j++) {
            fprintf(fp,"%f",learner->net->hiddens[i][j]->bias);
            if (j < bp_hiddens_in_layer(learner->net, i)-1) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n};\n\n");
    }

    /* output unit weights */
    fprintf(fp,
            "float output_layer_weights[] = {\n  ");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        for (j = 0; j < bp_hiddens_in_layer(learner->net, learner->net->HiddenLayers-1); j++) {
            fprintf(fp, "%f",
                    learner->net->outputs[i]->weights[j]);
            if (!((i == learner->net->NoOfOutputs-1) &&
                  (j == bp_hiddens_in_layer(learner->net, learner->net->HiddenLayers-1)-1))) {
                fprintf(fp, ",");
            }
        }
    }
    fprintf(fp, "\n};\n\n");

    /* output unit biases */
    fprintf(fp,
            "float output_layer_bias[] = {\n  ");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f",
                learner->net->outputs[i]->bias);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n};\n\n");
    fprintf(fp, "float inputs[%d];\n",learner->net->NoOfInputs);
    fprintf(fp, "float prev_hiddens[%d];\n",learner->net->NoOfHiddens);
    fprintf(fp, "float hiddens[%d];\n",learner->net->NoOfHiddens);
    fprintf(fp, "float outputs[%d];\n\n",learner->net->NoOfOutputs);

    fprintf(fp, "int main(int argc, char* argv[])\n");
    fprintf(fp, "{\n");

    fprintf(fp, "  int i,j;\n");
    fprintf(fp, "  float sum;\n\n");
    fprintf(fp, "  if (argc < %d) return -1;\n\n", learner->net->NoOfInputs);
    fprintf(fp, "  for (i = 1; i < argc; i++) {\n");
    fprintf(fp, "    if (i > no_of_inputs) return -2;\n");
    fprintf(fp, "    inputs[i-1] = atof(argv[i]);\n");
    fprintf(fp, "  }\n\n");

    fprintf(fp, "  /* Normalise inputs into a 0.25 - 0.75 range */\n");
    fprintf(fp, "  for (i = 0; i < no_of_inputs; i++) {\n");
    fprintf(fp, "    inputs[i] = 0.25f + ((inputs[i] - input_range_min[i])*0.5f/(input_range_max[i] - input_range_min[i]));\n");
    fprintf(fp, "    if (inputs[i] < 0.25f) inputs[i] = 0.25f;\n");
    fprintf(fp, "    if (inputs[i] > 0.75f) inputs[i] = 0.75f;\n");
    fprintf(fp, "  }\n\n");

    fprintf(fp, "  /* Hidden layer 1 */\n");
    fprintf(fp, "  for (i = 0; i < no_of_hiddens; i++) {\n");
    fprintf(fp, "    sum = hidden_layer_0_bias[i];\n");
    fprintf(fp, "    for (j = 0; j < no_of_inputs; j++) {\n");
    fprintf(fp, "      sum += hidden_layer_0_weights[i*no_of_inputs+j]*inputs[j];\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "    hiddens[i] = 1.0f / (1.0f + exp(-sum));\n");
    fprintf(fp, "  }\n");
    fprintf(fp, "  for (i = 0; i < no_of_hiddens; i++) {\n");
    fprintf(fp, "    prev_hiddens[i] = hiddens[i];\n");
    fprintf(fp, "  }\n\n");
    for (i = 1; i < learner->net->HiddenLayers; i++) {
        fprintf(fp, "  /* Hidden layer %d */\n", i+1);
        fprintf(fp, "  for (i = 0; i < %d; i++) {\n", bp_hiddens_in_layer(learner->net,i));
        fprintf(fp, "    sum = hidden_layer_%d_bias[i];\n",i);
        fprintf(fp, "    for (j = 0; j < %d; j++) {\n",bp_hiddens_in_layer(learner->net,i-1));
        fprintf(fp, "      sum += hidden_layer_%d_weights[i*%d+j]*prev_hiddens[j];\n",i,bp_hiddens_in_layer(learner->net,i-1));
        fprintf(fp, "    }\n");
        fprintf(fp, "    hiddens[i] = 1.0f / (1.0f + exp(-sum));\n");
        fprintf(fp, "  }\n");
        fprintf(fp, "  for (i = 0; i < %d; i++) {\n",bp_hiddens_in_layer(learner->net,i));
        fprintf(fp, "    prev_hiddens[i] = hiddens[i];\n");
        fprintf(fp, "  }\n\n");
    }
    fprintf(fp, "  /* Output layer */\n");
    fprintf(fp, "  for (i = 0; i < no_of_outputs; i++) {\n");
    fprintf(fp, "    sum = output_layer_bias[i];\n");
    fprintf(fp, "    for (j = 0; j < %d; j++) {\n",bp_hiddens_in_layer(learner->net,learner->net->HiddenLayers-1));
    fprintf(fp, "      sum += output_layer_weights[i*%d+j]*prev_hiddens[j];\n",bp_hiddens_in_layer(learner->net,learner->net->HiddenLayers-1));
    fprintf(fp, "    }\n");
    fprintf(fp, "    outputs[i] = 1.0f / (1.0f + exp(-sum));\n");
    fprintf(fp, "  }\n\n");

    fprintf(fp, "  for (i = 0; i < no_of_outputs; i++) {\n");
    fprintf(fp, "    /* Convert outputs from 0.25 - 0.75 back to their original range */\n");
    fprintf(fp, "    outputs[i] = output_range_min[i] + ((outputs[i]-0.25f)*(output_range_max[i] - output_range_min[i])/0.5f);\n");
    fprintf(fp, "    /* Send the outputs to stdout */\n");
    fprintf(fp, "    printf(\"%%f\",outputs[i]);\n");
    fprintf(fp, "    if (i < no_of_outputs-1) {\n");
    fprintf(fp, "      printf(\" \");\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "  }\n\n");
    fprintf(fp, "  printf(\"\\n\");");
    fprintf(fp, "\n");
    fprintf(fp, "  return 0;\n");
    fprintf(fp, "}\n");
    fclose(fp);
    return 0;
}

/**
* @brief Exports a trained network as a standalone python class
* @param learner Deep learner object
* @param filename The python source file to be produced
* @returns zero on success
*/
static int deeplearn_export_python(deeplearn * learner, char * filename)
{
    FILE * fp;
    int i, j, k, no_of_weights;

    fp = fopen(filename,"w");
    if (!fp) {
        return -1;
    }

    fprintf(fp, "import sys\n");
    fprintf(fp, "import math\n\n");

    fprintf(fp,"%s\n","class NeuralNet:");
    fprintf(fp,"\n");
    fprintf(fp, "  no_of_inputs = %d\n",
            learner->net->NoOfInputs);
    fprintf(fp, "  no_of_hiddens = %d\n",
            learner->net->NoOfHiddens);
    fprintf(fp, "  no_of_outputs = %d\n",
            learner->net->NoOfOutputs);
    fprintf(fp, "  hidden_layers = %d\n",
            learner->net->HiddenLayers);
    fprintf(fp,"\n");

    /* ranges */
    fprintf(fp, "  input_range_min = [");
    for (i = 0; i < learner->net->NoOfInputs; i++) {
        fprintf(fp, "%f", learner->input_range_min[i]);
        if (i < learner->net->NoOfInputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\n\n");
    fprintf(fp, "  input_range_max = [");
    for (i = 0; i < learner->net->NoOfInputs; i++) {
        fprintf(fp, "%f", learner->input_range_max[i]);
        if (i < learner->net->NoOfInputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\n\n");
    fprintf(fp, "  output_range_min = [");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f", learner->output_range_min[i]);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\n\n");
    fprintf(fp, "  output_range_max = [");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f", learner->output_range_max[i]);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\n\n");

    /* hidden unit weights */
    for (i = 0; i < learner->net->HiddenLayers; i++) {
        fprintf(fp,
                "  hidden_layer_%d_weights = [", i);
        if (i == 0) {
            no_of_weights = learner->net->NoOfInputs;
        }
        else {
            no_of_weights = bp_hiddens_in_layer(learner->net, i-1);
        }
        for (j = 0; j < bp_hiddens_in_layer(learner->net, i); j++) {
            for (k = 0; k < no_of_weights; k++) {
                fprintf(fp, "%f",
                        learner->net->hiddens[i][j]->weights[k]);
                if (!((j == bp_hiddens_in_layer(learner->net, i)-1) &&
                      (k == no_of_weights-1))) {
                    fprintf(fp, ",");
                }
            }
        }
        fprintf(fp, "]\n\n");
    }

    /* hidden unit biases */
    for (i = 0; i < learner->net->HiddenLayers; i++) {
        fprintf(fp,
                "  hidden_layer_%d_bias = [", i);
        for (j = 0; j < bp_hiddens_in_layer(learner->net, i); j++) {
            fprintf(fp,"%f",learner->net->hiddens[i][j]->bias);
            if (j < bp_hiddens_in_layer(learner->net, i)-1) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "]\n\n");
    }

    /* output unit weights */
    fprintf(fp,
            "  output_layer_weights = [");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        for (j = 0; j < bp_hiddens_in_layer(learner->net, learner->net->HiddenLayers-1); j++) {
            fprintf(fp, "%f",
                    learner->net->outputs[i]->weights[j]);
            if (!((i == learner->net->NoOfOutputs-1) &&
                  (j == bp_hiddens_in_layer(learner->net, learner->net->HiddenLayers-1)-1))) {
                fprintf(fp, ",");
            }
        }
    }
    fprintf(fp, "]\n\n");

    /* output unit biases */
    fprintf(fp,
            "  output_layer_bias = [");
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        fprintf(fp, "%f",
                learner->net->outputs[i]->bias);
        if (i < learner->net->NoOfOutputs-1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\n\n");
    fprintf(fp, "\n");

    fprintf(fp, "  def update(inputs):\n\n");

    fprintf(fp, "%s", "    prev_hiddens = []\n");
    fprintf(fp, "%s", "    hiddens = []\n");
    fprintf(fp, "%s", "    outputs = []\n\n");
    fprintf(fp, "    if len(inputs) < %d:\n", learner->net->NoOfInputs);
    fprintf(fp, "        return []\n\n");

    fprintf(fp, "    # Normalise inputs into a 0.25 - 0.75 range\n");
    fprintf(fp, "    for i in range (no_of_inputs):\n");
    fprintf(fp, "      inputs[i] = 0.25 + ((inputs[i] - input_range_min[i])*0.5/(input_range_max[i] - input_range_min[i]))\n");
    fprintf(fp, "      if inputs[i] < 0.25:\n");
    fprintf(fp, "        inputs[i] = 0.25\n");
    fprintf(fp, "      if inputs[i] > 0.75:\n");
    fprintf(fp, "        inputs[i] = 0.75\n\n");

    fprintf(fp, "    # Hidden layer 1\n");
    fprintf(fp, "    for i in range(no_of_hiddens):\n");
    fprintf(fp, "      adder = hidden_layer_0_bias[i]\n");
    fprintf(fp, "      for j in range(no_of_inputs):\n");
    fprintf(fp, "        adder = adder + hidden_layer_0_weights[i*no_of_inputs+j]*inputs[j]\n");
    fprintf(fp, "      hiddens[i] = 1.0 / (1.0f + math.exp(-adder))\n");
    fprintf(fp, "    for i in range(no_of_hiddens):\n");
    fprintf(fp, "      prev_hiddens[i] = hiddens[i]\n\n");
    for (i = 1; i < learner->net->HiddenLayers; i++) {
        fprintf(fp, "    # Hidden layer %d\n", i+1);
        fprintf(fp, "    for i in range(%d):\n", bp_hiddens_in_layer(learner->net,i));
        fprintf(fp, "      adder = hidden_layer_%d_bias[i]\n",i);
        fprintf(fp, "      for j in range(%d):\n",bp_hiddens_in_layer(learner->net,i-1));
        fprintf(fp, "        adder = adder + hidden_layer_%d_weights[i*%d+j]*prev_hiddens[j]\n",i,bp_hiddens_in_layer(learner->net,i-1));
        fprintf(fp, "      hiddens[i] = 1.0 / (1.0 + math.exp(-adder))\n");
        fprintf(fp, "    for i in range(%d):\n",bp_hiddens_in_layer(learner->net,i));
        fprintf(fp, "      prev_hiddens[i] = hiddens[i]\n\n");
    }
    fprintf(fp, "    # Output layer\n");
    fprintf(fp, "    for i in range(no_of_outputs):\n");
    fprintf(fp, "      adder = output_layer_bias[i]\n");
    fprintf(fp, "      for j in range(%d):\n",bp_hiddens_in_layer(learner->net,learner->net->HiddenLayers-1));
    fprintf(fp, "        adder = adder + output_layer_weights[i*%d+j]*prev_hiddens[j]\n",bp_hiddens_in_layer(learner->net,learner->net->HiddenLayers-1));
    fprintf(fp, "      outputs[i] = 1.0 / (1.0 + math.exp(-adder))\n\n");
    fprintf(fp, "    # Convert outputs from 0.25 - 0.75 back to their original range\n");
    fprintf(fp, "    for i in range(no_of_outputs):\n");
    fprintf(fp, "      outputs[i] = output_range_min[i] + ((outputs[i]-0.25)*(output_range_max[i] - output_range_min[i])/0.5)\n");
    fprintf(fp, "\n");
    fprintf(fp, "    # Return the output unit values as a list\n");
    fprintf(fp, "    return outputs\n\n\n");

    fprintf(fp, "# Create an instance of the class\n");
    fprintf(fp, "net = NeuralNet()\n\n");
    fprintf(fp, "# Use the commandline arguments as input values\n");
    fprintf(fp, "print net.update(sys.argv[1:])\n");
    fclose(fp);
    return 0;
}

/**
* @brief Exports a trained network as a standalone program
*        file types supported are .c and .py
* @param learner Deep learner object
* @param filename The source file to be produced
* @returns zero on success
*/
int deeplearn_export(deeplearn * learner, char * filename)
{
    int length = strlen(filename);

    if (length > 3) {
        if ((filename[length-3] == '.') &&
            (filename[length-2] == 'p') &&
            (filename[length-1] == 'y')) {
            return deeplearn_export_python(learner, filename);
        }
    }
    return deeplearn_export_c(learner, filename);
}
