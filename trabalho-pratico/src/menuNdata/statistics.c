/**
 * @file statistics.c
 * @brief Module that connects all the entities
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

#include "menuNdata/statistics.h"
#include "utils/utils.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct statistics{
    GHashTable* hotels;
    GHashTable* hotels_id;
    GPtrArray* hotel_key;
};

STATS create_stats(void){
    STATS new = malloc(sizeof(struct statistics));

    new->hotels = g_hash_table_new_full(NULL,g_direct_equal,NULL,NULL);
    new->hotels_id = g_hash_table_new_full(g_str_hash,g_str_equal, free, NULL);
    new->hotel_key = g_ptr_array_new_with_free_func(free);

    return new;
}

void insert_hotel_c(char* reserv_id, STATS stats, gpointer hotel_id){
    if (g_hash_table_contains(stats->hotels,hotel_id)){
        GPtrArray* reservs = g_hash_table_lookup(stats->hotels, hotel_id);
        g_ptr_array_add(reservs, reserv_id);
    }
    else{
        GPtrArray* reservs = g_ptr_array_new();
        g_ptr_array_add(reservs,reserv_id);
        g_hash_table_insert(stats->hotels, hotel_id, reservs);
    }
}

GPtrArray* get_hotel_reserv_by_id(STATS stats, char* hotel_id){
    gpointer hotel = g_hash_table_lookup(stats->hotels_id,hotel_id);
    if (hotel == NULL) return NULL;
    return get_hotel_reserv_by_gpointer(stats, hotel);
}

GPtrArray* get_hotel_reserv_by_gpointer(STATS stats, gpointer hotel_id){
    return g_hash_table_lookup(stats->hotels, hotel_id);
}

char* get_hotel_from_key(STATS catalog, gpointer hotel) {
    return g_ptr_array_index(catalog->hotel_key, GPOINTER_TO_INT(hotel) - 1);
}

void set_stats_hotel(STATS catalog, RESERV reserv, char* hotel_id){
    static int number_hotel = 1;

    if (g_hash_table_contains(catalog->hotels_id, hotel_id)){
        gpointer hotel = g_hash_table_lookup(catalog->hotels_id, hotel_id);
        set_hotel_id(reserv, hotel);
    }
    else {
        char* copy_hotel = g_strdup(hotel_id);
        gpointer hotel = GINT_TO_POINTER(number_hotel);
        g_hash_table_insert(catalog->hotels_id, copy_hotel,hotel);
        set_hotel_id(reserv,hotel);

        char* copy2 = strdup(hotel_id);
        g_ptr_array_insert(catalog->hotel_key,number_hotel-1, copy2);
        number_hotel++;
    }
}

