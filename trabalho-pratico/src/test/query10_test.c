/**
 * @file query10_test.c
 * @brief Test file for Query 10 function.
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

#include "test/query10_test.h"

#include <time.h>

void query10_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsAll = malloc(sizeof(char*)*2);
    argsAll[0] = NULL;
    argsAll[1] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultAll = query10(manager, argsAll);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 10 - years\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query10(resultAll);
    free(argsAll);

// ----------------------------------------------------------------------------
    char** args2023 = malloc(sizeof(char*)*2);
    args2023[0] = "2023";
    args2023[1] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultMonth = query10(manager, args2023);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 10 - months of 2023\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query10(resultMonth);
    free(args2023);

// ----------------------------------------------------------------------------
    char** args2306 = malloc(sizeof(char*)*2);
    args2306[0] = "2023";
    args2306[1] = "06";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultDays = query10(manager, args2306);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 10 - days of 06/2023\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query10(resultDays);
    free(args2306);

// ----------------------------------------------------------------------------
    char** argsInvalidYear = malloc(sizeof(char*)*2);
    argsInvalidYear[0] = "2024";
    argsInvalidYear[1] = "03";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidYear = query10(manager, argsInvalidYear);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 10 - invalid year (2024)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query10(resultInvalidYear);
    free(argsInvalidYear);

// ----------------------------------------------------------------------------
    char** argsInvalidMonth = malloc(sizeof(char*)*2);
    argsInvalidMonth[0] = "2024";
    argsInvalidMonth[1] = "13";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidMonth = query10(manager, argsInvalidMonth);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 10 - invalid month (13/2024)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query10(resultInvalidMonth);
    free(argsInvalidMonth);

    fclose(analysisTest);
}

