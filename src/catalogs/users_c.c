/**
 * @file users_c.c
 * @brief This file contains the implementation of the users catalog and related functions.
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

#include "catalogs/users_c.h"
#include "entities/users.h"

/**
 * @struct users_catalog
 * @brief User catalog structure that stores information about users.
 */
struct users_catalog {
    GHashTable* users; /**< Hash table that maps user IDs to user objects. */
};

USERS_C create_user_c(void){
    USERS_C new = malloc(sizeof(struct users_catalog));

    new->users = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify) free_user);

    return new;
}

void insert_user_c(USER user, USERS_C catalog){
    char* key = get_user_id(user);
    g_hash_table_insert(catalog->users, key, user);
}

USER get_user_by_id(USERS_C catalog, char* id){
    return g_hash_table_lookup(catalog->users, id);
}

void free_user_c(USERS_C catalog){
    g_hash_table_destroy(catalog->users);
    free(catalog);
}
