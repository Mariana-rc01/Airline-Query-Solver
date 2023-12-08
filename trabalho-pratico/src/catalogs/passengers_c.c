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
    GHashTable* flights; /**< Hash table to store passengers of flights records.*/

    GHashTable* users; /**< Hash table to store flights of users records. */
};

PASS_C create_passengers_c(void){
    PASS_C new = malloc(sizeof(struct passengers_catalog));

    new->flights = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_ptr_array);

    new->users = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_ptr_array);

    return new;
}

//--------------------------------------------
void insert_pass_flight_c(char* user_id, PASS_C catalog, char* key){
    if (g_hash_table_contains(catalog->flights, key)){
        GPtrArray* usersArray = g_hash_table_lookup(catalog->flights, key);
        g_ptr_array_add(usersArray, user_id);
    }
    else {
        GPtrArray* usersArray = g_ptr_array_new();
        g_ptr_array_add(usersArray, user_id);
        g_hash_table_insert(catalog->flights, key, usersArray);
    }
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
//--------------------------------------------

//--------------------------------------------
GPtrArray* get_flight_array_by_id(PASS_C catalog, char* id){
    return g_hash_table_lookup(catalog->flights, id);
}

int get_flight_array_number_by_id(PASS_C catalog, char* id){
    GPtrArray* flight_array = get_flight_array_by_id(catalog,id);
    if (!flight_array) return 0;
    return flight_array->len;
}
//--------------------------------------------

//--------------------------------------------
GPtrArray* get_user_array_by_id(PASS_C catalog, char* id){
    return g_hash_table_lookup(catalog->users, id);
}

int get_user_array_number_id(PASS_C catalog, char* id){
    GPtrArray* user_array = get_user_array_by_id(catalog, id);
    if (!user_array) return 0;
    return user_array->len;
}
//--------------------------------------------

void remove_flight_array_from_hash_table(PASS_C pass, char* flight_id) {
    if (flight_id != NULL) {
        g_hash_table_remove(pass->flights, flight_id);
    }
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->flights);
    g_hash_table_destroy(catalog->users);

    free(catalog);
}

