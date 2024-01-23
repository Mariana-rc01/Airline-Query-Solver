/**
 * @file reservations_c.h
 * @brief This file contains the definition of the reservations catalog struct and related functions.
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
#ifndef RESERVATIONS_C_H
#define RESERVATIONS_C_H

#include "entities/reservations.h"

#include <glib.h>

/**
 * @typedef RESERV_C
 * @brief A pointer to a reservations catalog.
 */
typedef struct reservations_catalog *RESERV_C;

#include "utils/utils.h"

/**
 * @brief Creates a new reservations catalog.
 * @return A pointer to the newly created reservations catalog.
 */
RESERV_C create_reservations_c(void);

/**
 * @brief Inserts a reservation record into the reservations catalog.
 * @param reserv A pointer to the reservation record.
 * @param catalog A pointer to the reservations catalog.
 */
void insert_reservations_c(RESERV reserv, RESERV_C catalog, char* key);

/**
 * @brief Inserts a reservation ID into the user's reservations array in the reservations catalog.
 *
 * @param reserv_id The reservation ID to be inserted.
 * @param catalog The reservations catalog.
 * @param key The key (user ID) to associate with the reservation in the hash table.
 */
void insert_usersReservations_c(char* reserv_id, RESERV_C catalog, char* key);

/**
 * @brief Inserts a hotel reservation ID into the hotel reservations catalog for a given key.
 *
 * @param reserv_id The ID of the hotel reservation to be inserted.
 * @param catalog The hotel reservations catalog structure.
 * @param key The key under which the reservation ID should be stored in the catalog.
 */
void insert_hotelsReservations_c(char* reserv_id, RESERV_C catalog, char* key);

/**
 * @brief Inserts or updates the count of reservations for a given reservation number on a specific day.
 *
 * @param catalog The reservations catalog structure.
 * @param key The reservation number to be inserted or updated.
 * @param day The day of the month for which the reservation count should be updated.
 */
void insert_reservNumber_c(RESERV_C catalog, char* key, char* day);

/**
 * @brief Retrieves the count of reservations for a given reservation number in the reservations catalog.
 *
 * @param catalog The reservations catalog structure.
 * @param key The reservation number for which the count should be retrieved.
 * @return A pointer to an array representing the count of reservations for each day in a month.
 *         Returns NULL if the reservation number is not found in the catalog.
 */
int* get_reservNumber_c(RESERV_C catalog, char* key);

/**
 * @brief Gets a reservation record by its ID.
 *
 * @param catalog A pointer to the reservations catalog.
 * @param id The reservation ID.
 * @return A pointer to the reservation record associated with the specified ID.
 */
RESERV get_reservations_by_id(RESERV_C catalog, char* id);

/**
 * @brief Retrieves a reservation by reservation ID from the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @param id The reservation ID.
 * @return The reservation object if found, or NULL if not found.
 */
RESERV get_reservations_by_id(RESERV_C catalog, char* id);

/**
 * @brief Retrieves the array of reservation IDs associated with a user by user ID.
 *
 *
 * @param catalog The reservations catalog.
 * @param user_id The user ID.
 * @return The array of reservation IDs if found, or NULL if not found.
 */
GPtrArray* get_user_reserv_array_by_id(RESERV_C catalog, char* user_id);

/**
 * @brief Retrieves the array of hotel reservation IDs for a given hotel ID from the hotel reservations catalog.
 *
 * @param catalog The hotel reservations catalog structure.
 * @param hotel_id The ID of the hotel for which the array of reservation IDs should be retrieved.
 * @return A pointer to a GPtrArray representing the array of hotel reservation IDs.
 *         Returns NULL if the hotel ID is not found in the catalog.
 */
GPtrArray* get_hotel_reserv_array_by_id(RESERV_C catalog, char* hotel_id);

/**
 * @brief Retrieves the number of reservation IDs associated with a user by user ID.
 *
 * @param catalog The reservations catalog.
 * @param id The user ID.
 * @return The number of reservation IDs if found, or 0 if not found.
 */
int get_user_array_reserv_id(RESERV_C catalog, char* id);

/**
 * @brief Retrieves the total number of reservation IDs in the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @return The total number of reservation IDs.
 */
int get_number_reserv_id(RESERV_C catalog);

/**
 * @brief Retrieves the hash table containing the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @return The hash table containing reservation records.
 */
GHashTable* get_hash_table_reserv(RESERV_C catalog);

/**
 * @brief Frees the memory used by the reservations catalog.
 * @param catalog A pointer to the reservations catalog.
 */
void free_reservations_c(RESERV_C catalog);

#endif
