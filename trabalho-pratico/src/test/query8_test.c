/**
 * @file query8_test.c
 * @brief Test file for Query 8 function.
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

#include "test/query8_test.h"

#include <time.h>

void query8_test(MANAGER manager){
    FILE* analysisTest = fopen("Resultados/analysisTest.txt", "a");

    char** args = malloc(sizeof(char*)*3);
    args[0] = "HTL1001";
    args[1] = "2023/05/01";
    args[2] = "2023/06/01";

    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    void* result = query8(manager, args);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 8 - Case 1\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query8(result);
    free(args);
// ----------------------------------------------------------------------------

    char** args2 = malloc(sizeof(char*)*3);
    args2[0] = "HTL203";
    args2[1] = "2022/09/07";
    args2[2] = "2023/12/09";

    clock_gettime(CLOCK_REALTIME, &start);
    void* result2 = query8(manager, args2);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(analysisTest, "Query 8 - Case 2\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n\n", elapsed);
    free_query8(result2);
    free(args2);
    fclose(analysisTest);
    //HTL203 2022/09/07 2022/12/09
}
