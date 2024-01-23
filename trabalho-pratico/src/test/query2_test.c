/**
 * @file query2_test.c
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

#include "test/query2_test.h"

#include <time.h>

void query2_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsInvalidID = malloc(sizeof(char*)*2);
    argsInvalidID[0] = "DGarcia429";
    argsInvalidID[1] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidID = query2(manager, argsInvalidID);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 2 - Invalid ID\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query2(resultInvalidID);
    free(argsInvalidID);
// ----------------------------------------------------------------------------

    char** argsValidID = malloc(sizeof(char*)*2);
    argsValidID[0] = "Jéssica Tavares";
    argsValidID[1] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidID = query2(manager, argsValidID);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 2 - Flights and Reservations\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query2(resultValidID);
    free(argsValidID);
// ----------------------------------------------------------------------------

    char** argsValidFlight = malloc(sizeof(char*)*3);
    argsValidFlight[0] = "Jéssica Tavares";
    argsValidFlight[1] = "flights";
    argsValidFlight[2] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidFlight = query2(manager, argsValidFlight);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 2 - Flights\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query2(resultValidFlight);
    free(argsValidFlight);
// ----------------------------------------------------------------------------

    char** argsValidReservations = malloc(sizeof(char*)*3);
    argsValidReservations[0] = "Jéssica Tavares";
    argsValidReservations[1] = "reservations";
    argsValidReservations[2] = NULL;

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidReservations = query2(manager, argsValidReservations);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 2 - Reservations\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query2(resultValidReservations);
    free(argsValidReservations);

    fclose(analysisTest);
}
