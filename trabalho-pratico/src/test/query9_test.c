/**
 * @file query9_test.c
 * @brief Test file for Query 9 function.
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

#include "test/query9_test.h"

#include <time.h>

void query9_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");

    char** args = malloc(sizeof(char*));
    args[0] = "Mateus Sim";

    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    void* result = query9(manager, args);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 9 - Small user list\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query9(result);
    free(args);
// ----------------------------------------------------------------------------

    char** args2 = malloc(sizeof(char*));
    args2[0] = "Alexand";

    clock_gettime(CLOCK_REALTIME, &start);
    void* result2 = query9(manager, args2);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 9 - Big user list\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query9(result2);
    free(args2);

    fclose(analysisTest);

}
