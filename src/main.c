/**
 * @file main.c
 * @brief Contains the entry point to the program
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

#include "entities/flights.h"
#include "entities/passengers.h"
#include "entities/reservations.h"
#include "entities/users.h"
#include "menuNdata/statistics.h"
#include "IO/parser.h"
#include "IO/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Concatenes two strings
 *
 * @param s1 Initial string
 * @param s2 Final string
 */

char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/**
 * @brief Function main that receives the arguments from the command line
 *
 * Depending on number of arguments starts wither batch mode(2 arguments) or interactive mode (no arguments)
 * 
 * @param argc Number of arguments
 * @param argsv Array containing the arguments
 */

int main(int argc, char** argsv){   
    char* path1 = arsv[0];
    char* path2 = arsv[1];
    FILE *flights_file, *passengers_file, *users_file, *reservations_file;
    void *flights_catalog, *users_catalog, *passengers_catalog, *reservations_catalog;
    STATS statistics = NULL;
    if(argc == 2) { 
        flights_file = fopen(concat(path1, "flights.csv"), "r");
        passengers_file = fopen(concat(path1, "passengers.csv"), "r");
        users_file = fopen(concat(path1, "users.csv"), "r");
        reservations_file = fopen(concat(path1, "reservations.csv"), "r");
        queries_file = fopen(path2, "r");
        
        parseF(flights_file, 13, build_flight, flights_catalog, statistics);
        parseF(passengers_file, 2, build_passengers, passengers_catalog, statistics);
        parseF(users_file, 12, build_users, users_catalog, statistics);
        parseF(reservations_file, 14, build_reservations, reservations_catalog, statistics);
        return 0;
    }
    if(argc == 0) {
        //stdin...
        return 0;
    }
    else{
        printf(%s, "Invalid number of arguments, must be either 0 or 2");
        //perror("Error");
        return 0;
    }
}
