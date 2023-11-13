/**
 * @file batch.c
 * @brief Contains the code related to the bath mode
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
#include "catalogs/manager_c.h"
#include "menuNdata/statistics.h"
#include "IO/parser.h"
#include "IO/input.h"
#include "utils/utils.h"
#include "IO/interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setup_catalog_and_stats(MANAGER manager_catalog, STATS statistics, char* path1){
    FILE *flights_file, *passengers_file, *users_file, *reservations_file;
    FILE *flights_error_file, *passengers_error_file, *users_error_file, *reservations_error_file;

    char* flight_path = concat(path1, "/flights.csv");
    flights_file = fopen(flight_path, "r");

    char* passenger_path = concat(path1, "/passengers.csv");
    passengers_file = fopen(passenger_path, "r");

    char* user_path = concat(path1, "/users.csv");
    users_file = fopen(user_path, "r");

    char* reservation_path = concat(path1, "/reservations.csv");
    reservations_file = fopen(reservation_path, "r");

    flights_error_file = fopen("Resultados/flights_errors.csv", "w");
    passengers_error_file = fopen("Resultados/passengers_errors.csv", "w");
    users_error_file = fopen("Resultados/users_errors.csv", "w");
    reservations_error_file = fopen("Resultados/reservations_errors.csv", "w");

    USERS_C users = get_users_c(manager_catalog);
    parseF(users_file, 12, build_user, users, statistics, users_error_file);
    //parseF(passengers_file, 2, build_passengers, manager_catalog, statistics, passengers_error_file);
    parseF(reservations_file, 14, build_reservations, manager_catalog, statistics, reservations_error_file);
    parseF(flights_file, 13, build_flight, manager_catalog, statistics, flights_error_file);

    free(flight_path);
    free(passenger_path);
    free(user_path);
    free(reservation_path);

    fclose(flights_file);
    fclose(passengers_file);
    fclose(users_file);
    fclose(reservations_file);

    // Verifies if the error files contain any data
    if (isFileEmpty(flights_error_file)) {
        remove("flights_errors.csv");
    }
    if (isFileEmpty(passengers_error_file)) {
        remove("passengers_errors.csv");
    }
    if (isFileEmpty(users_error_file)) {
        remove("users_errors.csv");
    }
    if (isFileEmpty(reservations_error_file)) {
        remove("reservations_errors.csv");
    }

    fclose(flights_error_file);
    fclose(passengers_error_file);
    fclose(users_error_file);
    fclose(reservations_error_file);

    return 0;
}

void batch (char* path1, char* path2) {

    USERS_C users_catalog = create_user_c();
    FLIGHTS_C flights_catalog = create_flight_c();
    RESERV_C reservations_catalog = create_reservations_c();
    PASS_C passengers_catalog = create_passengers_c();
    MANAGER manager_catalog = create_manager_c(users_catalog,flights_catalog,reservations_catalog,passengers_catalog);

    STATS statistics = NULL;

    if (setup_catalog_and_stats(manager_catalog,statistics,path1) == -1){
        return;
    }

    FILE* queries_file = fopen(path2, "r");

    interpreter(queries_file);

    fclose(queries_file);

    //free_user_c(users_catalog);
    //free_reservations_c(reservations_catalog);
    //free_flight_c(flights_catalog);
    free_passengers_c(passengers_catalog);
    free_manager_c(manager_catalog);
}

