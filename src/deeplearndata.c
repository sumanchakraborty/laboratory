/*
 libdeep - a library for deep learning
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

#include "deeplearndata.h"

/**
* @brief Adds a training or test sample to the data set
* @param learner Deep learner object
* @param inputs Input data
* @param outputs Output data 
* @returns 0 on success
*/
int deeplearndata_add(deeplearn * learner,
                      float * inputs,
                      float * outputs)
{
    int i;
    deeplearndata * data;
    data = (deeplearndata*)malloc(sizeof(deeplearndata));
    if (!data) {
        return -1;
    }

    /* create arrays to store the data */
    data->inputs =
      (float*)malloc(learner->net->NoOfInputs*sizeof(float));
    if (!data->inputs) {
        return -2;
    }
    data->outputs =
      (float*)malloc(learner->net->NoOfOutputs*sizeof(float));
    if (!data->outputs) {
        return -3;
    }

    /* copy the data */
    memcpy((void*)data->inputs, inputs, learner->net->NoOfInputs*sizeof(float));
    memcpy((void*)data->outputs, outputs, learner->net->NoOfOutputs*sizeof(float));

    /* update the data range */
    for (i = 0; i < learner->net->NoOfInputs; i++) {
        if (inputs[i] < learner->input_range_min[i]) {
            learner->input_range_min[i] = inputs[i];
        }
        if (inputs[i] > learner->input_range_max[i]) {
            learner->input_range_max[i] = inputs[i];
        }
    }
    for (i = 0; i < learner->net->NoOfOutputs; i++) {
        if (outputs[i] < learner->output_range_min[i]) {
            learner->output_range_min[i] = outputs[i];
        }
        if (outputs[i] > learner->output_range_max[i]) {
            learner->output_range_max[i] = outputs[i];
        }
    }
    
    data->flags = 0;
    
    /* change the current head of the list */
    data->prev = 0;
    data->next = 0;
    if (learner->data) {
      learner->data->prev = (struct deeplearndata *)data;
      data->next = (struct deeplearndata *)learner->data;
    }
    learner->data = data;
    learner->data_samples++;
    
    return 0;
}

/**
* @brief Returns a metadata sample
* @param Pointer to the metadata list
* @returns metadata object
*/
static deeplearndata_meta * deeplearndata_get_meta(deeplearndata_meta * list, int index)
{
    int i = 0;
    deeplearndata_meta * ptr = list;
  
    while (i < index) {
        if (ptr == 0) {
            break;
        }
        ptr = (deeplearndata_meta*)ptr->next;
        i++;
    }
    return ptr;
}

/**
* @brief Returns a training data sample
* @param learner Deep learner object
* @returns deeplearndata object
*/
deeplearndata * deeplearndata_get_training(deeplearn * learner, int index)
{
    if ((index < 0) || (index >= learner->training_data_samples)) {
        return 0;
    }
    deeplearndata_meta * meta = deeplearndata_get_meta(learner->training_data, index);
    if (meta == 0) {
        return 0;
    }
    return meta->sample;
}

/**
* @brief Returns a test data sample
* @param learner Deep learner object
* @returns deeplearndata object
*/
deeplearndata * deeplearndata_get_test(deeplearn * learner, int index)
{
    if ((index < 0) || (index >= learner->test_data_samples)) {
        return 0;
    }
    deeplearndata_meta * meta = deeplearndata_get_meta(learner->test_data, index);
    if (meta == 0) {
        return 0;
    }
    return meta->sample;
}

/**
* @brief Returns a data sample
* @param learner Deep learner object
* @returns deeplearndata object
*/
deeplearndata * deeplearndata_get(deeplearn * learner, int index)
{
    int i = 0;
    deeplearndata * ptr = learner->data;
  
    /* range checking of the index */
    if ((index < 0) || (index >= learner->data_samples)) {
      return 0;
    }
    while (i < index) {
        if (ptr == 0) {
            break;
        }
        ptr = (deeplearndata*)ptr->next;
        i++;
    }
    return ptr;
}

/**
* @brief Clears the flags on every data sample
* @param learner Deep learner object
*/
static void deeplearndata_clear_flags(deeplearn * learner)
{
    deeplearndata * ptr = learner->data;
    while (ptr != 0) {
        ptr->flags = 0;
        ptr = (deeplearndata*)ptr->next;
    }
}

