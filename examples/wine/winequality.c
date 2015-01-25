/*
 Estimating wine quality
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

#include <stdio.h>
#include "libdeep/globals.h"
#include "libdeep/deeplearn.h"

#define TITLE     "Red Wine Quality Training"
#define DATA_FILE "winequality-red.csv"

#define MAX_EXAMPLES      1600
#define MAX_TEST_EXAMPLES ((MAX_EXAMPLES) * 20 / 100)
#define MAX_FIELDS        16

float data_max_value[MAX_FIELDS];
float data_min_value[MAX_FIELDS];
float data_set[MAX_EXAMPLES*MAX_FIELDS];
float test_data[MAX_TEST_EXAMPLES*MAX_FIELDS];
float * current_data_set;

int no_of_examples = 0;
int no_of_test_examples = 0;
int fields_per_example = 0;
int no_of_inputs = 0;

deeplearn learner;

/**
* @brief create a test data set from the original data.
*        The test data can be used to calculate a final fitness
*        value, because it was not seen during training and so
*        provides an indication of how well the system has generalised
* @param data_set Array storing the full data set
* @param no_of_training_examples Returned number of training examples
* @param fields_per_example Number of fields for each entry
* @param test_data Array storing the test data
* @return The number of test examples
*/
static int create_test_data(float * data_set,
                            int * no_of_training_examples,
                            int fields_per_example,
                            float * test_data)
{
    int i,j,index;
    int no_of_test_examples = 0;
    unsigned int random_seed = (unsigned int)time(NULL);

    for (i = 0; i < MAX_TEST_EXAMPLES; i++) {
        /* pick an example from the loaded data set */
        index = rand_num(&random_seed)%(*no_of_training_examples);

        /* increase the number of test examples */
        for (j = 0; j < fields_per_example; j++) {
            test_data[no_of_test_examples*fields_per_example + j] =
                data_set[index*fields_per_example + j];
        }
        no_of_test_examples++;

        /* reshuffle the original data set */
        for (j = index+1; j < (*no_of_training_examples); j++) {
            data_set[(j-1)*fields_per_example + j] =
                data_set[j*fields_per_example + j];
        }
        /* decrease the number of training data examples */
        *no_of_training_examples = *no_of_training_examples - 1;
    }

    return no_of_test_examples;
}


/**
* @brief Load the data set from file and store it within an array
* @param filename File to load data from
* @param data_set Array within which to store the training data
* @param max_examples Maximum number of training examples
* @param fields_per_example Number of fields in each entry
* @return The number of training examples loaded
*/
static int load_data(char * filename, float * data_set,
                     int max_examples,
                     int * fields_per_example)
{
    int i, field_number, ctr, examples_loaded = 0;
    FILE * fp;
    char line[2000],valuestr[256],*retval;
    float value;
    int data_set_index = 0;

    for (i = 0; i < MAX_FIELDS; i++) {
        data_min_value[i] = 9999;
        data_max_value[i] = -9999;
    }

    fp = fopen(filename,"r");
    if (!fp) return 0;

    while (!feof(fp)) {
        retval = fgets(line,1999,fp);
        if (retval) {
            if (strlen(line)>0) {
                if (line[0]!='"') {
                    field_number = 0;
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
                                if (valuestr[0] == 'M') {
                                    value = 0.8f;
                                }
                                if (valuestr[0] == 'B') {
                                    value = 0.2f;
                                }
                            }

                            /* insert value into the array */
                            data_set[data_set_index] = value;
                            if (value > data_max_value[field_number]) {
                                data_max_value[field_number] = value;
                            }
                            if (value < data_min_value[field_number]) {
                                data_min_value[field_number] = value;
                            }
                            field_number++;
                            data_set_index++;
                        }
                        else {
                            /* update the value string */
                            valuestr[ctr++] = line[i];
                        }
                    }
                    *fields_per_example = field_number;
                    examples_loaded++;
                    if (examples_loaded >= max_examples) {
                        fclose(fp);
                        return examples_loaded;
                    }
                }
            }
        }
    }

    fclose(fp);

    return examples_loaded;
}

/**
* @brief returns a normalised version of a value suitable for inserting
*        into a neuron value
* @param field_number Field number within the data
* @param value Value to be normalised
* @return normalised value in the range 0.25 to 0.75
*/
float data_to_neuron_value(int field_number,
                           float value)
{
    float range =
        data_max_value[field_number] -
        data_min_value[field_number];

    if (range > 0) {
        return 0.25f +
            ((value - data_min_value[field_number])*0.5f/range);
    }
    return 0.5f;
}

