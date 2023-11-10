/**
 * @file interpreter.c
 * @brief Contains the code related to interpreting the file with the queries
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void divideInToArguments(char* line) {
    char *arguments[50]; 
    int i = 0; 
    char *token = strtok(line, " ");
    
    while (token != NULL) {
        if (token[0] == '"') {
            arguments[i] = token;
            token = strtok(NULL, " ");
            strcat(arguments[i], " ");
            strcat(arguments[i], token); 
            removeQuotationMarks(arguments[i]);
            i++;
        } 
        else{
            arguments[i] = token; 
            i++;
        }
        token = strtok(NULL, " ");
    }
}

void removeQuotationMarks(char* s) {
    s[strlen(s) - 1] = '\0';
    for(int i = 0; s[i]!= NULL; i++) {
        s[i] = s[i+1];
    }
}


void interpreter(FILE queries_file) {
    char *query = NULL;
    size_t lsize = 0;
    int isField;
    char** arguments;
    int query_n;
    while(getline(&query,&lsize, queries_file)) {
        query[strlen(query)-1] = '\0';
        divideInToArguments(arguments);
        if(strchr(arguments[0], 'F') != NULL) {isField = 1; arguments[0][strlen(arguments[0])-1] = '\0';}
        else {isField = 0;}
        if(arguments[0] == '1') {query_1(isField, &arguments[1]);}
        if(arguments[0] == '2') {query_2(isField, &arguments[1]);}
        if(arguments[0] == '3') {query_3(isField, &arguments[1]);}
        if(arguments[0] == '4') {query_4(isField, &arguments[1]);}
        if(arguments[0] == '5') {query_5(isField, &arguments[1]);}
        if(arguments[0] == '6') {query_6(isField, &arguments[1]);}
        if(arguments[0] == '7') {query_7(isField, &arguments[1]);}
        if(arguments[0] == '8') {query_8(isField, &arguments[1]);}
        if(arguments[0] == '9') {query_9(isField, &arguments[1]);}
        if(arguments[0] == '10') {query_10(isField, &arguments[1]);}
    }
}