/**
* @brief Clears existing training and test data sets
* @param learner Deep learner object
*/
static void deeplearndata_free_datasets(deeplearn * learner)
{
    /* free training samples */
    deeplearndata_meta * training_sample = learner->training_data;
    deeplearndata_meta * prev_training_sample;
    while (training_sample != 0) {
        prev_training_sample = training_sample;
        training_sample = (deeplearndata_meta *)training_sample->next;
        free(prev_training_sample);
    }
    learner->training_data = 0;
    learner->training_data_samples = 0;

    /* free test samples */
    deeplearndata_meta * test_sample = learner->test_data;
    deeplearndata_meta * prev_test_sample;
    while (test_sample != 0) {
        prev_test_sample = test_sample;
        test_sample = (deeplearndata_meta *)test_sample->next;
        free(prev_test_sample);
    }
    learner->test_data = 0;
    learner->test_data_samples = 0;
}

/**
* @brief Adds a sample to the training set
* @param learner Deep learner object
* @param sample The data sample to be added
* @returns zero on success
*/
int deeplearndata_add_training_sample(deeplearn * learner, deeplearndata * sample)
{
    deeplearndata_meta * data;

    if (sample == 0) {
        return -1;
    }

    data = (deeplearndata_meta*)malloc(sizeof(deeplearndata_meta));
    if (!data) {
        return -2;
    }

    data->sample = sample;
    data->prev = 0;
    data->next = 0;
    if (learner->training_data) {
        learner->training_data->prev = (struct deeplearndata_meta *)data;
        data->next = (struct deeplearndata_meta *)learner->training_data;
    }
    learner->training_data = data;
    learner->training_data_samples++;
    return 0;
}

/**
* @brief Adds a sample to the test set
* @param learner Deep learner object
* @param sample The data sample to be added
* @returns zero on success
*/
int deeplearndata_add_test_sample(deeplearn * learner, deeplearndata * sample)
{
    deeplearndata_meta * data;

    if (sample == 0) {
        return -1;
    }

    data = (deeplearndata_meta*)malloc(sizeof(deeplearndata_meta));
    if (!data) {
        return -2;
    }

    data->sample = sample;
    data->prev = 0;
    data->next = 0;
    if (learner->test_data) {
        learner->test_data->prev = (struct deeplearndata_meta *)data;
        data->next = (struct deeplearndata_meta *)learner->test_data;
    }
    learner->test_data = data;
    learner->test_data_samples++;
    return 0;
}

/**
* @brief Creates training and test sets from the data samples
* @param learner Deep learner object
* @param test_data_percentage The percentage of samples to be used for testing
* @returns zero on success
*/
int deeplearndata_create_datasets(deeplearn * learner, int test_data_percentage)
{
    int training_samples = learner->data_samples * (100-test_data_percentage) / 100;
    int index, retval;
    deeplearndata * sample;
    
    if (learner->data == 0) {
        return -1;
    }
    deeplearndata_clear_flags(learner);
    deeplearndata_free_datasets(learner);

    /* create training samples */
    while (learner->training_data_samples < training_samples) {
        index = rand_num(&learner->net->random_seed)%learner->data_samples;
        sample = deeplearndata_get(learner, index);
        if (!sample) return -1;
        if (sample->flags == 0) {
            sample->flags = 1;
            retval =
              deeplearndata_add_training_sample(learner, sample);
            if (retval != 0) {
                return -200 + retval;
            }
        }
    }

    /* create test samples */
    sample = learner->data;
    while (sample != 0) {
        if (sample->flags == 0) {
            retval =
              deeplearndata_add_test_sample(learner, sample);
            if (retval != 0) {
                return -300 + retval;
            }
        }
        sample = (deeplearndata*)sample->next;
    }

    return 0;
}

