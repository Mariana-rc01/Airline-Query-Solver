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
    for (int i = 0; i < 8; i++) {
        if(result[i] == NULL) fprintf(file, "False");
        else if(strcmp(result[i],"T") == 0) fprintf(file, "True");
        else fprintf(file, "%s", result[i]);

        if (i != 7) {
            fprintf(file, ";");
        }
    }
    fprintf(file,"\n");
}

void output_query1F(FILE* file, void* output){
    char** result = (char**) output;
    if (strcmp(result[8],"user") == 0){
        fprintf(file,"--- 1 ---\n");
        fprintf(file,"name: %s\n", result[0]);
        fprintf(file,"sex: %s\n", result[1]);
        fprintf(file,"age: %s\n",result[2]);
        fprintf(file,"country_code: %s\n", result[3]);
        fprintf(file,"passport: %s\n", result[4]);
        fprintf(file,"number_of_flights: %s\n", result[5]);
        fprintf(file,"number_of_reservations: %s\n", result[6]);
        fprintf(file,"total_spent: %s\n", result[7]);
    }
    else if (strcmp(result[8],"flight") == 0){
        fprintf(file,"--- 1 ---\n");
        fprintf(file,"airline: %s\n", result[0]);
        fprintf(file,"plane_model: %s\n", result[1]);
        fprintf(file,"origin: %s\n",result[2]);
        fprintf(file,"destination: %s\n", result[3]);
        fprintf(file,"schedule_departure_date: %s\n", result[4]);
        fprintf(file,"schedule_arrival_date: %s\n", result[5]);
        fprintf(file,"passengers: %s\n", result[6]);
        fprintf(file,"delay: %s\n", result[7]);
    }
    else if (strcmp(result[8],"reservation") == 0){
        fprintf(file,"--- 1 ---\n");
        fprintf(file,"hotel_id: %s\n", result[0]);
        fprintf(file,"hotel_name: %s\n", result[1]);
        fprintf(file,"hotel_stars: %s\n",result[2]);
        fprintf(file,"begin_date: %s\n", result[3]);
        fprintf(file,"end_date: %s\n", result[4]);
        if(result[5] == NULL) fprintf(file,"includes_breakfast: False\n");
        else if(strcmp(result[5],"T") == 0) fprintf(file, "includes_breakfast: True\n");
        else fprintf(file,"includes_breakfast: %s\n", result[5]);
        fprintf(file,"nights: %s\n", result[6]);
        fprintf(file,"total_price: %s\n", result[7]);
    }
}

void output_query2(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    char* type = result_array[1];
    if (!type){
        for (int i = 2; i < length + 2; i++) {
            if (i != (length + 1)) {
                if (result_array[i][0] == 'B'){
                    fprintf(file, "%s;reservation\n", result_array[i]);
                }
                else fprintf(file, "%s;flight\n", result_array[i]);
            }
            else {
                if (result_array[i][0] == 'B'){
                    fprintf(file, "%s;reservation\n", result_array[i]);
                }
                else fprintf(file, "%s;flight\n", result_array[i]);
            }
        }
    }
    else {
        for (int i = 2; i < length + 2; i++) {
            if (i != (length + 1)) {
                fprintf(file, "%s\n", result_array[i]);
            }
            else {
                result_array[i][strlen(result_array[i])] ='\0';
                char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
                fprintf(file,"%s\n",truncatedString);
                free(truncatedString);
            }
        }
        free(type);
    }
}

void output_query2F(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    char* type = result_array[1];
    if (!type){
        for (int i = 2; i < length + 2; i++) {
            char* id = strtok(result_array[i], ";");
            char* dateTime = strtok(NULL, ";");
            fprintf(file, "--- %d ---\n", i-1);
            fprintf(file, "id: %s\n",id);
            fprintf(file,"date: %s\n",dateTime);
            if (i != (length+1)){
                if (id[0] == 'B'){
                    fprintf(file, "type: reservation\n\n");
                }
                else fprintf(file, "type: flight\n\n");
            }
            else {
                if (id[0] == 'B'){
                    fprintf(file, "type: reservation\n");
                }
                else fprintf(file, "type: flight\n");
            }
        }
    }
    else {
        for (int i = 2; i < length + 2; i++) {
            char* id = strtok(result_array[i], ";");
            char* dateTime = strtok(NULL, ";");
            fprintf(file, "--- %d ---\n", i-1);
            fprintf(file, "id: %s\n",id);
            if (i != (length+1)){
                fprintf(file,"date: %s\n",dateTime);
                fprintf(file,"\n");
            }
            else {
                dateTime[strlen(dateTime)] = '\0';
                char *truncatedString = strndup(dateTime, strlen(dateTime));
                fprintf(file,"date: %s\n",truncatedString);
                free(truncatedString);
            }
        }
        free(type);
    }
}

void output_query3(FILE* file, void* output){
    char* rating = (char*) output;
    fprintf(file,"%s\n",rating);
}

