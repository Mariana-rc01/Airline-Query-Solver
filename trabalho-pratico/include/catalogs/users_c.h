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


#include <glib.h>

/**
 * @typedef USERS_C
 * @brief A pointer to the user catalog structure.
 */
typedef struct users_catalog *USERS_C;

#include "entities/users.h"
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
void insert_user_c(USER user, USERS_C catalog,char* key);

/**
 * @brief Get a user based on the user ID.
 *
 * @param catalog The user catalog.
 * @param id The ID will be used for the lookup.
 *
 * @return The user corresponding to the specified ID or NULL if not found.
 */
USER get_user_by_id(USERS_C catalog, char* id);

void update_user_c(USERS_C catalog, char* id, double cost);

void set_catalog_user(USERS_C catalog, USER user, char* id);

/**
 * @brief Free the allocated memory for the user catalog.
 *
 * Releases the resources associated with the catalog, including the hash tables and the structure itself.
 *
 * @param catalog The user catalog to be freed.
 */
void free_user_c(USERS_C catalog);

#endif
