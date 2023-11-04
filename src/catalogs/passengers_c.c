/**
 * @file passengers_c.c
 * @brief This file contains the implementation of the passengers catalog struct and related functions.
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

#include "catalogs/passengers_c.h"
#include "entities/passengers.h"

/**
 * @struct passengers_catalog
 * @brief A catalog for storing passenger records.
 */
struct passengers_catalog {
    GHashTable *passengers; /**< Hash table to store passenger records. */
};

PASS_C create_passengers_c(void){
    PASS_C new_catalog = malloc(sizeof(struct passengers_catalog));

    new_catalog->passengers = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);

    return new_catalog;
}

void insert_passengers_c(PASS pass, PASS_C catalog){
    char* key = get_flight_id_P(pass);
    g_hash_table_insert(catalog->passengers, key, pass);
}

PASS get_c_passengers(PASS_C catalog, char* flight_id){
    return g_hash_table_lookup(catalog->passengers, flight_id);
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->passengers);
    free(catalog);
}