void output_query3F(FILE* file, void* output){
    char* rating = (char*) output;
    fprintf(file,"--- 1 ---\n");
    fprintf(file,"rating: %s\n",rating);
}

void output_query4(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length + 1; i++) {
        fprintf(file, "%s\n", result_array[i]);
    }
}

void output_query4F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 1; i < length + 1; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i);
        if(token != NULL) fprintf(file, "id: %s\n", token);
        token = strtok(NULL, ";");
        if(token != NULL) fprintf(file, "begin_date: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "end_date: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "user_id: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "rating: %s\n", token);
        token = strtok(NULL,";");
        if(i != length){ fprintf(file, "total_price: %s\n\n", token);
        }
        else{
            token[strlen(token)] = '\0';
            char *truncatedString = strndup(token, strlen(token));
            fprintf(file,"total_price: %s\n",truncatedString);
            free(truncatedString);
        }

    }
}

void output_query5(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length + 1; i++) {
        if (i != length) fprintf(file, "%s\n", result_array[i]);
        else {
            result_array[i][strlen(result_array[i])] ='\0';
            char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
            fprintf(file,"%s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query5F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 1; i < length + 1; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i);
        if(token != NULL) fprintf(file, "id: %s\n", token);
        token = strtok(NULL, ";");
        if(token != NULL) fprintf(file, "schedule_departure_date: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "destination: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "airline: %s\n", token);
        token = strtok(NULL,";");
        if (i != length){
                fprintf(file,"plane_model: %s\n",token);
                fprintf(file,"\n");
        } else {
            token[strlen(token)] = '\0';
            char *truncatedString = strndup(token, strlen(token));
            fprintf(file,"plane_model: %s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query6(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length + 1; i++) {
        if (i != length) fprintf(file, "%s\n", result_array[i]);
        else {
            result_array[i][strlen(result_array[i])] ='\0';
            char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
            fprintf(file,"%s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query6F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 1; i < length + 1; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i);
        if(token != NULL) fprintf(file, "name: %s\n", token);
        token = strtok(NULL, ";");
        if (i != length){
                fprintf(file, "passengers: %s\n", token);
                fprintf(file,"\n");
        } else {
            token[strlen(token)] = '\0';
            char *truncatedString = strndup(token, strlen(token));
            fprintf(file,"passengers: %s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query7(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length + 1; i++) {
        if (i != length) fprintf(file, "%s\n", result_array[i]);
        else {
            result_array[i][strlen(result_array[i])] ='\0';
            char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
            fprintf(file,"%s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query7F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 1; i < length + 1; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i);
        if(token != NULL) fprintf(file, "name: %s\n", token);
        token = strtok(NULL, ";");
        if (i != length){
                fprintf(file, "median: %s\n", token);
                fprintf(file,"\n");
        } else {
            token[strlen(token)] = '\0';
            char *truncatedString = strndup(token, strlen(token));
            fprintf(file,"median: %s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query8(FILE* file, void* output){
    char* result = (char*) output;
    fprintf(file, "%s\n", result);
}

void output_query8F(FILE* file, void* output){
    char* result = (char*) output;
    fprintf(file,"--- 1 ---\n");
    fprintf(file,"revenue: %s\n",result);
}

void output_query9(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 1; i < length + 1; i++) {
        if (i != length) fprintf(file, "%s\n", result_array[i]);
        else {
            result_array[i][strlen(result_array[i])] ='\0';
            char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
            fprintf(file,"%s\n",truncatedString);
            free(truncatedString);
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
        if (i != length){
                fprintf(file, "name: %s\n", token);
                fprintf(file,"\n");
        } else {
            token[strlen(token)] = '\0';
            char *truncatedString = strndup(token, strlen(token));
            fprintf(file,"name: %s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query10(FILE* file, void* output){
    char** result_array = (char**)output;
    int length = ourAtoi(result_array[0]);
    for (int i = 2; i < length + 2; i++) {
        if (i != (length+1)) fprintf(file, "%s\n", result_array[i]);
        else {
            result_array[i][strlen(result_array[i])] ='\0';
            char *truncatedString = strndup(result_array[i], strlen(result_array[i]));
            fprintf(file,"%s\n",truncatedString);
            free(truncatedString);
        }
    }
}

void output_query10F(FILE* file, void* output){
    char** result = (char**)output;
    int length = ourAtoi(result[0]);
    for(int i = 2; i < length + 2; i++){
        char *token = strtok(result[i], ";");

        fprintf(file, "--- %d ---\n", i-1);
        if(token != NULL) {
            fprintf(file, "%s: %s\n", result[1], token);
        }
        token = strtok(NULL, ";");
        if(token != NULL) fprintf(file, "users: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "flights: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "passengers: %s\n", token);
        token = strtok(NULL,";");
        if(token != NULL) fprintf(file, "unique_passengers: %s\n", token);
        token = strtok(NULL,";");
        if (i != (length+1)){
                fprintf(file,"reservations: %s\n",token);
                fprintf(file,"\n");
        } else {
            fprintf(file,"reservations: %s\n",token);
        }
    }
}

