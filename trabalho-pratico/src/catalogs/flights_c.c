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
    GHashTable* flightsNumber; /**< Hash table that maps flight numbers to flight objects. */
};

FLIGHTS_C create_flight_c(void){
    FLIGHTS_C new_catalog = malloc(sizeof(struct flights_catalog));

    new_catalog->flights = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify) free_flight);
    new_catalog->flightsNumber = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    return new_catalog;
}

void insert_flight_c(FLIGHT flight, FLIGHTS_C catalog, char* key){
    g_hash_table_insert(catalog->flights, key, flight);
}

void insert_flightNumber_c(FLIGHTS_C catalog, char* key, char* day){
    int dayN = ourAtoi(day);
    if (g_hash_table_contains(catalog->flightsNumber, key)){
        int *days = g_hash_table_lookup(catalog->flightsNumber, key);
        days[dayN - 1]++;
        free(key);
    } else{
        int* days = g_new(int, 31);
        memset(days, 0, sizeof(int) * 31);
        days[dayN - 1]++;
        g_hash_table_insert(catalog->flightsNumber, key, days);
    }
}

int* get_flightNumber_c(FLIGHTS_C catalog, char* key){
    return g_hash_table_lookup(catalog->flightsNumber, key);
}

FLIGHT get_flight_by_id(FLIGHTS_C catalog, char* id){
    return g_hash_table_lookup(catalog->flights, id);
}

GHashTable* get_hash_table_flight(FLIGHTS_C catalog){
    return catalog->flights;
}

void update_flight_c(FLIGHTS_C catalog, char* id){
    FLIGHT flight = get_flight_by_id(catalog, id);
    if (flight == NULL) return;
    int total = get_flight_nPassengers(flight);

    set_flight_nPassengers(flight, total + 1);
}

void remove_flight_from_hash_table(FLIGHTS_C flights, char* flight_id) {
    g_hash_table_remove(flights->flights, flight_id);
}

void free_flight_c(FLIGHTS_C catalog){
    g_hash_table_destroy(catalog->flights);

    // Free user hash table
    GHashTableIter iter2;
    gpointer reserv_id, reservations;
    g_hash_table_iter_init(&iter2, catalog->flightsNumber);
    while (g_hash_table_iter_next(&iter2, &reserv_id, &reservations)) {
        // Free the GPtrArray associated with each user
        int* reservations_array = reservations;
        g_free(reservations_array);
    }
    g_hash_table_destroy(catalog->flightsNumber);
    free(catalog);
}
