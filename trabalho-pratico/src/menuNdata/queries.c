/**
 * @file queries.c
 * @brief File that contains the struct and implementation of queries.
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
#include "menuNdata/queries.h"
#include "catalogs/manager_c.h"
#include "menuNdata/statistics.h"
#include "utils/utils.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* parser_query(MANAGER catalog, STATS stats, char* line){
    char** query_args = malloc(sizeof(char*) * MAX_ARGS);

    char* token = strtok(line, " ");
    int query;
    if (line[1] == '0') query = 10;
    else query = line[0] - '0';
    int i = 0;
    //char* temp;
    /*while (token != NULL) {
        if (token[0] == '"') {
            do {
                temp = strdup(token);
                token = strtok(NULL, " ");
                temp = (char *) realloc(temp, sizeof(query_args[i]) + sizeof(token) + 3);
                query_args[i] = strcat(temp, " ");
                query_args[i] = strcat(temp, token);
            } while (token != NULL && token[strlen(token) - 1] != '"');
            removeQuotes(temp);
            query_args[i] = temp;
            i++;
        } else {
            query_args[i] = token;
            i++;
        }

        token = strtok(NULL, " ");
    }
    */

    while (token != NULL) {
        token = strtok(NULL, " ");
        query_args[i] = token;
        i++;
    }

    static queries_func queries[] = {query1, query2, query3,
                                    query4, query5, query6,
                                    query7, query8, query9, query10};

    void* result = queries[query - 1](catalog, stats, query_args);

    free(query_args);

    return result;
}

void* query1(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query2(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query3(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query4(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query5(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query6(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query7(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query8(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query9(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query10(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void free_query(void* result, char query_id){

    static free_queries_func queries[] = {free_query1, free_query2, free_query3,
                                        free_query4, free_query5, free_query6,
                                        free_query7, free_query8, free_query9, free_query10};

    queries[query_id - '1'](result);
}

void free_query1(void* result){
    (void) result;
}

void free_query2(void* result){
    (void) result;
}

void free_query3(void* result){
    (void) result;
}

void free_query4(void* result){
    (void) result;
}

void free_query5(void* result){
    (void) result;
}

void free_query6(void* result){
    (void) result;
}

void free_query7(void* result){
    (void) result;
}

void free_query8(void* result){
    (void) result;
}

void free_query9(void* result){
    (void) result;
}

void free_query10(void* result){
    (void) result;
}

