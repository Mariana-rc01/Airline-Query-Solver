/**
 * @file manager_c.h
 * @brief This file contains the definition of all catalogs jointed and related functions.
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

#ifndef MANAGER_C_H
#define MANAGER_C_H

/**
 * @brief A manager catalog structure that contains various related catalogs.
 */
typedef struct manager_catalog *MANAGER;

#include "catalogs/flights_c.h"
#include "catalogs/users_c.h"
#include "catalogs/passengers_c.h"
#include "catalogs/reservations_c.h"

/**
 * @brief Create a new manager catalog.
 *
 * @param users_c User catalog
 * @param flights_c Flight catalog
 * @param reserv_c Reservation catalog
 * @param pass_c Passenger catalog
 * @return A dynamically allocated new manager catalog.
 */
MANAGER create_manager_c(USERS_C users_c, FLIGHTS_C flights_c, RESERV_C reserv_c, PASS_C pass_c);

/**
 * @brief Get the user catalog from a manager catalog.
 *
 * @param catalog The manager catalog.
 * @return The user catalog.
 */
USERS_C get_users_c(MANAGER catalog);

/**
 * @brief Get the flight catalog from a manager catalog.
 *
 * @param catalog The manager catalog.
 * @return The flight catalog.
 */
FLIGHTS_C get_flights_c(MANAGER catalog);

/**
 * @brief Get the reservation catalog from a manager catalog.
 *
 * @param catalog The manager catalog.
 * @return The reservation catalog.
 */
RESERV_C get_reserv_c(MANAGER catalog);

/**
 * @brief Get the passenger catalog from a manager catalog.
 *
 * @param catalog The manager catalog.
 * @return The passenger catalog.
 */
PASS_C get_pass_c(MANAGER catalog);

/**
 * @brief Free the memory allocated for a manager catalog.
 *
 * @param catalog The manager catalog to be freed.
 */
void free_manager_c(MANAGER catalog);

#endif
