/**
 * @file passengers_c.h
 * @brief This file contains the definition of the passengers catalog struct and related functions.
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

#ifndef PASSENGERS_C_H
#define PASSENGERS_C_H

#include <glib.h>

/**
 * @typedef PASS_C
 * @brief A pointer to a passengers catalog.
 */
typedef struct passengers_catalog *PASS_C;

#include "entities/passengers.h"

/**
 * @brief Creates a new passengers catalog.
 * @return A pointer to the newly created passengers catalog.
 */
PASS_C create_passengers_c(void);

void insert_pass_flight_c(char* user_id, PASS_C catalog, gpointer key);

void insert_pass_user_c(char* flight_id, PASS_C catalog, gpointer key);

GPtrArray* get_flight_array_by_id(PASS_C catalog, char* id);

GPtrArray* get_flight_array_by_gpointer(PASS_C catalog, gpointer flight_id);

int get_flight_array_number_by_id(PASS_C catalog, char* id);

GPtrArray* get_user_array_by_id(PASS_C catalog, char* id);

GPtrArray* get_user_array_by_gpointer(PASS_C catalog, gpointer user_id);

int get_user_array_number_id(PASS_C catalog, char* id);

void set_catalog_passenger(PASS_C catalog, PASS pass, char* user_id, char* flight_id);

/**
 * @brief Frees the memory used by the passengers catalog.
 * @param catalog A pointer to the passengers catalog.
 */
void free_passengers_c(PASS_C catalog);

#endif

