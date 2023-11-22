/**
 * @file passengers_c.h
 * @brief This file contains the definition of the passengers catalog struct and related functions.
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

#ifndef PASSENGERS_C_H
#define PASSENGERS_C_H

#include "entities/passengers.h"
#include "utils/utils.h"

#include <glib.h>

/**
 * @typedef PASS_C
 * @brief A pointer to a passengers catalog.
 */
typedef struct passengers_catalog *PASS_C;

#include "entities/passengers.h"

/**
 * @brief Creates a new passengers catalog.
 * @return A pointer to the newly created passengers catalog.
 */
PASS_C create_passengers_c(void);

/**
 * @brief Inserts a user ID into the array of passengers associated with a flight in the passengers catalog.
 *
 * @param user_id The user ID to be inserted.
 * @param catalog The passengers catalog.
 * @param key The key (flight ID) to associate with the user in the hash table.
 */
void insert_pass_flight_c(char* user_id, PASS_C catalog, gpointer key);

/**
 * @brief Inserts a flight ID into the array of flights associated with a user in the passengers catalog.
 *
 * @param flight_id The flight ID to be inserted.
 * @param catalog The passengers catalog.
 * @param key The key (user ID) to associate with the flight in the hash table.
 */
void insert_pass_user_c(char* flight_id, PASS_C catalog, gpointer key);

/**
 * @brief Retrieves the array of flight IDs associated with a user by user ID.
 *
 * @param catalog The passengers catalog.
 * @param id The user ID.
 * @return The array of flight IDs if found, or NULL if not found.
 */
GPtrArray* get_flight_array_by_id(PASS_C catalog, char* id);

/**
 * @brief Retrieves the array of flight IDs associated with a user by user ID (stored as a gpointer).
 *
 * @param catalog The passengers catalog.
 * @param flight_id The user ID stored as a gpointer.
 * @return The array of flight IDs if found, or NULL if not found.
 */
GPtrArray* get_flight_array_by_gpointer(PASS_C catalog, gpointer flight_id);

/**
 * @brief Retrieves the number of flight IDs associated with a user by user ID.
 *
 * @param catalog The passengers catalog.
 * @param id The user ID.
 * @return The number of flight IDs if found, or 0 if not found.
 */
int get_flight_array_number_by_id(PASS_C catalog, char* id);

/**
 * @brief Retrieves the array of user IDs associated with a flight by flight ID.
 *
 * @param catalog The passengers catalog.
 * @param id The flight ID.
 * @return The array of user IDs if found, or NULL if not found.
 */
GPtrArray* get_user_array_by_id(PASS_C catalog, char* id);

/**
 * @brief Retrieves the array of user IDs associated with a flight by flight ID (stored as a gpointer).
 *
 * @param catalog The passengers catalog.
 * @param user_id The flight ID stored as a gpointer.
 * @return The array of user IDs if found, or NULL if not found.
 */
GPtrArray* get_user_array_by_gpointer(PASS_C catalog, gpointer user_id);

/**
 * @brief Retrieves the number of user IDs associated with a flight by flight ID.
 *
 * @param catalog The passengers catalog.
 * @param id The flight ID.
 * @return The number of user IDs if found, or 0 if not found.
 */
int get_user_array_number_id(PASS_C catalog, char* id);

/**
 * @brief Sets the catalog information for a passenger.
 *
 * This function adds to the catalog hash tables the records of a passenger,and
 * links its keys with their corresponding ID string in other hash tables.
 *
 * @param catalog The passengers catalog.
 * @param pass The passenger object.
 * @param user_id The user ID.
 * @param flight_id The flight ID.
 */
void set_catalog_passenger(PASS_C catalog, PASS pass, char* user_id, char* flight_id);

/**
 * @brief Removes a flight from the passengers catalog.
 *
 * This function removes a flight identified by its ID from the passengers catalog.
 *
 * @param pass A pointer to the passengers catalog.
 * @param flight_id The ID of the flight to be removed.
 */
void remove_flight_array_from_hash_table(PASS_C pass, char* flight_id);

/**
 * @brief Frees the memory used by the passengers catalog.
 * @param catalog A pointer to the passengers catalog.
 */
void free_passengers_c(PASS_C catalog);

#endif