/**
* @brief converts a neuron value into a data value within the expected range
* @param field_number The field index within the data
* @param neuron_value The value of the neuron in the range 0.0 to 1.0,
*        but with an effective linear range of 0.25 to 0.75
* @return Value mapped back into the expected range
*/
float neuron_value_to_data(int field_number,
                           float neuron_value)
{
    float range =
        data_max_value[field_number] -
        data_min_value[field_number];

    if (range > 0) {
        return data_min_value[field_number] +
            (((neuron_value - 0.25f)/0.75f)*range);
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
float get_performance(deeplearn * learner,
                      float * data_set, int data_set_size)
{
    int index,i,hits=0;
    float reference, v, error_percent, total_error=0, average_error;

    for (index = 0; index < data_set_size; index++) {
        /* load the data set inputs into the network inputs */
        for (i = 0; i < fields_per_example-1; i++) {
            v = data_set[index*fields_per_example + i];
            v = data_to_neuron_value(i, v);
            deeplearn_set_input(learner, i, v);
        }

        deeplearn_feed_forward(learner);

        reference = data_set[index*fields_per_example + fields_per_example - 1];
        v = neuron_value_to_data(fields_per_example - 1, deeplearn_get_output(learner,0));
        if (reference != 0) {
            error_percent = (v-reference)/reference;
            total_error += error_percent*error_percent;
            hits++;
        }
    }
    if (hits > 0) {
        average_error = (float)sqrt(total_error / hits) * 100;
        if (average_error > 100) average_error = 100;
        return 100 - average_error;
    }
    return 0;
}

/**
* @brief Train the deep learner
*/
static void training()
{
    int no_of_hiddens = 3*3;
    int hidden_layers=3;
    int no_of_outputs=1;
    int itt,i,index;
    unsigned int random_seed = 123;
    char filename[256];
    char title[256];
    char weights_filename[256];
    int weights_image_width = 480;
    int weights_image_height = 800;
    float error_threshold_percent[] = { 1.6f, 0.8f, 0.8f, 11.0f };
    float v;
    const int logging_interval = 40000;

    current_data_set = data_set;

    sprintf(weights_filename,"%s","weights.png");
    sprintf(title, "%s", TITLE);

    /* create the learner */
    deeplearn_init(&learner,
                   no_of_inputs, no_of_hiddens,
                   hidden_layers,
                   no_of_outputs,
                   error_threshold_percent,
                   &random_seed);

    /* set learning rate */
    deeplearn_set_learning_rate(&learner, 0.2f);

    /* set percentage of dropouts */
    deeplearn_set_dropouts(&learner, 0.001f);

    /* perform pre-training with an autocoder */
    itt = 0;
    while (learner.current_hidden_layer < hidden_layers) {
        /* index of the example to be used */
        index = rand_num(&random_seed)%no_of_examples;

        /* load the data set inputs into the network inputs */
        for (i = 0; i < fields_per_example-1; i++) {
            v = current_data_set[index*fields_per_example + i];
            v = data_to_neuron_value(i, v);
            deeplearn_set_input(&learner, i, v);
        }

        /* update the learner */
        deeplearn_update(&learner);

        itt++;
        if ((itt % logging_interval == 0) && (itt>0)) {
            printf("%d: %.5f%%\n",
                   learner.current_hidden_layer, learner.BPerror);

            /* save a graph */
            sprintf(filename,"%s","training_error.png");
            deeplearn_plot_history(&learner,
                                   filename, title,
                                   1024, 480);
            /* plot the weights */
            if ((&learner)->autocoder != 0) {
                bp_plot_weights((&learner)->autocoder,
                                weights_filename,
                                weights_image_width,
                                weights_image_height,
                                0);
            }
        }
    }

    /* save a graph */
    sprintf(filename,"%s","training_error.png");
    deeplearn_plot_history(&learner,
                           filename, title,
                           1024, 480);
    /* plot the weights */
    bp_plot_weights((&learner)->net,
                    weights_filename,
                    weights_image_width,
                    weights_image_height,
                    0);

    /* perform the final training between the last
       hidden layer and the outputs */
    while (learner.training_complete == 0) {
        /* index of the example to be used */
        index = rand_num(&random_seed)%no_of_examples;

        /* load the data set inputs into the network inputs */
        for (i = 0; i < fields_per_example-1; i++) {
            v = current_data_set[index*fields_per_example + i];
            v = data_to_neuron_value(i, v);
            deeplearn_set_input(&learner, i, v);
        }

        /* set the desired outputs */
        v = current_data_set[index*fields_per_example + fields_per_example - 1];
        v = data_to_neuron_value(fields_per_example - 1, v);
        deeplearn_set_output(&learner, 0, v);

        /* update the learner */
        deeplearn_update(&learner);

        itt++;
        if ((itt % logging_interval == 0) && (itt>0)) {
            printf("Final: %.5f  %.2f%%/%.2f%%\n", learner.BPerror,
                   get_performance(&learner,
                                   data_set,no_of_examples),
                   get_performance(&learner,
                                   test_data,no_of_test_examples));

            /* save a graph */
            sprintf(filename,"%s","training_error.png");
            deeplearn_plot_history(&learner,
                                   filename, title,
                                   1024, 480);
            /* plot the weights */
            if ((&learner)->autocoder!=0) {
                bp_plot_weights((&learner)->autocoder,
                                weights_filename,
                                weights_image_width,
                                weights_image_height,
                                0);
            }
        }
    }

    /* save a graph */
    sprintf(filename,"%s","training_error.png");
    deeplearn_plot_history(&learner,
                           filename, title,
                           1024, 480);
    /* plot the weights */
    bp_plot_weights((&learner)->net,
                    weights_filename,
                    weights_image_width,
                    weights_image_height,
                    0);

    printf("Training performance: %.4f%%/nTest Performance: %.4f%%\n",
           get_performance(&learner,data_set,no_of_examples),
           get_performance(&learner,test_data,no_of_test_examples));
}


/**
* @brief Main function
*/
int main(int argc, char* argv[])
{
    /* load the data */
    printf("Loading data set\n");
    no_of_examples =
        load_data(DATA_FILE,
                  data_set, MAX_EXAMPLES,
                  &fields_per_example);

    /* create a test data set */
    printf("Creating test data set\n");
    no_of_test_examples =
        create_test_data(data_set,
                         &no_of_examples,
                         fields_per_example,
                         test_data);

    no_of_inputs = fields_per_example-1;

    printf("Number of training examples: %d\n",no_of_examples);
    printf("Number of test examples: %d\n",no_of_test_examples);
    printf("Number of fields: %d\n",fields_per_example);

    training();

    return 1;
}
