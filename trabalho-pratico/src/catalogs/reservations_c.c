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

/**
 * @struct reservations_catalog
 * @brief A catalog for storing reservation records.
 */
struct reservations_catalog {
    GHashTable* reserv; /**< Hash table to store reservation records. */
    GHashTable* user; /**< Hash table to store all user's reservations*/
    GHashTable* hotel; /**< Hash table to store all hotel's reservations.*/
    GHashTable* reservNumber;
};

RESERV_C create_reservations_c(void){
    RESERV_C new = malloc(sizeof(struct reservations_catalog));

    new->reserv = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_reservations);
    new->user = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    new->hotel = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    new->reservNumber = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    return new;
}

void insert_reservations_c(RESERV reserv, RESERV_C catalog, char* key){
    g_hash_table_insert(catalog->reserv, key, reserv);
}

void insert_usersReservations_c(char* reserv_id, RESERV_C catalog, char* key){
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

void insert_hotelsReservations_c(char* reserv_id, RESERV_C catalog, char* key){
    if(g_hash_table_contains(catalog->hotel, key)){
        GPtrArray* reservations = g_hash_table_lookup(catalog->hotel, key);
        g_ptr_array_add(reservations, reserv_id);
    }
    else{
        GPtrArray* reservations = g_ptr_array_new();
        g_ptr_array_add(reservations, reserv_id);
        g_hash_table_insert(catalog->hotel, key, reservations);
    }
}

void insert_reservNumber_c(RESERV_C catalog, char* key, char* day){
    int dayN = ourAtoi(day);
    if (g_hash_table_contains(catalog->reservNumber, key)){
        int* days = g_hash_table_lookup(catalog->reservNumber, key);
        days[dayN - 1]++;
        free(key);
    } else{
        int* days = g_new(int, 31);
        memset(days, 0, sizeof(int) * 31);
        days[dayN - 1]++;
        g_hash_table_insert(catalog->reservNumber, key, days);
    }
}

int* get_reservNumber_c(RESERV_C catalog, char* key){
    return g_hash_table_lookup(catalog->reservNumber, key);
}

RESERV get_reservations_by_id(RESERV_C catalog, char* id){
    return g_hash_table_lookup(catalog->reserv, id);
}

GPtrArray* get_user_reserv_array_by_id(RESERV_C catalog, char* user_id){
    return g_hash_table_lookup(catalog->user, user_id);
}

GPtrArray* get_hotel_reserv_array_by_id(RESERV_C catalog, char* hotel_id){
    return g_hash_table_lookup(catalog->hotel, hotel_id);
}

int get_user_array_reserv_id(RESERV_C catalog, char* id){
    GPtrArray* user_array = get_user_reserv_array_by_id(catalog, id);
    if (!user_array) return 0;
    return user_array->len;
}

int get_number_reserv_id(RESERV_C catalog){
    return g_hash_table_size(catalog->reserv);
}

GHashTable* get_hash_table_reserv(RESERV_C catalog){
    return catalog->reserv;
}

void free_reservations_c(RESERV_C catalog){
    g_hash_table_destroy(catalog->reserv);

    // Free user hash table
    GHashTableIter iter;
    gpointer user_id, user_reservations;
    g_hash_table_iter_init(&iter, catalog->user);
    while (g_hash_table_iter_next(&iter, &user_id, &user_reservations)) {
        // Free the GPtrArray associated with each user
        GPtrArray *reservations_array = user_reservations;
        g_ptr_array_free(reservations_array, TRUE);
    }

    g_hash_table_destroy(catalog->user);

    // Free user hash table
    GHashTableIter iter1;
    gpointer hotel_id, hotel_reservations;
    g_hash_table_iter_init(&iter1, catalog->hotel);
    while (g_hash_table_iter_next(&iter1, &hotel_id, &hotel_reservations)) {
        // Free the GPtrArray associated with each user
        GPtrArray *reservations_array = hotel_reservations;
        g_ptr_array_free(reservations_array, TRUE);
    }

    g_hash_table_destroy(catalog->hotel);

    // Free user hash table
    GHashTableIter iter2;
    gpointer reserv_id, reservations;
    g_hash_table_iter_init(&iter2, catalog->reservNumber);
    while (g_hash_table_iter_next(&iter2, &reserv_id, &reservations)) {
        // Free the GPtrArray associated with each user
        int* reservations_array = reservations;
        g_free(reservations_array);
    }
    g_hash_table_destroy(catalog->reservNumber);

    free(catalog);
}

