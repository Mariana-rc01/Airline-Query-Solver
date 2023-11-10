/**
 * @file passengers.h
 * @brief This file contains the definition of the passengers struct and related functions.
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

#ifndef PASSENGERS_H
#define PASSENGERS_H

/**
 * @typedef PASS
 * @brief Typedef for struct passengers pointer.
 */
typedef struct passengers *PASS;

#include "menuNdata/statistics.h"
#include "catalogs/users_c.h"

/**
 * @brief Creates a new passengers struct with default values.
 * @return A pointer to the newly created passenger.
 */
PASS create_passengers(void);

/**
 * @brief Sets the flight ID associated with the passenger.
 * @param pass A pointer to the passenger struct.
 * @param id The flight ID.
 */
void set_flight_P(PASS pass, char* id);

/**
 * @brief Sets the user ID of the passenger.
 * @param pass A pointer to the passenger struct.
 * @param id The user ID of the passenger.
 */
void set_user_P(PASS pass, char* id);

/**
 * @brief Gets the flight ID associated with the passenger.
 * @param pass A pointer to the passenger struct.
 * @return The flight ID.
 */
char* get_flight_P(PASS pass);

/**
 * @brief Gets the user ID of the passenger.
 * @param pass A pointer to the passenger struct.
 * @return The user ID of the passenger.
 */
char* get_user_P(PASS pass);

/**
 * @brief Frees memory associated with a passenger struct.
 * @param pass A pointer to the passenger struct.
 */
void free_passengers(PASS pass);

/**
 * @brief Verifies the validity of passenger data.
 * @param passengers_fields An array of passenger data fields.
 * @return 1 if the passenger data is valid, 0 otherwise.
 */
int verify_passengers(char** passengers_fields, USERS_C users);

/**
 * @brief Builds a passenger struct from passenger data fields.
 * @param passengers_fields An array of passenger data fields.
 * @param catalog A pointer to the manager catalog.
 * @param stats A pointer to the statistics.
 *
 * @return 1 if the passenger is added to the catalog 0 if not
 */
int build_passengers(char** passengers_fields, void* catalog, STATS stats);

#endif
