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
    GHashTable* reserv_id; /**< Hash table to link the key to the reserv_id*/

    GHashTable* user; /**< Hash table to store all user's reservations*/
    GHashTable* user_id; /**< Hash table to link the key to the user_id*/
};

RESERV_C create_reservations_c(void){
    RESERV_C new = malloc(sizeof(struct reservations_catalog));

    new->reserv = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_reservations);
    new->reserv_id = g_hash_table_new_full(g_str_hash,g_str_equal, free, NULL);

    new->user = g_hash_table_new_full(NULL, g_direct_equal, NULL, free_ptr_array);
    new->user_id = g_hash_table_new_full(g_str_hash,g_str_equal, free, NULL);

    return new;
}

void insert_reservations_c(RESERV reserv, RESERV_C catalog, gpointer key){
    g_hash_table_insert(catalog->reserv, key, reserv);
}

void insert_usersReservations_c(char* reserv_id, RESERV_C catalog, gpointer key){
    if(g_hash_table_contains(catalog->user, key)){
        GPtrArray* reservations = g_hash_table_lookup(catalog->user, key);
        g_ptr_array_add(reservations, reserv_id);
    }
    else{
        GPtrArray* reservations = g_ptr_array_new();
        g_ptr_array_add(reservations, reserv_id);
        g_hash_table_insert(catalog->user, key, reservations);
    }
}

RESERV get_reservations_by_id(RESERV_C catalog, char* id){
    gpointer reserv_id = g_hash_table_lookup(catalog->reserv_id, id);
    if (reserv_id == NULL) return NULL;
    return get_reservations_by_gpointer(catalog, reserv_id);
}

RESERV get_reservations_by_gpointer(RESERV_C catalog, gpointer reserv_id){
    return g_hash_table_lookup(catalog->reserv, reserv_id);
}

GPtrArray* get_user_reserv_array_by_id(RESERV_C catalog, char* user_id){
    gpointer user = g_hash_table_lookup(catalog->user_id, user_id);
    if (user == NULL) return NULL;
    return get_user_reserv_array_by_gpointer(catalog, user);
}

GPtrArray* get_user_reserv_array_by_gpointer(RESERV_C catalog, gpointer user_id){
    return g_hash_table_lookup(catalog->user, user_id);
}

int get_user_array_reserv_id(RESERV_C catalog, char* id){
    GPtrArray* user_array = get_user_reserv_array_by_id(catalog, id);
    if (!user_array) return 0;
    return user_array->len;
}

void set_catalog_reserv(RESERV_C catalog, RESERV reserv, char* id, char* user_id){
    static int number_reservs = 1;
    static int number_users = 1;

    char* copy_id = g_strdup(id);
    gpointer reserv_id = GINT_TO_POINTER(number_reservs);
    g_hash_table_insert(catalog->reserv_id, copy_id, reserv_id);

    set_reservation_id(reserv, reserv_id);

    if(g_hash_table_contains(catalog->user_id, user_id)){
        gpointer user = g_hash_table_lookup(catalog->user_id, user_id);
        set_user_id_R(reserv, user);
    }
    else{
        char* copy_user = g_strdup(user_id);
        gpointer user = GINT_TO_POINTER(number_users);
        g_hash_table_insert(catalog->user_id, copy_user, user);
        set_user_id_R(reserv,user);
        number_users++;
    }

    number_reservs++;

}

void free_reservations_c(RESERV_C catalog){
    g_hash_table_destroy(catalog->reserv);
    g_hash_table_destroy(catalog->reserv_id);

    //g_hash_table_destroy(catalog->user);
    g_hash_table_destroy(catalog->user_id);

    free(catalog);
}

