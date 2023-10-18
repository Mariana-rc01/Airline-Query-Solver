/**
 * @file reservantions.h
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

#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct reservations *RESERV;

#include "menuNdata/statistics.h"

RESERV create_reservation(void);

void set_id(RESERV res, char* i);

void set_user_id(RESERV res, char* u_id);

void set_hotel_id(RESERV res, char* h_id);

void set_hotel_name(RESERV res, char* h_name);

void set_hotel_stars(RESERV res, int stars);

void set_city_tax(RESERV res, char* c_tax);

void set_address(RESERV res, char** address);

void set_begin_date(RESERV res, char* b_date);

void set_end_date(RESERV res, char* e_date);

void set_price_per_night(RESERV res, char* price);

void set_includes_breakfast(RESERV res, char* inc_breakfast);

void set_room_details(RESERV res, char* r_details);

void set_rating(RESERV res, char* ratin);

void set_commnet(RESERV res, char* comm);

char* get_id(RESERV res);

char* get_user_id(RESERV res);

char* get_hotel_id(RESERV res);

char* get_hotel_name(RESERV res);

int get_hotel_stars(RESERV res);

char* get_city_tax(RESERV res);

char* get_address(RESERV res);

int get_begin_date(RESERV res);

int get_end_date(RESERV res);

char* get_price_per_night(RESERV res);

char* get_includes_breakfast(RESERV res);

char* get_room_details(RESERV res);

char* get_rating(RESERV res);

char* get_comment(RESERV res);

void free_reservations(RESERV res);

int verify_reservations(char** fields);

void build_reservations(char  **reservations_fields, void *catalog, STATS stats);

#endif
