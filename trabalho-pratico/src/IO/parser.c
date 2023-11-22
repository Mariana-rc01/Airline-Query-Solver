/**
 * @file parser.c
 * @brief Module that parses any given file
 */

/*
 *   Copyright 2023  Hugo Abelheira, Luís França, Mariana Rocha
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
*/

#include "IO/parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parseF (FILE* f, int max_fields, void_function func, void *catalog, FILE* error_f){
    int verify = 0;
    char* line = NULL;
    size_t lsize = 0;

    // Check if file is opened successfully
    if (f == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    // Write first line of the error csv
    if (getline(&line, &lsize, f) != -1) {
        fprintf(error_f, "%s", line);
    } else {
        fprintf(stderr, "Error reading first line from file\n");
        free(line);
        return;
    }

    while(getline(&line,&lsize,f) != -1){
        // Replace \n for \0
        line[strlen(line)-1] = '\0';
        char* temp;
        temp = strdup(line);

        char **fields = parseL(line, max_fields);
        verify = func(fields,catalog);

        if (verify == 0) {
            fprintf(error_f,"%s\n",temp);
        }
        free(temp);
        free(fields);
    }
    free(line);
}

char** parseL(char* line, int max_fields) {
    // Allocate memory for the array of fields
    char** fields = malloc(sizeof(char*) * max_fields);
    char* temp = strstr(line, ";");
    char* field = NULL;

    int i;
    // Iterate through the line, extracting fields using the delimiter
    for (i = 0; temp != NULL; (temp = strstr(line, ";")), i++) {
        // Check if the field is not the beginning of the line
        field = temp != line ? line : NULL;

        // Store the field in the array
        fields[i] = field;
        line = temp + 1;
        *temp = '\0';
    }

    // Handle the last field after the last delimiter
    field = line;
    fields[i] = field;

    return fields;
}

