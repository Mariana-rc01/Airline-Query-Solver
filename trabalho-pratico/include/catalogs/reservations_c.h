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
void insert_reservations_c(RESERV reserv, RESERV_C catalog, gpointer key);

/**
 * @brief Inserts a reservation ID into the user's reservations array in the reservations catalog.
 *
 * @param reserv_id The reservation ID to be inserted.
 * @param catalog The reservations catalog.
 * @param key The key (user ID) to associate with the reservation in the hash table.
 */
void insert_usersReservations_c(char* reserv_id, RESERV_C catalog, gpointer key);

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
 * @brief Retrieves a reservation by reservation ID (stored as a gpointer) from the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @param reserv_id The reservation ID stored as a gpointer.
 * @return The reservation object if found, or NULL if not found.
 */
RESERV get_reservations_by_gpointer(RESERV_C catalog, gpointer reserv_id);

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
 * @brief Retrieves the array of reservation IDs associated with a user by user ID (stored as a gpointer).
 *
 * @param catalog The reservations catalog.
 * @param user_id The user ID stored as a gpointer.
 * @return The array of reservation IDs if found, or NULL if not found.
 */
GPtrArray* get_user_reserv_array_by_gpointer(RESERV_C catalog, gpointer user_id);

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
 * @brief Retrieves the user ID associated with a user key in the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @param user The user key associated with the user.
 * @return The user ID if found, or NULL if not found.
 */
char* get_user_from_key(RESERV_C catalog, gpointer user);

/**
 * @brief Retrieves the reservation ID associated with a reserv key in the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @param reserv The reserv key associated with the reservation.
 * @return The reservation ID if found, or NULL if not found.
 */
char* get_reserv_from_key(RESERV_C catalog, gpointer reserv);

/**
 * @brief Retrieves the hash table containing the reservations catalog.
 *
 * @param catalog The reservations catalog.
 * @return The hash table containing reservation records.
 */
GHashTable* get_hash_table_reserv(RESERV_C catalog);

/**
 * @brief Sets the catalog information for a reservation.
 *
 * This function adds to the catalog hash table the records of a reservation, and 
 * links its keys with their corresponding ID string in other hash tables.
 *
 * @param catalog The reservations catalog.
 * @param reserv The reservation object.
 * @param id The reservation ID.
 * @param user_id The user ID.
 */
void set_catalog_reserv(RESERV_C catalog, RESERV reserv, char* id, char* user_id);


/**
 * @brief Frees the memory used by the reservations catalog.
 * @param catalog A pointer to the reservations catalog.
 */
void free_reservations_c(RESERV_C catalog);


#endif
