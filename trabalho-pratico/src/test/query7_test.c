/**
 * @file query7_test.c
 * @brief Test file for Query 7 function.
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

#include "test/query7_test.h"

#include <time.h>

void query7_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsInvalid = malloc(sizeof(char*));
    argsInvalid[0] = "-1";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalid = query7(manager, argsInvalid);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 7 - Invalid N (-1)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query7(resultInvalid);
    free(argsInvalid);
// ----------------------------------------------------------------------------

    char** argsSmall = malloc(sizeof(char*));
    argsSmall[0] = "10";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultSmall = query7(manager, argsSmall);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 7 - N = 10\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query7(resultSmall);
    free(argsSmall);
// ----------------------------------------------------------------------------

    char** argsMedium = malloc(sizeof(char*));
    argsMedium[0] = "100";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultMedium = query7(manager, argsMedium);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 7 - N = 100\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query7(resultMedium);
    free(argsMedium);
// ----------------------------------------------------------------------------

    char** argsBig = malloc(sizeof(char*));
    argsBig[0] = "300";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultBig = query7(manager, argsBig);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 7 - N = 250\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query7(resultBig);
    free(argsBig);
    fclose(analysisTest);
}
