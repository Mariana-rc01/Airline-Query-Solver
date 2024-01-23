/**
 * @file query1_test.c
 * @brief Test file for Query 1 function.
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

#include "test/query1_test.h"

#include <time.h>

void query1_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "w");
// ----------------------------------------------------------------------------
    char** argsValidUser = malloc(sizeof(char*));
    argsValidUser[0] = "Jéssica Tavares";

    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidUser = query1(manager, argsValidUser);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Valid user\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query1(resultValidUser);
    free(argsValidUser);

// ----------------------------------------------------------------------------
    char** argsInvalidUser = malloc(sizeof(char*));
    argsInvalidUser[0] = "DGarcia429";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInValidUser = query1(manager, argsInvalidUser);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Invalid user\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query1(resultInValidUser);
    free(argsInvalidUser);

// ----------------------------------------------------------------------------
    char** argsValidFlight = malloc(sizeof(char*));
    argsValidFlight[0] = "0000000029";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidFlight = query1(manager, argsValidFlight);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Valid flight\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query1(resultValidFlight);
    free(argsValidFlight);

// ----------------------------------------------------------------------------
    char** argsInvalidFlight = malloc(sizeof(char*));
    argsInvalidFlight[0] = "0000000678";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidFlight = query1(manager, argsInvalidFlight);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Invalid flight\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query1(resultInvalidFlight);
    free(argsInvalidFlight);

// ----------------------------------------------------------------------------
    char** argsValidReservation = malloc(sizeof(char*));
    argsValidReservation[0] = "Book0000000048";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidReservation = query1(manager, argsValidReservation);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Valid reservation\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query1(resultValidReservation);
    free(argsValidReservation);

// ----------------------------------------------------------------------------
    char** argsInvalidReservation = malloc(sizeof(char*));
    argsInvalidReservation[0] = "Book0000020828";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidReservation = query1(manager, argsInvalidReservation);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 1 - Invalid reservation\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query1(resultInvalidReservation);
    free(argsInvalidReservation);

    fclose(analysisTest);

}

