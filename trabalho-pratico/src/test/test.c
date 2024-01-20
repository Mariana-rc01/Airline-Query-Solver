/**
 * @file test.c
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

#include "test/test.h"

#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

void test(char* pathD, char* pathI, char* pathO){
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);

    USERS_C users_catalog = create_user_c();
    FLIGHTS_C flights_catalog = create_flight_c();
    RESERV_C reservations_catalog = create_reservations_c();
    PASS_C passengers_catalog = create_passengers_c();
    MANAGER manager_catalog = create_manager_c(users_catalog,flights_catalog,reservations_catalog,passengers_catalog);

    if (set_catalogs(manager_catalog,pathD) == -1){
        printf("The provided dataset is not valid.\n");
        return;
    }

    int n = execute_queries(manager_catalog,pathI, 1);

    if (n == -1){
        return;
    }

    compare_files(pathO, n);

    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);

    char time[512];
    sprintf(time, "Elapsed time: %.6f seconds", elapsed);
    char memory[512];
    sprintf(memory, "Memory usage: %ld KB\n", r_usage.ru_maxrss);

    replace_lines_at_start("Resultados/analysis.txt", time, memory);

    //Testes para cada query
    clock_gettime(CLOCK_REALTIME, &start);

    query1_test(manager_catalog);
    
    
    
    
    
    query7_test(manager_catalog);
    query8_test(manager_catalog);
    query9_test(manager_catalog);
    //-> Restantes queries aqui <-

    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    getrusage(RUSAGE_SELF, &r_usage);

    char timeT[512];
    sprintf(timeT, "Elapsed time: %.6f seconds", elapsed);
    char memoryT[512];
    sprintf(memoryT, "Memory usage: %ld KB\n", r_usage.ru_maxrss);

    replace_lines_at_start("Resultados/analysisTest.txt", timeT, memoryT);

    free_manager_c(manager_catalog);
}


