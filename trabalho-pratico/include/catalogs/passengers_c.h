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


#include <glib.h>

/**
 * @typedef PASS_C
 * @brief A pointer to a passengers catalog.
 */
typedef struct passengers_catalog *PASS_C;

#include "utils/utils.h"

/**
 * @brief Creates a new passengers catalog.
 * @return A pointer to the newly created passengers catalog.
 */
PASS_C create_passengers_c(void);

/**
 * @brief Inserts a flight ID into the array of flights associated with a user in the passengers catalog.
 *
 * @param flight_id The flight ID to be inserted.
 * @param catalog The passengers catalog.
 * @param key The key (user ID) to associate with the flight in the hash table.
 */
void insert_pass_user_c(char* flight_id, PASS_C catalog, char* key);

/**
 * @brief Inserts a passenger into the passengers catalog for a given key.
 *
 * @param catalog The passengers catalog structure.
 * @param key The key under which the passenger should be stored in the catalog.
 * @param user The user to be added to the catalog.
 */
void insert_passengers_c(PASS_C catalog, char* key, char* user);

/**
 * @brief Retrieves the array of passengers for a given key from the passengers catalog.
 *
 * @param catalog The passengers catalog structure.
 * @param key The key for which the array of passengers should be retrieved.
 * @return A pointer to a GPtrArray representing the array of passengers.
 *         Returns NULL if the key is not found in the catalog.
 */
GPtrArray* get_passengers_c(PASS_C catalog, char* key);

/**
 * @brief Retrieves the array of user IDs associated with a flight by flight ID.
 *
 * @param catalog The passengers catalog.
 * @param id The flight ID.
 * @return The array of user IDs if found, or NULL if not found.
 */
GPtrArray* get_user_array_by_id(PASS_C catalog, char* id);

/**
 * @brief Retrieves the number of user IDs associated with a flight by flight ID.
 *
 * @param catalog The passengers catalog.
 * @param id The flight ID.
 * @return The number of user IDs if found, or 0 if not found.
 */
int get_user_array_number_id(PASS_C catalog, char* id);

/**
 * @brief Frees the memory used by the passengers catalog.
 * @param catalog A pointer to the passengers catalog.
 */
void free_passengers_c(PASS_C catalog);

#endif

