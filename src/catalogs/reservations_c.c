/**
 * @file reservations_c.c
 * @brief This file contains the implementation of the reservations catalog struct and related functions.
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

#include "catalogs/reservations_c.h"
#include "entities/reservations.h"
#include "utils/utils.h"

/**
 * @struct reservations_catalog
 * @brief A catalog for storing reservation records.
 */
struct reservations_catalog {
    GHashTable *reservations; /**< Hash table to store reservation records. */
};

RESERV_C create_reservations_c(void){
    RESERV_C new = malloc(sizeof(struct reservations_catalog));

    new->reservations = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify) free_reservations);

    return new;
}

void insert_reservations_c(RESERV reserv, RESERV_C catalog){
    char* key = get_reservation_id(reserv);
    g_hash_table_insert(catalog->reservations, key, reserv);
}

RESERV get_reservations_by_id(RESERV_C catalog, char* id){
    return g_hash_table_lookup(catalog->reservations, id);
}

void free_reservations_c(RESERV_C catalog){
    g_hash_table_destroy(catalog->reservations);
    free(catalog);
}



