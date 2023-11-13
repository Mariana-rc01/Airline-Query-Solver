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
    GHashTable* users_id; /**< Hash table that maps id_user(int) to id_user(char)*/
};

USERS_C create_user_c(void){
    USERS_C new = malloc(sizeof(struct users_catalog));

    new->users = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_user);
    new->users_id = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    return new;
}

void insert_user_c(USER user, USERS_C catalog, gpointer key){
    g_hash_table_insert(catalog->users, key, user);
}

USER get_user_by_id(USERS_C catalog, char* id){
    gpointer user_id = g_hash_table_lookup(catalog->users_id, id);
    if (user_id == NULL) return NULL;
    return get_user_by_gpointer(catalog, user_id);
}

USER get_user_by_gpointer(USERS_C catalog, gpointer user_id){
    return g_hash_table_lookup(catalog->users,user_id);
}

void update_user_c(USERS_C catalog, char* id, double cost){
    USER user = get_user_by_id(catalog, id);
    if (user == NULL) return;
    double total = get_user_total_spent(user);

    set_user_total_spent(user, total + cost);
}

void set_catalog_user(USERS_C catalog, USER user, char* id){

    static int number_users = 1;

    char* copy_id = g_strdup(id);
    gpointer user_id = GINT_TO_POINTER(number_users);
    g_hash_table_insert(catalog->users_id, copy_id, user_id);

    set_user_id(user, user_id);

    number_users++;
}

void free_user_c(USERS_C catalog){
    g_hash_table_destroy(catalog->users);
    g_hash_table_destroy(catalog->users_id);
    free(catalog);
}
