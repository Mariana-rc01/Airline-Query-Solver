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
    GHashTable* flights; /**< Hash table to store passengers of flights records.*/
    GHashTable* flights_id;

    GHashTable* users; /**< Hash table to store flights of users records. */
    GHashTable* users_id;
};

PASS_C create_passengers_c(void){
    PASS_C new = malloc(sizeof(struct passengers_catalog));

    new->flights = g_hash_table_new_full(NULL, g_direct_equal, NULL, free_ptr_array);
    new->flights_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    new->users = g_hash_table_new_full(NULL, g_direct_equal, NULL, free_ptr_array);
    new->users_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    return new;
}

//--------------------------------------------
void insert_pass_flight_c(char* user_id, PASS_C catalog, gpointer key){
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

void insert_pass_user_c(char* flight_id, PASS_C catalog, gpointer key){
    if (g_hash_table_contains(catalog->users, key)){
        GPtrArray* flightArray = g_hash_table_lookup(catalog->users,key);
        g_ptr_array_add(flightArray, flight_id);
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
    gpointer flight_id = g_hash_table_lookup(catalog->flights_id, id);
    if (flight_id == NULL) return NULL;
    return get_flight_array_by_gpointer(catalog, flight_id);
}

GPtrArray* get_flight_array_by_gpointer(PASS_C catalog, gpointer flight_id){
    return g_hash_table_lookup(catalog->flights, flight_id);
}
//--------------------------------------------

//--------------------------------------------
GPtrArray* get_user_array_by_id(PASS_C catalog, char* id){
    gpointer user_id = g_hash_table_lookup(catalog->users_id, id);
    if (user_id == NULL) return NULL;
    return get_user_array_by_gpointer(catalog, user_id);
}

GPtrArray* get_user_array_by_gpointer(PASS_C catalog, gpointer user_id){
    return g_hash_table_lookup(catalog->users, user_id);
}
//--------------------------------------------

void set_catalog_passenger(PASS_C catalog, PASS pass, char* user_id, char* flight_id){
    static int number_flights = 1;
    static int number_users = 1;

    if (g_hash_table_contains(catalog->flights_id,flight_id)){
        gpointer pass_id = g_hash_table_lookup(catalog->flights_id, flight_id);
        set_flight_P(pass, pass_id);
    }
    else {
        char* copy_id = g_strdup(flight_id);
        gpointer pass_id = GINT_TO_POINTER(number_flights);
        g_hash_table_insert(catalog->flights_id, copy_id, pass_id);
        set_flight_P(pass, pass_id);
        number_flights++;
    }

    if (g_hash_table_contains(catalog->users_id, user_id)){
        gpointer pass_id3 = g_hash_table_lookup(catalog->users_id, user_id);
        set_user_P(pass, pass_id3);
    }
    else {
        char* copy_id3 = g_strdup(user_id);
        gpointer pass_id3 = GINT_TO_POINTER(number_users);
        g_hash_table_insert(catalog->users_id, copy_id3, pass_id3);
        set_user_P(pass, pass_id3);
        number_users++;
    }
}

void free_ptr_array(gpointer data) {
    GPtrArray *array = (GPtrArray *)data;
    for (guint i = 0; i < array->len; i++) {
        g_free(g_ptr_array_index(array, i));
    }

    g_ptr_array_free(array, TRUE);
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->flights);
    g_hash_table_destroy(catalog->flights_id);

    g_hash_table_destroy(catalog->users);
    g_hash_table_destroy(catalog->users_id);

    free(catalog);
}

