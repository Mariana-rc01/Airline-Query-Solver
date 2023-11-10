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

#include <stdlib.h>
#include <stdio.h>


void output_query(FILE* output_file, void* output, char query_id) {

  if (output == NULL){
    return;
  }

  static output_query_func output_queries[] = {
      output_query1, output_query2, output_query3,
      output_query4, output_query5, output_query6,
      output_query7, output_query8, output_query9,
      output_query10};

  output_queries[query_id - '1'](output_file, output);
}

void output_query1(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query2(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query3(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query4(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query5(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query6(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query7(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query8(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query9(FILE* file, void* output){
    (void) file;
    (void) output;
}

void output_query10(FILE* file, void* output){
    (void) file;
    (void) output;
}

