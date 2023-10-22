/**
 * @file passengers_c.h
 * @brief This file contains the implementation of the flight struct and related functions.
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
#include <glib.h>

/**
 * @typedef PASS_C
 * @brief A pointer to a passengers catalog.
 */
typedef struct passengers_catalog *PASS_C;

/**
 * @brief Creates a new passengers catalog.
 * @return A pointer to the newly created passengers catalog.
 */
PASS_C create_passengers_c(void);

/**
 * @brief Inserts a passenger record into the passengers catalog.
 * @param pass A pointer to the passenger record.
 * @param catalog A pointer to the passengers catalog.
 */
void insert_passengers_c(PASS pass, PASS_C catalog);

/**
 * @brief Sets the flight and user ID for a passenger in the catalog.
 * @param catalog A pointer to the passengers catalog.
 * @param pass A pointer to the passenger record.
 * @param flight_id The flight ID.
 * @param user_id The user ID.
 */
void set_c_flight_id_P(PASS_C catalog, PASS pass, char* flight_id, char* user_id);

/**
 * @brief Gets the passengers by flight ID.
 * @param catalog A pointer to the passengers catalog.
 * @param flight_id The flight ID.
 * @return A string containing passenger information for the specified flight ID.
 */
char* get_c_passengers_by_flight_id(PASS_C catalog, char* flight_id);

/**
 * @brief Gets the passengers by user ID.
 * @param catalog A pointer to the passengers catalog.
 * @param user_id The user ID.
 * @return A string containing passenger information for the specified user ID.
 */
char* get_c_passengers_by_user_id(PASS_C catalog, char* user_id);

/**
 * @brief Gets a passenger record by flight ID.
 * @param catalog A pointer to the passengers catalog.
 * @param flight_id The flight ID.
 * @return A pointer to the passenger record associated with the specified flight ID.
 */
PASS get_c_passengers(PASS_C catalog, char* flight_id);

/**
 * @brief Frees the memory used by the passengers catalog.
 * @param catalog A pointer to the passengers catalog.
 */
void free_passengers_c(PASS_C catalog);


#endif
