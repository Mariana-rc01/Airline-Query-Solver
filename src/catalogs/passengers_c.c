/**
 * @file passengers_c.c
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

#include "catalogs/passengers_c.h"
#include "entities/passengers.h"

/**
 * @struct passengers_catalog
 * @brief A catalog for storing passenger records.
 */
struct passengers_catalog {
    GHashTable *passengers; /**< Hash table to store passenger records. */
    GHashTable *passengers_flight_id; /**< Hash table for passenger records by flight ID. */
    GHashTable *passengers_user_id; /**< Hash table for passenger records by user ID. */
};

PASS_C create_passengers_c(void){
    PASS_C new_catalog = malloc(sizeof(struct passengers_catalog));

    new_catalog->passengers = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);

    new_catalog->passengers_flight_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    new_catalog->passengers_user_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    return new_catalog;
}

void insert_passenger_c(PASS_C catalog, PASS pass){
    gpointer key1 = GINT_TO_POINTER(get_flight_id_P(pass));
    gpointer key2 = GINT_TO_POINTER(get_user_id_P(pass));
    g_hash_table_insert(catalog->passengers, key1, pass);
    g_hash_table_insert(catalog->passengers_flight_id, key1, pass);
    g_hash_table_insert(catalog->passengers_user_id, key2, pass);
}

void set_c_flight_id_P(PASS_C catalog, PASS pass, char* flight_id, char* user_id){
    return;
}

char* get_c_passengers_by_flight_id(PASS_C catalog, char* flight_id){
    return;
}

char* get_c_passengers_by_user_id(PASS_C catalog, char* user_id){
    return;
}

PASS get_c_passengers(PASS_C catalog, char* flight_id){
    return;
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->passengers);
    g_hash_table_destroy(catalog->passengers_flight_id);
    g_hash_table_destroy(catalog->passengers_user_id);
    free(catalog);
}










