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
    GHashTable* reserv; /**< Hash table to store reservation records. */
    GHashTable* reserv_id;
};

RESERV_C create_reservations_c(void){
    RESERV_C new = malloc(sizeof(struct reservations_catalog));

    new->reserv = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_reservations);
    new->reserv_id = g_hash_table_new_full(g_str_hash,g_str_equal, free, NULL);
    return new;
}

void insert_reservations_c(RESERV reserv, RESERV_C catalog, gpointer key){
    g_hash_table_insert(catalog->reserv, key, reserv);
}

RESERV get_reservations_by_id(RESERV_C catalog, char* id){
    gpointer reserv_id = g_hash_table_lookup(catalog->reserv_id, id);
    if (reserv_id == NULL) return NULL;
    return get_reservations_by_gpointer(catalog, reserv_id);
}

RESERV get_reservations_by_gpointer(RESERV_C catalog, gpointer reserv_id){
    return g_hash_table_lookup(catalog->reserv, reserv_id);
}

void set_catalog_reserv(RESERV_C catalog, RESERV reserv, char* id){
    static int number_reservs = 1;

    char* copy_id = g_strdup(id);
    gpointer reserv_id = GINT_TO_POINTER(number_reservs);
    g_hash_table_insert(catalog->reserv_id, copy_id, reserv_id);

    set_reservation_id(reserv, reserv_id);

    number_reservs++;

}

void free_reservations_c(RESERV_C catalog){
    g_hash_table_destroy(catalog->reserv);
    g_hash_table_destroy(catalog->reserv_id);
    free(catalog);
}

