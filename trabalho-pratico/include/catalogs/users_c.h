/**
 * @file users_c.h
 * @brief This file contains the definition of the users catalog and related functions.
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

#ifndef USERS_C_H
#define USERS_C_H

#include "entities/users.h"
#include "utils/utils.h"

#include <glib.h>

/**
 * @typedef USERS_C
 * @brief A pointer to the user catalog structure.
 */
typedef struct users_catalog *USERS_C;

/**
 * @brief Create a new instance of USERS_C.
 *
 * Allocates memory for a user catalog structure and initializes the hash tables.
 *
 * @return A new instance of USERS_C.
 */
USERS_C create_user_c(void);

/**
 * @brief Insert a user into the user catalog.
 *
 * @param user The user to be inserted.
 * @param catalog The user catalog.
 */
void insert_user_c(USER user, USERS_C catalog, char* key);

/**
 * @brief Inserts or updates the count of users for a given user ID on a specific day.
 *
 * @param catalog The users catalog structure.
 * @param key The user ID to be inserted or updated.
 * @param day The day of the month for which the user count should be updated.
 */
void insert_userNumber_c(USERS_C catalog, char* key, char* day);

/**
 * @brief Retrieves the count of users for a given user ID in the users catalog.
 *
 * @param catalog The users catalog structure.
 * @param key The user ID for which the count should be retrieved.
 * @return A pointer to an array representing the count of users for each day in a month.
 *         Returns NULL if the user ID is not found in the catalog.
 */
int* get_userNumber_c(USERS_C catalog, char* key);

/**
 * @brief Retrieves a user by user ID from the users catalog.
 *
 * @param catalog The users catalog.
 * @param id The user ID.
 * @return The user object if found, or NULL if not found.
 */
USER get_user_by_id(USERS_C catalog, char* id);

/**
 * @brief Updates the total amount spent by a user in the users catalog.
 *
 * @param catalog The users catalog.
 * @param id The user ID.
 * @param cost The additional cost to be added to the user's total.
 */
void update_user_c(USERS_C catalog, char* id, double cost);

/**
 * @brief Free the allocated memory for the user catalog.
 *
 * Releases the resources associated with the catalog, including the hash tables and the structure itself.
 *
 * @param catalog The user catalog to be freed.
 */
void free_user_c(USERS_C catalog);

/**
 * @brief Retrieves the hash table containing user information from the users catalog.
 *
 * @param catalog The users catalog structure.
 * @return A pointer to the GHashTable containing user information.
 */
GHashTable* get_hash_table_users(USERS_C catalog);

#endif
