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

#include <glib.h>

/**
 * @typedef FLIGHTS_C
 * @brief A pointer to the flight catalog structure.
 */
typedef struct flights_catalog *FLIGHTS_C;

#include "entities/flights.h"

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
void insert_flight_c(FLIGHT flight, FLIGHTS_C catalog, char* key);

/**
 * @brief Inserts or updates the count of flights for a given flight number on a specific day.
 *
 * @param catalog The flights catalog structure.
 * @param key The flight number to be inserted or updated.
 * @param day The day of the month for which the flight count should be updated.
 */
void insert_flightNumber_c(FLIGHTS_C catalog, char* key, char* day);

/**
 * @brief Retrieves the count of flights for a given flight number in the flights catalog.
 *
 * @param catalog The flights catalog structure.
 * @param key The flight number for which the count should be retrieved.
 * @return A pointer to an array representing the count of flights for each day in a month.
 *         Returns NULL if the flight number is not found in the catalog.
 */
int* get_flightNumber_c(FLIGHTS_C catalog, char* key);

/**
 * @brief Get a flight by its ID.
 *
 * @param catalog The flight catalog.
 * @param flight The flight whose ID will be used for the lookup.
 *
 * @return The flight corresponding to the specified ID or NULL if not found.
 */
FLIGHT get_flight_by_id(FLIGHTS_C catalog, char* id);

/**
 * @brief Retrieves the hash table of flights from the flights catalog.
 *
 * @param catalog The flights catalog.
 * @return The hash table of flights.
 */
GHashTable* get_hash_table_flight(FLIGHTS_C catalog);

/**
 * @brief Updates the number of passengers for a given flight in the flights catalog.
 *
 *
 * @param catalog The flights catalog structure.
 * @param id The id of the flight for which the number of passengers should be updated.
 */
void update_flight_c(FLIGHTS_C catalog, char* id);

/**
 * @brief Removes a flight from the flights catalog.
 *
 * This function removes a flight identified by its ID from the flights catalog.
 *
 * @param flights A pointer to the flights catalog.
 * @param flight_id The ID of the flight to be removed.
 */
void remove_flight_from_hash_table(FLIGHTS_C flights, char* flight_id);

/**
 * @brief Free the allocated memory for the flight catalog.
 *
 * Releases the resources associated with the catalog, including the hash table and the structure itself.
 *
 * @param catalog The flight catalog to be freed.
 */
void free_flight_c(FLIGHTS_C catalog);

#endif
