/**
 * @file reservations_c.c
 * @brief This file contains the implementation of the flight struct and related functions.
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
    GHashTable *reservations_id; /**< Hash table for reservation records by ID. */
    GHashTable *reservations_user_id; /**< Hash table for reservation records by user ID. */
};

RESERV_C create_reservations_c(void){
    RESERV_C new_catalog = malloc(sizeof(struct reservations_catalog));

    new_catalog->reservations = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify) free_reservations);
    new_catalog->reservations_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    new_catalog->reservations_user_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    return new;
}

void insert_reservations_c(RESERV reserv, RESERV_C catalog){
    char* idS = get_reservation_id(reserv);
    int id = ourAtoi(idS+4);
    gpointer key = GINT_TO_POINTER(id);
    g_hash_table_insert(catalog->reservations, key, reserv);
}

void set_catalog_reservations_id(RESERV_C catalog, RESERV reserv, char* id){
    return;
}

RESERV get_reservations_by_id(RESERV_C catalog, char* id){
    int idI = ourAtoi(id+4);
    char* idS = sprintf("%d", idI);
    gpointer reserv_id = g_hash_table_lookup(catalog->reservations_id, idS);

    if(reserv_id == NULL) return NULL;

    return g_hash_table_lookup(catalog->reservations, reserv_id);
}

void free_reservations_c(RESERV_C catalog){
    g_hash_table_destroy(catalog->reservations);
    g_hash_table_destroy(catalog->reservations_id);
    g_hash_table_destroy(catalog->reservations_user_id);
    free(catalog);
}



