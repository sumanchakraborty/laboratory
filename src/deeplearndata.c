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
