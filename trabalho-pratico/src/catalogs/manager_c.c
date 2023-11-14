/**
 * @file manager_c.c
 * @brief This file contains the implementation of all catalogs jointed and related functions.
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

#include "catalogs/manager_c.h"

/**
 * @struct manager_catalog
 * @brief A structure that contains various related catalogs.
 */
struct manager_catalog {
    USERS_C users;          /**< User catalog */
    FLIGHTS_C flights;      /**< Flight catalog */
    RESERV_C reservations;  /**< Reservation catalog */
    PASS_C passengers;      /**< Passenger catalog */
};

MANAGER create_manager_c(USERS_C users_c, FLIGHTS_C flights_c, RESERV_C reserv_c, PASS_C pass_c){
    MANAGER new = malloc(sizeof(struct manager_catalog));

    new->users = users_c;
    new->flights = flights_c;
    new->reservations = reserv_c;
    new->passengers = pass_c;

    return new;
}

USERS_C get_users_c(MANAGER catalog){
    return catalog->users;
}

FLIGHTS_C get_flights_c(MANAGER catalog){
    return catalog->flights;
}

RESERV_C get_reserv_c(MANAGER catalog){
    return catalog->reservations;
}

PASS_C get_pass_c(MANAGER catalog){
    return catalog->passengers;
}

void free_manager_c(MANAGER catalog){
    free_flight_c(catalog->flights);
    free_user_c(catalog->users);
    free_reservations_c(catalog->reservations);
    free_passengers_c(catalog->passengers);
    free(catalog);
}
