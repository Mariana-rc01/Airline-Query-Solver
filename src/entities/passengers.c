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
#include "catalogs/passengers_c.h"
#include "catalogs/users_c.h"

#include <stdlib.h>
#include <string.h>

/**
 * @struct passengers
 * @brief Represents passenger information related to a flight.
 */
struct passengers {
    char* flight_id; /**< Unique flight ID associated with the passenger. */
    char* user_id; /**< Unique user ID of the passenger. */
};

PASS create_passengers(void){
    PASS new = malloc(sizeof(struct passengers));

    new->flight_id = NULL;
    new->user_id = NULL;;

    return new;
}

void set_flight_id_P(PASS pass, char* f_id){
    pass->flight_id = strdup(f_id);
}

void set_user_id_P(PASS pass, char* u_id){
    pass->user_id = strdup(u_id);
}

char* get_flight_id_P(PASS pass){
    return strdup(pass->flight_id);
}

char* get_user_id_P(PASS pass){
    return strdup(pass->user_id);
}


void free_passengers(PASS pass){
    free(pass->flight_id);
    free(pass->user_id);

    free(pass);
}

int verify_passengers(char** passengers_fields, USERS_C users){
    if (!(passengers_fields[0]) || !(passengers_fields[1])) return 0;
    if (!(get_user_by_id(users, passengers_fields[1]))) return 0;
    return 1;
}

int build_passengers(char** passengers_fields, void* catalogU, void* catalogF, STATS stats){

    if (!verify_passengers(passengers_fields, catalogU)) return 0;

    PASS pass = create_passengers();

    set_flight_id_P(pass,passengers_fields[0]);
    set_user_id_P(pass,passengers_fields[1]);

    insert_passengers_c(pass,catalog);
    (void) stats;
    (void) catalogF;

    return 1;
}



