/**
 * @file query8_test.c
 * @brief
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
    fprintf(analysisTest, "Query 8\n");
    fprintf(analysisTest, "Elapsed time: %.6f seconds\n\n", elapsed);
    free_query8(result);
    fclose(analysisTest);
}