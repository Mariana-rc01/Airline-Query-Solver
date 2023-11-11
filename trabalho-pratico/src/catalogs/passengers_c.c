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
    GHashTable *flights; /**< Hash table to store passengers of flights records.*/
    GHashTable *users; /**< Hash table to store flights of users records. */
    GHashTable *totalPassengers; /**< Hash table to store total passengers' flights records. */
};

PASS_C create_passengers_c(void){
    PASS_C new_catalog = malloc(sizeof(struct passengers_catalog));

    new_catalog->flights = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
    new_catalog->users = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
    new_catalog->totalPassengers = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);

    return new_catalog;
}

void insert_passenger_c(PASS pass, PASS_C catalog){
    char* flight = get_flight_P(pass);
    char* user = get_user_P(pass);
    // Addes id_user to GArray associated to flight_id
    GArray* usersForFlight = g_hash_table_lookup(catalog->flights, flight);
    if (usersForFlight == NULL){
        usersForFlight = g_array_new(FALSE,FALSE, sizeof(char*));
        g_hash_table_insert(catalog->flights,flight,usersForFlight);
    }
    g_array_append_val(usersForFlight,user);

    GArray* flightsForUser = g_hash_table_lookup(catalog->users,user);
    if (flightsForUser == NULL){
        flightsForUser = g_array_new(FALSE,FALSE, sizeof(char*));
        g_hash_table_insert(catalog->users,user,flightsForUser);
    }
    g_array_append_val(flightsForUser,flight);

    int *countPassengers = g_hash_table_lookup(catalog->totalPassengers,flight);
    if (countPassengers == NULL){
        countPassengers = g_new(int,1);
        *countPassengers = 1;
        g_hash_table_insert(catalog->totalPassengers,flight,countPassengers);
    }
    else {
        (*countPassengers)++;
    }
}

int get_total_passengers_c(PASS_C catalog, char* flight_id){
    int *countPassengers = g_hash_table_lookup(catalog->totalPassengers,flight_id);
    if (countPassengers != NULL) {
        return ((int)*countPassengers);
    }
    return 0;
}

GArray* get_users_for_flight(PASS_C catalog, char *flight_id){
    return (g_hash_table_lookup(catalog->flights, flight_id));
}

GArray* get_flights_for_user(PASS_C catalog, char *user_id){
    return (g_hash_table_lookup(catalog->users, user_id));
}

void free_passengers_c(PASS_C catalog){
    g_hash_table_destroy(catalog->flights);
    g_hash_table_destroy(catalog->users);
    g_hash_table_destroy(catalog->totalPassengers);
    free(catalog);
}

