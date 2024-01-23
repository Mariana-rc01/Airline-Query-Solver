/**
 * @file query6_test.c
 * @brief Test file for Query 6 function.
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

#include "test/query6_test.h"

#include <time.h>

void query6_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsInvalid = malloc(sizeof(char*)*2);
    argsInvalid[0] = "2023";
    argsInvalid[1] = "-1";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalid = query6(manager, argsInvalid);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 6 - Invalid N (-1)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query6(resultInvalid);
    free(argsInvalid);
// ----------------------------------------------------------------------------

    char** argsInvalidY = malloc(sizeof(char*)*2);
    argsInvalidY[0] = "2024";
    argsInvalidY[1] = "10";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidY = query6(manager, argsInvalidY);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 6 - Invalid year (2024)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query6(resultInvalidY);
    free(argsInvalidY);
// ----------------------------------------------------------------------------

    char** argsSmall = malloc(sizeof(char*)*2);
    argsSmall[0] = "2023";
    argsSmall[1] = "10";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultSmall = query6(manager, argsSmall);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 6 - N = 10\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query6(resultSmall);
    free(argsSmall);

// ----------------------------------------------------------------------------

    char** argsMedium = malloc(sizeof(char*)*2);
    argsMedium[0] = "2023";
    argsMedium[1] = "100";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultMedium = query6(manager, argsMedium);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 6 - N = 100\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query6(resultMedium);
    free(argsMedium);
// ----------------------------------------------------------------------------

    char** argsBig = malloc(sizeof(char*)*2);
    argsBig[0] = "2023";
    argsBig[1] = "300";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultBig = query6(manager, argsBig);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 6 - N = 250\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query6(resultBig);
    free(argsBig);
    fclose(analysisTest);

}

