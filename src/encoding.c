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

#include "encoding.h"

/**
* @brief Encodes text into binary input values
* @param text The text string to be encoded
* @param inputs Array of input neurons
* @param no_of_inputs The number of input neurons
* @param offset The index of the input neuron to begin inserting the text
* @param max_field_length_chars The maximum length of a text field in characters
* @returns current inputs index
*/
int enc_text_to_binary(char * text,
                       bp_neuron ** inputs, int no_of_inputs,
                       int offset,
                       int max_field_length_chars)
{
    int pos = offset, i, bit, max_chars = strlen(text);

    if (max_chars > (no_of_inputs-offset)/CHAR_BITS) {
        max_chars = ((no_of_inputs-offset)/CHAR_BITS);
    }
    if (max_chars > max_field_length_chars) {
        max_chars = max_field_length_chars;
    }

    /* for each character in the string */
    for (i = 0; i < max_chars; i++) {
        /* set the bits for this character */
        for (bit = 0; bit < CHAR_BITS; bit++, pos++) {
            if (text[i] & (1<<bit)) {
                inputs[pos]->value = 0.75f;
            }
            else {
                inputs[pos]->value = 0.25f;
            }
        }
    }
    /* set the remaining inputs within the field to neutral */
    while (i < max_field_length_chars) {
        for (bit = 0; bit < CHAR_BITS; bit++) {
            if (pos >= no_of_inputs) {
                i = max_field_length_chars;
                break;
            }
            inputs[pos++]->value = 0.5f;
        }
        i++;
    }
    return pos;
}
