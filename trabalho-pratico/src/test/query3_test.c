/**
 * @file query3_test.c
 * @brief Test file for Query 3 function.
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

#include "test/query3_test.h"

#include <time.h>

void query3_test(MANAGER manager){

    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsInvalidID = malloc(sizeof(char*));
    argsInvalidID[0] = "DGarcia429";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidID = query3(manager, argsInvalidID);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 3 - Invalid ID\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query3(resultInvalidID);
    free(argsInvalidID);
// ----------------------------------------------------------------------------

    char** argsValidID = malloc(sizeof(char*));
    argsValidID[0] = "HTL1001";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultValidID = query3(manager, argsValidID);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 3 - Valid ID\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query3(resultValidID);
    free(argsValidID);

    fclose(analysisTest);
}