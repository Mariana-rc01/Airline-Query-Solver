/**
 * @file flights_c.c
 * @brief This file contains the implementation of the flights catalog and related functions.
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

#include "catalogs/flights_c.h"

/**
 * @struct flights_catalog
 * @brief Flight catalog structure that stores information about flights.
 */
struct flights_catalog {
    GHashTable* flights; /**< Hash table that maps flight IDs to flight objects.*/
};

FLIGHTS_C create_flight_c(void){
    FLIGHTS_C new = malloc(sizeof(struct flights_catalog));

    new->flights = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify) free_user);

    return new;
}

void insert_flight_c(FLIGHT flight, FLIGHTS_C catalog){
    char* key = get_flight_id(flight);
    g_hash_table_insert(catalog->flights, key, flight);
}

FLIGHT get_flight_by_id(FLIGHTS_C catalog, FLIGHT flight){
    char* id = get_flight_id(flight);
    return g_hash_table_lookup(catalog->flights, id);
}

void free_flight_c(FLIGHTS_C catalog){
    g_hash_table_destroy(catalog->flights);
    free(catalog);
}
