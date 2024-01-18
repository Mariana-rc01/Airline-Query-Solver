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

/**
 * @struct passengers_catalog
 * @brief A catalog for storing passenger records.
 */
struct passengers_catalog {
    GHashTable* users; /**< Hash table to store flights of users records. */
    GHashTable* passengers;
};

PASS_C create_passengers_c(void){
    PASS_C new = malloc(sizeof(struct passengers_catalog));

    new->users = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_ptr_array);
    new->passengers = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_ptr_array);

    return new;
}

void insert_pass_user_c(char* flight_id, PASS_C catalog, char* key){
    if (g_hash_table_contains(catalog->users, key)){
        GPtrArray* flightArray = g_hash_table_lookup(catalog->users,key);
        g_ptr_array_add(flightArray, flight_id);
        free(key);
    }
    else {
        GPtrArray* flightArray = g_ptr_array_new();
        g_ptr_array_add(flightArray, flight_id);
        g_hash_table_insert(catalog->users, key, flightArray);
    }
}

void insert_passengers_c(PASS_C catalog, char* key, char* user){
    if (g_hash_table_contains(catalog->passengers, key)){
        GPtrArray* userArray = g_hash_table_lookup(catalog->passengers,key);
        g_ptr_array_add(userArray, user);
        free(key);
    } else{
        GPtrArray* userArray = g_ptr_array_new();
        g_ptr_array_add(userArray, user);
        g_hash_table_insert(catalog->passengers, key, userArray);
    }
}

GPtrArray* get_passengers_c(PASS_C catalog, char* key){
    return g_hash_table_lookup(catalog->passengers, key);
}

GPtrArray* get_user_array_by_id(PASS_C catalog, char* id){
    return g_hash_table_lookup(catalog->users, id);
}

int get_user_array_number_id(PASS_C catalog, char* id){
    GPtrArray* user_array = get_user_array_by_id(catalog, id);
    if (!user_array) return 0;
    return user_array->len;
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->users);
    g_hash_table_destroy(catalog->passengers);

    free(catalog);
}

