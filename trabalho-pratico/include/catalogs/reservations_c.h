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

void insert_usersReservations_c(char* reserv_id, RESERV_C catalog, gpointer key);

/**
 * @brief Gets a reservation record by its ID.
 * @param catalog A pointer to the reservations catalog.
 * @param id The reservation ID.
 * @return A pointer to the reservation record associated with the specified ID.
 */
RESERV get_reservations_by_id(RESERV_C catalog, char* id);

RESERV get_reservations_by_gpointer(RESERV_C catalog, gpointer reserv_id);

GPtrArray* get_user_reserv_array_by_id(RESERV_C catalog, char* user_id);

GPtrArray* get_user_reserv_array_by_gpointer(RESERV_C catalog, gpointer user_id);

char* get_key_by_value_R(RESERV_C catalog, gpointer value);

int get_user_array_reserv_id(RESERV_C catalog, char* id);

void set_catalog_reserv(RESERV_C catalog, RESERV reserv, char* id, char* user_id);

/**
 * @brief Frees the memory used by the reservations catalog.
 * @param catalog A pointer to the reservations catalog.
 */
void free_reservations_c(RESERV_C catalog);

#endif
