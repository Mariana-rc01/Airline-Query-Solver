/**
 * @file reservations.c
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

#include "entities/reservations.h"

#include "menuNdata/statistics.h"
#include "IO/input.h"

#include <stdlib.h>
#include <string.h>

struct reservations{
    char* id;
    char* user_id;
    char* hotel_id;
    char* hotel_name;
    int hotel_stars;
    char* city_tax;
    char* address;
    int begin_date;
    int end_date;
    char* price_per_night;
    char* includes_breakfast;
    char* room_details;
    char* rating;
    char* comment;
};

RESERV create_reservation(void){
    RESERV new = malloc(sizeof(struct reservations));

    new->id = NULL;
    new->user_id = NULL;
    new->hotel_id = NULL;
    new->hotel_name = NULL;
    new->hotel_stars = 0;
    new->city_tax = NULL;
    new->address = NULL;
    new->begin_date = 0;
    new->end_date = 0;
    new->price_per_night = NULL;
    new->includes_breakfast = NULL;
    new->room_details = NULL;
    new->rating = NULL;
    new->comment = NULL;

    return new;
}

void set_reservation_id(RESERV res, char* i){
    res->id = strdup(i);
}

void set_user_id_R(RESERV res, char* u_id){
    res->user_id = strdup(u_id);
}

void set_hotel_id(RESERV res, char* h_id){
    res->hotel_id = strdup(h_id);
}

void set_hotel_name(RESERV res, char* h_name){
    res->hotel_name = strdup(h_name);
}

void set_hotel_stars(RESERV res, int stars){
    res->hotel_stars = stars;
}

void set_city_tax(RESERV res, char* c_tax){
    res->city_tax = strdup(c_tax);
}

void set_address(RESERV res, char** address){
    res->address = strdup(address);
}

void set_begin_date(RESERV res, char* b_date){
    int date = 0;

    date = s_to_d(b_date[9]) + s_to_d(b_date[8]) * 10 +
    s_to_d(b_date[6]) * 100 + s_to_d(b_date[5]) * 1000 +
    s_to_d(b_date[3]) * 10000 + s_to_d(b_date[2]) * 100000 +
    s_to_d(b_date[1]) * 1000000 + s_to_d(b_date[0]) * 10000000;

    res->begin_date = date;
}

void set_end_date(RESERV res, char* e_date){
    int date = 0;

    date = s_to_d(e_date[9]) + s_to_d(e_date[8]) * 10 +
    s_to_d(e_date[6]) * 100 + s_to_d(e_date[5]) * 1000 +
    s_to_d(e_date[3]) * 10000 + s_to_d(e_date[2]) * 100000 +
    s_to_d(e_date[1]) * 1000000 + s_to_d(e_date[0]) * 10000000;

    res->end_date = date;
}

void set_price_per_night(RESERV res, char* price){
    res->price_per_night = strdup(price);
}

void set_includes_breakfast(RESERV res, char* inc_breakfast){
    res->includes_breakfast = strdup(inc_breakfast);
}

void set_room_details(RESERV res, char* r_details){
    res->room_details = strdup(r_details);
}

void set_rating(RESERV res, char* ratin){
    res->rating = strdup(ratin);
}

void set_commnet(RESERV res, char* comm){
    res->comment = strdup(comm);
}

char* get_reservation_id(RESERV res){
    return strdup(res->id);
}

char* get_user_id_R(RESERV res){
    return strdup(res->user_id);
}

char* get_hotel_id(RESERV res){
    return strdup(res->hotel_id);
}

char* get_hotel_name(RESERV res){
    return strdup(res->hotel_name);
}

int get_hotel_stars(RESERV res){
    return res->hotel_stars;
}

char* get_city_tax(RESERV res){
    return strdup(res->city_tax);
}

char* get_address(RESERV res){
    return strdup(res->address);
}

int get_begin_date(RESERV res){
    return res->begin_date;
}

int get_end_date(RESERV res){
    return res->end_date;
}

char* get_price_per_night(RESERV res){
    return strdup(res->price_per_night);
}

char* get_includes_breakfast(RESERV res){
    return strdup(res->includes_breakfast);
}

char* get_room_details(RESERV res){
    return strdup(res->room_details);
}

char* get_rating(RESERV res){
    return strdup(res->rating);
}

char* get_comment(RESERV res){
    return strdup(res->comment);
}

void free_reservations(RESERV res){
    free(res->id);
    free(res->user_id);
    free(res->hotel_id);
    free(res->hotel_name);
    free(res->hotel_stars);
    free(res->city_tax);
    free(res->address);
    free(res->begin_date);
    free(res->end_date);
    free(res->price_per_night);
    free(res->includes_breakfast);
    free(res->room_details);
    free(res->rating);
    free(res->comment);

    free(res);
}

int verify_reservations(char** fields){
    if (!(fields[0]) || !(fields[1]) || !(fields[2]) ||
        !(fields[3]) || !(fields[6])) return 0;

    if (!validate_hotel_stars(fields[4])) return 0;
    if (!validate_city_tax(fields[5])) return 0;
    if (!validate_date_time(fields[7])) return 0;
    if (!validate_date_time(fields[8])) return 0;
    // temos também que validar se a begin_date é antes da end_date aqui?
    if (!validate_price_per_night(fields[9])) return 0;
    if (!validate_includes_breakfast(fields[10])) return 0;
    //if (!validate_room_details(fields[11])) return 0;
    if (!validate_rating(fields[12])) return 0;
    //if (!validate_comment(fields[13])) return 0;

    return 1;
}

void build_reservations(char  **reservations_fields, void *catalog, STATS stats){

    if (!verify_reservations(reservations_fields)) return;

    RESERV res = create_reserres();

    set_reservations_id(res,reservations_fields[0]);
    set_reservations_user_id(res,reservations_fields[1]);
    set_reservations_hotel_id(res,reservations_fields[2]);
    set_reservations_hotel_name(res,reservations_fields[3]);
    set_reservations_hotel_stars(res,reservations_fields[4]);
    set_reservations_city_tax(res,reservations_fields[5]);
    set_reservations_address(res,reservations_fields[6]);
    set_reservations_begin_date(res,reservations_fields[7]);
    set_reservations_end_date(res,reservations_fields[8]);
    set_reservations_price_per_night(res,reservations_fields[9]);
    set_reservations_includes_breakfast(res,reservations_fields[10]);
    set_reservations_room_details(res,reservations_fields[11]);
    set_reservations_rating(res,reservations_fields[12]);
    set_reservations_comment(res,reservations_fields[13]);
}



