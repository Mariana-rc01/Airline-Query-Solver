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

#include "entities/passengers.h"

/**
 * @brief Creates a new passengers catalog.
 * @return A pointer to the newly created passengers catalog.
 */
PASS_C create_passengers_c(void);

/**
 * @brief Inserts passenger information into a passenger catalog.
 *
 * This function inserts passenger information, associating a user with a flight in the catalog. 
 * It keeps track of the total number of passengers for each flight.
 *
 * @param pass The passenger information to be inserted.
 * @param catalog The passenger catalog to which the information will be added.
 */
void insert_passenger_c(PASS pass, PASS_C catalog);

/**
 * @brief Retrieves the total number of passengers for a specific flight.
 *
 * This function retrieves the total number of passengers for a given flight from the catalog.
 *
 * @param catalog The passenger catalog.
 * @param flight_id The ID of the flight for which to retrieve passenger count.
 *
 * @return The total number of passengers for the specified flight.
 */
int get_total_passengers_c(PASS_C catalog, char* flight_id);

/**
 * @brief Retrieves an array of users associated with a specific flight.
 *
 * This function retrieves an array of user IDs associated with a particular flight from the catalog.
 *
 * @param catalog The passenger catalog.
 * @param flight_id The ID of the flight for which to retrieve user information.
 *
 * @return A GArray containing user IDs for the specified flight.
 */
GArray* get_users_for_flight(PASS_C catalog, char *flight_id);

/**
 * @brief Retrieves an array of flights associated with a specific user.
 *
 * This function retrieves an array of flight IDs associated with a particular user from the catalog.
 *
 * @param catalog The passenger catalog.
 * @param user_id The ID of the user for which to retrieve flight information.
 *
 * @return A GArray containing flight IDs for the specified user.
 */
GArray* get_flights_for_user(PASS_C catalog, char *user_id);

/**
 * @brief Frees the memory used by the passengers catalog.
 * @param catalog A pointer to the passengers catalog.
 */
void free_passengers_c(PASS_C catalog);

#endif
