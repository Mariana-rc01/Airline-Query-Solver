/**
 * @file passengers.c
 * @brief This file contains the implementation of the passengers struct and related functions.
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

#include "entities/passengers.h"

#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>

/**
 * @struct passengersF
 * @brief Represents total passengers information related to a flight.
 */
struct passengers {
    gpointer flight; /**< Flight ID associated with the passenger. */
    gpointer user; /**< User ID associated with the passenger. */
};

PASS create_passengers(void){
    PASS new = malloc(sizeof(struct passengers));
    return new;
}

void set_flight_P(PASS pass, gpointer id){
    pass->flight = id;
}

void set_user_P(PASS pass, gpointer id){
    pass->user = id;
}

int get_flight_P(PASS pass){
    return GPOINTER_TO_INT(pass->flight);
}

int get_user_P(PASS pass){
    return GPOINTER_TO_INT(pass->user);
}

void free_passengers(PASS pass){
    free(pass);
}

int verify_passengers(char** passengers_fields, USERS_C users, FLIGHTS_C flights){
    if (!(passengers_fields[0])) return 0;
    if (!(passengers_fields[1])) return 0;
    if (!(get_flight_by_id(flights, passengers_fields[0]))) return 0;
    if (!(get_user_by_id(users, passengers_fields[1]))) return 0;
    return 1;
}

int build_passengers(char** passengers_fields, void* catalog){

    MANAGER managerC = (MANAGER) catalog;
    USERS_C usersC = get_users_c(managerC);
    FLIGHTS_C flightsC = get_flights_c(managerC);
    PASS_C passengersC = get_pass_c(managerC);

    if (!verify_passengers(passengers_fields, usersC, flightsC)) return 0;

    PASS pass = create_passengers();

    char* copy_flight = strdup(passengers_fields[0]);
    char* copy_user = strdup(passengers_fields[1]);
    set_catalog_passenger(passengersC, pass, copy_user, copy_flight);

    insert_pass_flight_c(copy_user, passengersC, pass->flight);
    insert_pass_user_c(copy_flight,passengersC, pass->user);

    free(pass);

    return 1;
}

