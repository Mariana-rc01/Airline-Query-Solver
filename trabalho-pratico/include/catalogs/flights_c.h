/**
 * @file flights_c.h
 * @brief This file contains the definition of the flights catalog and related functions.
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

#ifndef FLIGHTS_C_H
#define FLIGHTS_C_H

#include "entities/flights.h"

/**
 * @typedef FLIGHTS_C
 * @brief A pointer to the flight catalog structure.
 */
typedef struct flights_catalog *FLIGHTS_C;


/**
 * @brief Create a new instance of FLIGHTS_C.
 *
 * Allocates memory for a flight catalog structure and initializes the hash table.
 *
 * @return A new instance of FLIGHTS_C.
 */
FLIGHTS_C create_flight_c(void);

/**
 * @brief Insert a flight into the flight catalog.
 *
 * @param flight The flight to be inserted.
 * @param catalog The flight catalog.
 */
void insert_flight_c(FLIGHT flight, FLIGHTS_C catalog);

/**
 * @brief Get a flight by its ID.
 *
 * @param catalog The flight catalog.
 * @param flight The flight whose ID will be used for the lookup.
 *
 * @return The flight corresponding to the specified ID or NULL if not found.
 */
FLIGHT get_flight_by_id(FLIGHTS_C catalog, FLIGHT flight);

/**
 * @brief Free the allocated memory for the flight catalog.
 *
 * Releases the resources associated with the catalog, including the hash table and the structure itself.
 *
 * @param catalog The flight catalog to be freed.
 */
void free_flight_c(FLIGHTS_C catalog);

#endif
