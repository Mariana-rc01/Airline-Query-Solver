/**
 * @file passengers.h
 * @brief
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

typedef struct passengers *PASS;

#include "menuNdata/statistics.h"

PASS create_passengers(void);

void set_flight_id(PASS pass, int f_id);

void set_user_id(PASS pass, char* u_id);

int get_flight_id(PASS pass);

char* get_user_id(PASS pass);

void free_passengers(PASS pass);

int verifiy_passengers(char** passengers_fields);

void build_passengers(char** passengers_fields, void* catalog, STATS stats);

#endif
