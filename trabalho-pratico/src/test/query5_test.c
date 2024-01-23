/**
 * @file query5_test.c
 * @brief Test file for Query 5 function.
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

#include "test/query5_test.h"

#include <time.h>

void query5_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");
    struct timespec start, end;
    double elapsed;

    char** argsInvalidAirport = malloc(sizeof(char*)*3);
    argsInvalidAirport[0] = "Lisbon";
    argsInvalidAirport[1] = "2021/01/01 00:00:00";
    argsInvalidAirport[2] = "2022/12/31 23:59:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidAir = query5(manager, argsInvalidAirport);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Invalid Airport\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query5(resultInvalidAir);
    free(argsInvalidAirport);
// ----------------------------------------------------------------------------

    char** argsInvalidBDate = malloc(sizeof(char*)*3);
    argsInvalidBDate[0] = "LIS";
    argsInvalidBDate[1] = "2021/13/01 00:00:00";
    argsInvalidBDate[2] = "2022/12/31 23:59:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidBDate = query5(manager, argsInvalidBDate);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Invalid begin date (2021/13/01 00:00:00)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query5(resultInvalidBDate);
    free(argsInvalidBDate);
// ----------------------------------------------------------------------------

    char** argsInvalidEDate = malloc(sizeof(char*)*3);
    argsInvalidEDate[0] = "LIS";
    argsInvalidEDate[1] = "2021/01/01 00:00:00";
    argsInvalidEDate[2] = "2022/12/31 23:60:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultInvalidEDate = query5(manager, argsInvalidEDate);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Invalid end date (2022/12/31 23:60:59)\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query5(resultInvalidEDate);
    free(argsInvalidEDate);
// ----------------------------------------------------------------------------

    char** argsSmall = malloc(sizeof(char*)*3);
    argsSmall[0] = "LIS";
    argsSmall[1] = "2021/01/01 00:00:00";
    argsSmall[2] = "2021/12/31 23:60:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultSmall = query5(manager, argsSmall);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Within a short time frame\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query5(resultSmall);
    free(argsSmall);
// ----------------------------------------------------------------------------

    char** argsMedium = malloc(sizeof(char*)*3);
    argsMedium[0] = "LIS";
    argsMedium[1] = "2020/01/01 00:00:00";
    argsMedium[2] = "2022/12/31 23:60:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultMedium = query5(manager, argsMedium);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Within a moderate time frame\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query5(resultMedium);
    free(argsMedium);
// ----------------------------------------------------------------------------

    char** argsBig = malloc(sizeof(char*)*3);
    argsBig[0] = "LIS";
    argsBig[1] = "2017/01/01 00:00:00";
    argsBig[2] = "2022/12/31 23:60:59";

    clock_gettime(CLOCK_REALTIME, &start);
    void* resultBig = query5(manager, argsBig);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 5 - Within a longer time frame\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query5(resultBig);
    free(argsBig);
    fclose(analysisTest);

}

