/**
 * @file output.c
 * @brief This file contains the implementation of queries output related functions.
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

#include "IO/output.h"
#include "utils/utils.h"

#include <stdlib.h>
#include <stdio.h>


void output_query(FILE* output_file, void* output, int query_id) {

    if (output == NULL){
        return;
    }

    static output_query_func output_queries[] = {
        output_query1, output_query2, output_query3,
        output_query4, output_query5, output_query6,
        output_query7, output_query8, output_query9,
        output_query10, output_query1F, output_query2F, output_query3F,
        output_query4F, output_query5F, output_query6F, output_query7F,
        output_query8F, output_query9F, output_query10F};

    output_queries[query_id - 1](output_file, output);
}

void output_query1(FILE* file, void* output){
    char** result = (char**) output;
    for (int i = 0; result[i] != NULL; i++) {
        fprintf(file, "%s", result[i]);

        if (result[i + 1] != NULL) {
            fprintf(file, ";");
        }
    }
}

void output_query1F(FILE* file, void* output){
    char** result = (char**) output;
    fprintf(file,"--- 1 ---\n");
    fprintf(file,"name: %s\n", result[0]);
    fprintf(file,"sex: %s\n", result[1]);
    fprintf(file,"country_code: %s\n", result[2]);
    fprintf(file,"passport: %s\n", result[3]);
    fprintf(file,"number_of_flights: %s\n", result[4]);
    fprintf(file,"number_of_reservations: %s\n", result[5]);
    fprintf(file,"total_spent: %s\n", result[6]);
}

void output_query2(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query2F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query3(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query3F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query4(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query4F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query5(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query5F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query6(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query6F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query7(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query7F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query8(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query8F(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query9(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length; i++) {
        if (result_array[i] != NULL) {
            fprintf(file, "%s", result_array[i]);
        } else {
            break;
        }
    }
}

void output_query9F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 1; i < length + 1; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i);
        if(token != NULL) fprintf(file, "id: %s\n", token);
        token = strtok(NULL, ";");
        if(token != NULL) fprintf(file, "name: %s\n", token);
    }
}

void output_query10(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query10F(FILE* file, void* output){
    (void) file;
    (void) output;
}

