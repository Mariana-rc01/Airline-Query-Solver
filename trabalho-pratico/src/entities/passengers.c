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

#include "menuNdata/statistics.h"
#include "IO/input.h"
#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>

/**
 * @struct passengersF
 * @brief Represents total passengers information related to a flight.
 */
struct passengers {
    char* flight; /**< Flight ID associated with the passenger. */
    char* user; /**< User ID associated with the passenger. */
};

PASS create_passengers(void){
    PASS new = malloc(sizeof(struct passengers));

    new->flight = NULL;
    new->user = NULL;

    return new;
}

void set_flight_P(PASS pass, char* id){
    pass->flight = strdup(id);
}

void set_user_P(PASS pass, char* id){
    pass->user = strdup(id);
}

char* get_flight_P(PASS pass){
    return (strdup(pass->flight));
}

char* get_user_P(PASS pass){
    return (strdup(pass->user));
}

void free_passengers(PASS pass){
    free(pass->flight);
    free(pass->user);

    free(pass);
}

int verify_passengers(char** passengers_fields, USERS_C users){
    if (!(passengers_fields[0])) return 0;
    if (!(passengers_fields[1])) return 0;
    if (!(get_user_by_id(users, passengers_fields[1]))) return 0;
    (void) users;
    return 1;
}

int build_passengers(char** passengers_fields, void* catalog, STATS stats){

    MANAGER managerC = (MANAGER) catalog;
    USERS_C usersC = get_users_c(managerC);
    PASS_C passengersC = get_pass_c(managerC);

    if (!verify_passengers(passengers_fields, usersC)) return 0;

    PASS pass = create_passengers();

    set_flight_P(pass,passengers_fields[0]);
    set_user_P(pass,passengers_fields[1]);

    insert_passenger_c(pass, passengersC);

    (void) stats;

    return 1;
}

