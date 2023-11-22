/**
 * @file flights_c.c
 * @brief This file contains the implementation of the flights catalog and related functions.
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

#include "catalogs/flights_c.h"

#include <glib.h>
#include <stdio.h>

/**
 * @struct flights_catalog
 * @brief Flight catalog structure that stores information about flights.
 */
struct flights_catalog {
    GHashTable* flights; /**< Hash table that maps flight IDs to flight objects.*/
    GHashTable* flights_id; /**< Hash table to link the key to the flight_id. */
    GPtrArray* flights_key; /**< Hash table to link the flight_id to the key. */
};

FLIGHTS_C create_flight_c(void){
    FLIGHTS_C new_catalog = malloc(sizeof(struct flights_catalog));

    new_catalog->flights = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify) free_flight);
    new_catalog->flights_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    new_catalog->flights_key = g_ptr_array_new_with_free_func(free);

    return new_catalog;
}

void insert_flight_c(FLIGHT flight, FLIGHTS_C catalog, gpointer key){
    g_hash_table_insert(catalog->flights, key, flight);
}

FLIGHT get_flight_by_id(FLIGHTS_C catalog, char* id){
    gpointer flight_id = g_hash_table_lookup(catalog->flights_id, id);
    if (flight_id == NULL) return NULL;
    return get_flight_by_gpointer(catalog,flight_id);
}

FLIGHT get_flight_by_gpointer(FLIGHTS_C catalog, gpointer flight_id){
    return g_hash_table_lookup(catalog->flights, flight_id);
}

char* get_flight_from_key(FLIGHTS_C catalog, gpointer flight){
    return g_ptr_array_index(catalog->flights_key,GPOINTER_TO_INT(flight)-1);
}

GHashTable* get_hash_table_flight(FLIGHTS_C catalog){
    return catalog->flights;
}

void set_catalog_flight(FLIGHTS_C catalog, FLIGHT flight, char* id){

    static int number_flights = 1;

    // Create a copy of the flight ID and insert it into the flight_id hashtable
    char* copy_id = g_strdup(id);
    gpointer flight_id = GINT_TO_POINTER(number_flights);
    g_hash_table_insert(catalog->flights_id, copy_id, flight_id);

    // Create a copy of the flight ID and insert it into the flight_key GPtrArray
    char* copy_id2 = g_strdup(id);
    g_ptr_array_insert(catalog->flights_key, number_flights-1, copy_id2);
    set_flight_id(flight, flight_id);

    number_flights++;
}

void remove_flight_from_hash_table(FLIGHTS_C flights, char* flight_id) {
    gpointer flight = g_hash_table_lookup(flights->flights_id, flight_id);

    if (flight != NULL) {
        g_hash_table_remove(flights->flights, flight);

        g_hash_table_remove(flights->flights_id, flight_id);
    }
}

void free_flight_c(FLIGHTS_C catalog){
    g_hash_table_destroy(catalog->flights);
    g_hash_table_destroy(catalog->flights_id);
    g_ptr_array_free(catalog->flights_key, TRUE);
    free(catalog);
}
