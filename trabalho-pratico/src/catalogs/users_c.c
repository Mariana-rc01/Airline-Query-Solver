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

/**
 * @struct users_catalog
 * @brief User catalog structure that stores information about users.
 */
struct users_catalog {
    GHashTable* users; /**< Hash table that maps user IDs to user objects. */
    GHashTable* usersNumber; /**< Hash table that maps number of users for each year and month. */
};

USERS_C create_user_c(void){
    USERS_C new = malloc(sizeof(struct users_catalog));

    new->users = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_user);
    new->usersNumber = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    return new;
}

void insert_user_c(USER user, USERS_C catalog, char* key){
    g_hash_table_insert(catalog->users, key, user);
}

void insert_userNumber_c(USERS_C catalog, char* key, char* day){
    int dayN = ourAtoi(day);
    if (g_hash_table_contains(catalog->usersNumber, key)){
        int *days = g_hash_table_lookup(catalog->usersNumber, key);
        days[dayN - 1]++;
        free(key);
    } else{
        int* days = g_new(int, 31);
        memset(days, 0, sizeof(int) * 31);
        days[dayN - 1]++;
        g_hash_table_insert(catalog->usersNumber, key, days);
    }
}

int* get_userNumber_c(USERS_C catalog, char* key){
    return g_hash_table_lookup(catalog->usersNumber, key);
}

USER get_user_by_id(USERS_C catalog, char* id){
    return g_hash_table_lookup(catalog->users,id);
}

void update_user_c(USERS_C catalog, char* id, double cost){
    USER user = get_user_by_id(catalog, id);
    if (user == NULL) return;
    double total = get_user_total_spent(user);

    set_user_total_spent(user, total + cost);
}

void free_user_c(USERS_C catalog){
    g_hash_table_destroy(catalog->users);

    // Free user hash table
    GHashTableIter iter2;
    gpointer reserv_id, reservations;
    g_hash_table_iter_init(&iter2, catalog->usersNumber);
    while (g_hash_table_iter_next(&iter2, &reserv_id, &reservations)) {
        // Free the GPtrArray associated with each user
        int* reservations_array = reservations;
        g_free(reservations_array);
    }
    g_hash_table_destroy(catalog->usersNumber);
    free(catalog);
}

GHashTable* get_hash_table_users(USERS_C catalog){
    return catalog->users;
}
