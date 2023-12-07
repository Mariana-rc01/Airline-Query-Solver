/**
 * @file passengers.h
 * @brief This file contains the definition of the passengers struct and related functions.
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

#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "catalogs/users_c.h"
#include "catalogs/flights_c.h"
#include "IO/input.h"

/**
 * @brief Verifies the validity of passenger data.
 * @param passengers_fields An array of passenger data fields.
 * @return 1 if the passenger data is valid, 0 otherwise.
 */
int verify_passengers(char** passengers_fields, USERS_C users, FLIGHTS_C flights);

/**
 * @brief Builds a passenger struct from passenger data fields.
 * @param passengers_fields An array of passenger data fields.
 * @param catalog A pointer to the manager catalog.
 *
 * @return 1 if the passenger is added to the catalog 0 if not
 */
int build_passengers(char** passengers_fields, void* catalog);

#endif
