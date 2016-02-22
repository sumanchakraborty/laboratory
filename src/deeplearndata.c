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
* @param datalist The list to be added to
* @param data_samples The number of data samples in the list
* @param inputs Input data
* @param outputs Output data
* @param no_of_input_fields The number of input fields
* @param no_of_outputs The number of output fields
* @param input_range_min Minimum value for each input field
* @param input_range_max Maximum value for each input field
* @param output_range_min Minimum value for each output field
* @param output_range_max Maximum value for each output field
* @returns 0 on success
*/
int deeplearndata_add(deeplearndata ** datalist,
                      int data_samples[],
                      float inputs[],
                      char ** inputs_text,
                      float outputs[],
                      int no_of_input_fields,
                      int no_of_outputs,
                      float input_range_min[],
                      float input_range_max[],
                      float output_range_min[],
                      float output_range_max[])
{
    int i;
    deeplearndata * data;
    data = (deeplearndata*)malloc(sizeof(deeplearndata));
    if (!data) {
        return -1;
    }

    /* create arrays to store the data */
    data->inputs =
      (float*)malloc(no_of_input_fields*sizeof(float));
    if (!data->inputs) {
        return -2;
    }
    data->inputs_text = 0;
    if (inputs_text != 0) {
        data->inputs_text =
            (char**)malloc(no_of_input_fields*sizeof(char*));
        for (i = 0; i < no_of_input_fields; i++) {
            data->inputs_text[i] = 0;
            if (inputs_text[i] != 0) {
                /* copy the string */
                data->inputs_text[i] =
                    (char*)malloc((strlen(inputs_text[i])+1)*sizeof(char));
                strcpy(data->inputs_text[i], inputs_text[i]);
            }
        }
    }
    data->outputs =
      (float*)malloc(no_of_outputs*sizeof(float));
    if (!data->outputs) {
        return -3;
    }

    /* copy the data */
    memcpy((void*)data->inputs, inputs, no_of_input_fields*sizeof(float));
    memcpy((void*)data->outputs, outputs, no_of_outputs*sizeof(float));

    /* update the data range */
    for (i = 0; i < no_of_input_fields; i++) {
        if (inputs[i] < input_range_min[i]) {
            input_range_min[i] = inputs[i];
        }
        if (inputs[i] > input_range_max[i]) {
            input_range_max[i] = inputs[i];
        }
    }
    data->labeled = 1;
    for (i = 0; i < no_of_outputs; i++) {
        if ((int)outputs[i] != DEEPLEARN_UNKNOWN_VALUE) {
            if (outputs[i] < output_range_min[i]) {
                output_range_min[i] = outputs[i];
            }
            if (outputs[i] > output_range_max[i]) {
                output_range_max[i] = outputs[i];
            }
        }
        else {
            data->labeled = 0;
        }
    }

    data->flags = 0;

    /* change the current head of the list */
    data->prev = 0;
    data->next = 0;
    if (*datalist) {
        (*datalist)->prev = (struct deeplearndata *)data;
        data->next = (struct deeplearndata *)(*datalist);
    }
    *datalist = data;
    *data_samples = *data_samples + 1;

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
* @brief Returns a labeled training data sample
* @param learner Deep learner object
* @returns deeplearndata object
*/
deeplearndata * deeplearndata_get_training_labeled(deeplearn * learner, int index)
{
    if ((index < 0) || (index >= learner->training_data_labeled_samples)) {
        return 0;
    }
    deeplearndata_meta * meta = deeplearndata_get_meta(learner->training_data_labeled, index);
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

    /* free labeled training samples */
    deeplearndata_meta * training_sample_labeled = learner->training_data_labeled;
    deeplearndata_meta * prev_training_sample_labeled;
    while (training_sample_labeled != 0) {
        prev_training_sample_labeled = training_sample_labeled;
        training_sample_labeled = (deeplearndata_meta *)training_sample_labeled->next;
        free(prev_training_sample_labeled);
    }
    learner->training_data_labeled = 0;
    learner->training_data_labeled_samples = 0;

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
* @brief Adds a labeled sample to the training set
* @param learner Deep learner object
* @param sample The data sample to be added
* @returns zero on success
*/
int deeplearndata_add_labeled_training_sample(deeplearn * learner, deeplearndata * sample)
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
    if (learner->training_data_labeled) {
        learner->training_data_labeled->prev = (struct deeplearndata_meta *)data;
        data->next = (struct deeplearndata_meta *)learner->training_data_labeled;
    }
    learner->training_data_labeled = data;
    learner->training_data_labeled_samples++;
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
            if (sample->labeled != 0) {
                retval =
                    deeplearndata_add_labeled_training_sample(learner, sample);
                if (retval != 0) {
                    return -300 + retval;
                }
            }
        }
    }

    /* create test samples */
    sample = learner->data;
    while (sample != 0) {
        if (sample->flags == 0) {
            if (sample->labeled != 0) {
                retval =
                    deeplearndata_add_test_sample(learner, sample);
                if (retval != 0) {
                    return -400 + retval;
                }
            }
            else {
                retval =
                    deeplearndata_add_training_sample(learner, sample);
                if (retval != 0) {
                    return -500 + retval;
                }
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
    char line[2000],valuestr[DEEPLEARN_MAX_FIELD_LENGTH_CHARS],*retval;
    float value;
    int data_set_index = 0;
    int no_of_inputs = 0;
    int no_of_input_fields = 0;
    float inputs[DEEPLEARN_MAX_CSV_INPUTS];
    char* inputs_text[DEEPLEARN_MAX_CSV_INPUTS];
    float outputs[DEEPLEARN_MAX_CSV_OUTPUTS];
    int fields_per_example = 0;
    int network_outputs = no_of_outputs;
    int is_text;
    deeplearndata * data = 0;
    int data_samples = 0;
    float input_range_min[DEEPLEARN_MAX_CSV_INPUTS];
    float input_range_max[DEEPLEARN_MAX_CSV_INPUTS];
    float output_range_min[DEEPLEARN_MAX_CSV_OUTPUTS];
    float output_range_max[DEEPLEARN_MAX_CSV_OUTPUTS];
    int field_length[DEEPLEARN_MAX_CSV_INPUTS];

    for (i = 0; i < DEEPLEARN_MAX_CSV_INPUTS; i++) {
        input_range_min[i] = 9999;
        input_range_max[i] = -9999;
        inputs_text[i] = 0;
    }
    for (i = 0; i < DEEPLEARN_MAX_CSV_OUTPUTS; i++) {
        output_range_min[i] = 9999;
        output_range_max[i] = -9999;
    }

    if (output_classes > 0) {
        network_outputs = output_classes;
    }
    for (i = 0; i < network_outputs; i++) {
        outputs[i] = DEEPLEARN_UNKNOWN_VALUE;
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
                                if (ctr < DEEPLEARN_MAX_FIELD_LENGTH_CHARS-1) {
                                    valuestr[ctr++]=line[i];
                                }
                            }
                            valuestr[ctr]=0;
                            ctr=0;

                            /* get the value from the string */
                            value = 0;
                            is_text = 0;
                            if ((valuestr[0]!='?') && (valuestr[0]!=10)) {
                                /* positive numbers*/
                                if (((valuestr[0]>='0') &&
                                     (valuestr[0]<='9')) ||
                                    /* negative numbers*/
                                    ((valuestr[0]=='-') &&
                                     (valuestr[1]>='0') &&
                                     (valuestr[1]<='9'))) {
                                    value = atof(valuestr);
                                }
                                else {
                                    is_text = 1;
                                }
                            }

                            for (j = 0; j < no_of_outputs; j++) {
                                if (field_number == output_field_index[j]) {
                                    if (j < DEEPLEARN_MAX_CSV_OUTPUTS-1) {
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
                            if ((j == no_of_outputs) && (input_index < DEEPLEARN_MAX_CSV_INPUTS-1)) {
                                inputs_text[input_index] = 0;
                                if (is_text != 0) {
                                    /* allocate some memory for the string */
                                    inputs_text[input_index] =
                                        (char*)malloc((strlen(valuestr)+1)*sizeof(char));
                                    /* copy it */
                                    strcpy(inputs_text[input_index],(char*)valuestr);
                                }
                                inputs[input_index++] = value;
                            }

                            field_number++;
                            data_set_index++;
                        }
                        else {
                            /* update the value string */
                            if (ctr < DEEPLEARN_MAX_FIELD_LENGTH_CHARS-1) {
                                valuestr[ctr++] = line[i];
                            }
                        }
                    }
                    if (fields_per_example == 0) {
                        fields_per_example = field_number;
                    }
                    if (samples_loaded == 0) {
                        no_of_input_fields = input_index;
                    }
                    /* add a data sample */
                    if (deeplearndata_add(&data,
                                          &data_samples,
                                          inputs, inputs_text,
                                          outputs,
                                          no_of_input_fields,
                                          network_outputs,
                                          input_range_min,
                                          input_range_max,
                                          output_range_min,
                                          output_range_max) != 0) {
                        fclose(fp);
                        return -2;
                    }
                    /* free memory for any text strings */
                    for (i = 0; i < no_of_input_fields; i++) {
                        if (inputs_text[i] != 0) {
                            free(inputs_text[i]);
                            inputs_text[i] = 0;
                        }
                    }
                    for (i = 0; i < network_outputs; i++) {
                        outputs[i] = DEEPLEARN_UNKNOWN_VALUE;
                    }
                    samples_loaded++;
                }
            }
        }
    }

    fclose(fp);

    /* calculate field lengths */
    no_of_inputs =
        deeplearndata_update_field_lengths(no_of_input_fields,
                                           field_length, data);

    /* create the deep learner */
    deeplearn_init(learner,
                   no_of_inputs, no_of_hiddens,
                   hidden_layers, network_outputs,
                   error_threshold, random_seed);

    /* set the input fields */
    learner->no_of_input_fields = no_of_input_fields;
    learner->field_length = (int*)malloc(no_of_input_fields*sizeof(int));
    for (i = 0; i < no_of_input_fields; i++) {
        learner->field_length[i] = field_length[i];
        if (field_length[i] > 0) {
            input_range_min[i] = 0.25f;
            input_range_max[i] = 0.75f;
        }
    }

    /* attach the data samples */
    learner->data = data;
    learner->data_samples = data_samples;

    /* set the field ranges */
    for (i = 0; i < no_of_input_fields; i++) {
        learner->input_range_min[i] = input_range_min[i];
        learner->input_range_max[i] = input_range_max[i];
    }
    for (i = 0; i < network_outputs; i++) {
        learner->output_range_min[i] = output_range_min[i];
        learner->output_range_max[i] = output_range_max[i];
    }

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

    if ((learner->net->HiddenLayers > 1) &&
        (learner->current_hidden_layer < learner->net->HiddenLayers)) {
        /* index number of a random training sample */
        int index = rand_num(&learner->net->random_seed)%learner->training_data_samples;
        /* get the sample */
        deeplearndata * sample = deeplearndata_get_training(learner, index);
        deeplearn_set_inputs(learner, sample);
        deeplearn_update(learner);
        return 1;
    }
    if (learner->training_complete == 0) {
        /* index number of a random training sample */
        int index = rand_num(&learner->net->random_seed)%learner->training_data_labeled_samples;
        /* get the sample */
        deeplearndata * sample = deeplearndata_get_training_labeled(learner, index);
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

/**
* @brief Returns the maximum field length for a text field
* @param data List of data samples
* @param field_index Index number of the input field
* @returns maximum field length in number of input neurons (bits)
*          Zero length indicates a numeric value
*/
int deeplearndata_get_field_length(deeplearndata * data, int field_index)
{
    int max = 0;

    while (data != 0) {
        if (data->inputs_text != 0) {
            if (data->inputs_text[field_index] != 0) {
                if (strlen(data->inputs_text[field_index])*CHAR_BITS > max) {
                    max = strlen(data->inputs_text[field_index])*CHAR_BITS;
                }
            }
        }
        data = (deeplearndata *)data->next;
    }
    return max;
}

/**
* @brief Calculates the field lengths (input neurons per field)
*        Note that a zero field length indicates a numeric value
* @param no_of_input_fields The number of input fields
* @param field_length Array storing the field lengths in input neurons (bits)
* @param data List containing data samples
* @returns The total number of input neurons needed
*/
int deeplearndata_update_field_lengths(int no_of_input_fields,
                                       int field_length[],
                                       deeplearndata * data)
{
    int i, no_of_inputs = 0, length;

    for (i = 0; i < no_of_input_fields; i++) {
        length = deeplearndata_get_field_length(data, i);
        field_length[i] = length;
        if (length < 1) length = 1;
        no_of_inputs += length;
    }
    return no_of_inputs;
}