/**
* @brief Loads a data set from a csv file and creates a deep learner
* @param filename csv filename
* @param learner Deep learner object
* @param no_of_hiddens The number of hidden units per layer
* @param hidden layers The number of hidden layers
* @param no_of_outputs The number of outputs
* @param output_field_index Field numbers for the outputs within the csv file
* @param output_classes The number of output classes if the output in the 
*        data set is a single integer value
* @param error_threshold Training error thresholds for each hidden layer
* @param random_seed Random number seed
* @returns The number of data samples loaded
*/
int deeplearndata_read_csv(char * filename,
                           deeplearn * learner,
                           int no_of_hiddens, int hidden_layers,
                           int no_of_outputs, int * output_field_index,
                           int output_classes,
                           float error_threshold[],
                           unsigned int * random_seed)
{
    int i, j, k, field_number, input_index, ctr, samples_loaded = 0;
    FILE * fp;
    char line[2000],valuestr[256],*retval;
    float value;
    int data_set_index = 0;
    float inputs[2048], outputs[1024];
    int fields_per_example = 0;
    int network_outputs = no_of_outputs;

    if (output_classes > 0) {
        network_outputs = output_classes;
    }
    
    fp = fopen(filename,"r");
    if (!fp) return -1;

    while (!feof(fp)) {
        retval = fgets(line,1999,fp);
        if (retval) {
            if (strlen(line)>0) {
                if ((line[0]!='"') && (line[0]!='#')) {
                    field_number = 0;
                    input_index = 0;
                    ctr = 0;
                    for (i = 0; i < strlen(line); i++) {
                        if ((line[i]==',') || (line[i]==';') ||
                            (i==strlen(line)-1)) {
                            if (i==strlen(line)-1) {
                                valuestr[ctr++]=line[i];
                            }
                            valuestr[ctr]=0;
                            ctr=0;

                            /* get the value from the string */
                            value = 0;
                            if (valuestr[0]!='?') {
                                if ((valuestr[0]>='0') &&
                                    (valuestr[0]<='9')) {
                                    value = atof(valuestr);
                                }
                            }

                            for (j = 0; j < no_of_outputs; j++) {
                                if (field_number == output_field_index[j]) {
                                    if (j < 1023) {
                                        if (output_classes <= 0) {
                                            outputs[j] = value;
                                        }
                                        else {
                                            /* for a class number */
                                            for (k = 0; k < network_outputs; k++) {
                                                if (k != (int)value) {
                                                    outputs[k] = 0.25f;
                                                }
                                                else {
                                                    outputs[k] = 0.75f;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                            if ((j == no_of_outputs) && (input_index < 2047)) {
                                inputs[input_index++] = value;
                            }
                                                       
                            field_number++;
                            data_set_index++;
                        }
                        else {
                            /* update the value string */
                            valuestr[ctr++] = line[i];
                        }
                    }
                    if (fields_per_example == 0) {
                        fields_per_example = field_number;
                    }
                    if (samples_loaded == 0) {
                        /* create the deep learner */
                        deeplearn_init(learner,
                                       input_index, no_of_hiddens,
                                       hidden_layers, network_outputs,
                                       error_threshold, random_seed);
                    }
                    /* add a data sample */
                    if (deeplearndata_add(learner, inputs, outputs) != 0) {
                        fclose(fp);
                        return -2;
                    }
                    samples_loaded++;
                }
            }
        }
    }

    fclose(fp);

    /* create training and test data sets */
    if (deeplearndata_create_datasets(learner, 20) != 0) {
        return -3;
    }

    return samples_loaded;
}

/**
* @brief Performs a single training step
* @param learner Deep learner object
* @returns 1=pretraining,2=final training,0=training complete,-1=no training data
*/
int deeplearndata_training(deeplearn * learner)
{
    if (learner->training_data_samples == 0) {
        return -1;
    }

    /* plot a graph showing training progress */
    if (learner->training_ctr > learner->history_plot_interval) {
        if (strlen(learner->history_plot_filename) > 0) {
            deeplearn_plot_history(learner,
                                   learner->history_plot_filename,
                                   learner->history_plot_title,
                                   1024, 480);
        }
        learner->training_ctr = 0;
    }
    learner->training_ctr++;

    /* index number of a random training sample */
    int index = rand_num(&learner->net->random_seed)%learner->training_data_samples;
    /* get the sample */
    deeplearndata * sample = deeplearndata_get_training(learner, index);

    if (learner->current_hidden_layer < learner->net->HiddenLayers) {
        deeplearn_set_inputs(learner, sample);
        deeplearn_update(learner);
        return 1;
    }
    if (learner->training_complete == 0) {
        deeplearn_set_inputs(learner, sample);
        deeplearn_set_outputs(learner, sample);
        deeplearn_update(learner);
        return 2;
    }
    return 0;
}

/**
* @brief Returns the performance on the test data set as a percentage value
* @param learner Deep learner object
* @param data_set An array containing all the data
* @param data_set_size The number of entries in the data set
* @return Training or test performance on the given data, in the range 0 to 100%
*/
float deeplearndata_get_performance(deeplearn * learner)
{
    int index,i,hits=0;
    float error_percent, total_error=0, average_error;
    float * outputs = (float*)malloc(learner->net->NoOfOutputs*sizeof(float));

    for (index = 0; index < learner->test_data_samples; index++) {
        deeplearndata * sample = deeplearndata_get_training(learner, index);
        deeplearn_set_inputs(learner, sample);
        deeplearn_feed_forward(learner);
        deeplearn_get_outputs(learner, outputs);

        for (i = 0; i < learner->net->NoOfOutputs; i++) {
            if (sample->outputs[i] != 0) {
                error_percent = (sample->outputs[i] - outputs[i]) / sample->outputs[i];
                total_error += error_percent*error_percent;
                hits++;
            }
        }
    }
    if (hits > 0) {
        average_error = (float)sqrt(total_error / hits) * 100;
        if (average_error > 100) average_error = 100;
        free(outputs);
        return 100 - average_error;
    }
    free(outputs);
    return 0;
}
