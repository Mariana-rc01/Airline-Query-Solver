/**
 * @file interpreter.c
 * @brief Module for parsing and executing queries from an input file
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

#include "IO/interpreter.h"

#include <time.h>
#include <stdio.h>

void* parser_query(MANAGER catalog,char* line){
    int i = 0;
    char** args = malloc(sizeof(char*) * MAX_ARGS);
    char* copy = strdup(line);
    char* token = strtok(copy, " ");

    while (token != NULL && i < MAX_ARGS) {
        if (token[0] == '"') {
            char temp[100];
            strcpy(temp, token);
            removeQuotes(temp);

            token = strtok(NULL,"\"");
            char* temp1;
            if (temp[strlen(temp)-2] == '\"') {
                temp[strlen(temp)-2] = '\0';
                temp1 = strdup(temp);
            }
            else temp1 = concat(temp,token);
            args[i] = temp1;
            i++;
        } else {
            args[i] = strdup(token);
            i++;
        }

        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    free(copy);
    if (token != NULL) free(token);

    int query;
    if(args[0][1] != '0') query = args[0][0] - '0';
    else query = 10;

    static queries_func queries[] = {query1, query2, query3,
                                    query4, query5, query6,
                                    query7, query8, query9, query10};

    void* result = queries[query-1](catalog, args+1);

    for (int k = 0; k < i; k++) free(args[k]);

    free(args);

    return result;
}

int execute_queries(MANAGER manager_catalog, char* path2, int flag){

    char *line = NULL;
    size_t lsize = 0;
    int cmd_n = 1;
    void* result;

    FILE* queries_file = fopen(path2, "r");
    FILE* output_file;
    struct timespec start, end;
    double elapsed;
    FILE* analysis_file = fopen("Resultados/analysis.txt", "w");

    while(getline(&line,&lsize, queries_file) != -1){
        int query_id;
        line[strlen(line)-1] = '\0';
        if (flag == 1){
            clock_gettime(CLOCK_REALTIME, &start);
        }
        result = parser_query(manager_catalog, line);
        if (flag == 1){
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            fprintf(analysis_file, "Query: %s\n",line);
            fprintf(analysis_file,"Elapsed time: %.6f seconds\n\n", elapsed);
        }
        output_file = create_output_file(cmd_n);
        if (output_file == NULL) return -1;

        if(line[1] == ' ') query_id = line[0] - '0';
        else if (line[1] == 'F') {query_id = (line[0] - '0') + 10;}
        else if (line[2] == 'F' && line[1] == '0') query_id = 20;
        else query_id = 10;

        if(result != NULL){
            output_query(output_file, result, query_id);
            if (query_id > 10){
                free_query(result, query_id-10);
            }
            else free_query(result,query_id);
        }
        fclose(output_file);
        cmd_n++;
    }
    free(line);
    fclose(queries_file);
    fclose(analysis_file);
    return cmd_n;
}
