/**
 * @file reservations.c
 * @brief This file contains the implementation of the reservations struct and related functions.
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

#include "IO/input.h"
#include "utils/utils.h"
#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @struct reservations
 * @brief Represents a reservation record.
 */
struct reservations {
    char* id; /**< Unique reservation ID. */
    char* user_id; /**< User's ID associated with the reservation. */
    char* hotel_id; /**< Hotel's ID associated with the reservation. */
    char* hotel_name; /**< Name of the hotel. */
    char* hotel_stars; /**< Number of stars rating for the hotel. */
    char* begin_date; /**< Start date of the reservation. */
    char* end_date; /**< End date of the reservation. */
    char* includes_breakfast; /**< Information about breakfast inclusion. */
    char* rating; /**< Rating associated with the reservation. */
    double cost; /**< Cost of the reservation. */
    int price_per_night; /**<Price of a single of the reservation*/
};

RESERV create_reservation(void){
    RESERV new = malloc(sizeof(struct reservations));

    new->id = NULL;
    new->user_id = NULL;
    new->hotel_id = NULL;
    new->hotel_name = NULL;
    new->hotel_stars = 0;
    new->begin_date = NULL;
    new->end_date = NULL;
    new->includes_breakfast = NULL;
    new->rating = NULL;
    new->cost = 0;
    new->price_per_night = 0;

    return new;
}

void set_reservation_id(RESERV res, char* id){
    res->id = strdup(id);
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

void set_hotel_stars(RESERV res, char* stars){
    res->hotel_stars = strdup(stars);
}

void set_begin_date(RESERV res, char* b_date){
    res->begin_date = strdup(b_date);
}

void set_end_date(RESERV res, char* e_date){
    res->end_date = strdup(e_date);
}

void set_includes_breakfast(RESERV res, char* inc_breakfast){
    if (inc_breakfast == NULL) res->includes_breakfast = NULL;
    else res->includes_breakfast = strdup(inc_breakfast);
}

void set_rating(RESERV res, char* ratin){
    if (!ratin) res->rating = NULL;
    else res->rating = strdup(ratin);
}

void set_cost(RESERV res, double cost){
    res->cost = cost;
}

void set_price_per_night(RESERV res, int ppn){
    res->price_per_night = ppn;
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

char* get_hotel_stars(RESERV res){
    return strdup(res->hotel_stars);
}

char* get_begin_date(RESERV res){
    return strdup(res->begin_date);
}

char* get_end_date(RESERV res){
    return strdup(res->end_date);
}

char* get_includes_breakfast(RESERV res){
    if (res->includes_breakfast == NULL) return NULL;
    else return strdup(res->includes_breakfast);
}

char* get_rating(RESERV res){
    if (!res->rating) return NULL;
    else return strdup(res->rating);
}

double get_cost(RESERV res){
    return (res->cost);
}

int get_price_per_night(RESERV res){
    return (res->price_per_night);
}

void free_reservations(RESERV res){
    free(res->user_id);
    free(res->hotel_id);
    free(res->hotel_name);
    free(res->hotel_stars);
    free(res->begin_date);
    free(res->end_date);
    if (res->includes_breakfast != NULL) free(res->includes_breakfast);
    free(res->rating);

    free(res);
}

int verify_reservations(char** fields, USERS_C users){
    if (!(fields[0]) || !(fields[1]) || !(fields[2]) ||
        !(fields[3]) || !(fields[6]) || !(fields[7]) || !(fields[8])) return 0;

    if (!validate_hotel_stars(fields[4])) return 0;
    if (!validate_city_tax(fields[5])) return 0;
    if (!validate_date_timeless(fields[7])) return 0;
    if (!validate_date_timeless(fields[8])) return 0;
    if (!compare_date_timeless(fields[7],fields[8])) return 0;
    if (!validate_price_per_night(fields[9])) return 0;
    if (!validate_includes_breakfast(fields[10])) return 0;
    if (!validate_rating(fields[12])) return 0;
    if (!(get_user_by_id(users, fields[1]))) return 0;

    return 1;
}

int build_reservations(char** reservations_fields, void* catalog){

    MANAGER managerC = (MANAGER)catalog;
    USERS_C usersC = get_users_c(managerC);
    RESERV_C reservsC = get_reserv_c(managerC);

    if (!verify_reservations(reservations_fields, usersC)) return 0;

    RESERV res = create_reservation();
    char* breakfast = first_letter_to_upper(reservations_fields[10]);

    set_reservation_id(res,reservations_fields[0]);
    set_user_id_R(res,reservations_fields[1]);
    set_hotel_id(res,reservations_fields[2]);
    set_hotel_name(res,reservations_fields[3]);
    set_hotel_stars(res,reservations_fields[4]);
    set_begin_date(res,reservations_fields[7]);
    set_end_date(res,reservations_fields[8]);
    set_includes_breakfast(res,breakfast);
    set_rating(res,reservations_fields[12]);

    double cost = 0;
    char beginD[3];
    beginD[0] = reservations_fields[7][8];
    beginD[1] = reservations_fields[7][9];
    beginD[2] = '\0';

    char endD[3];
    endD[0] = reservations_fields[8][8];
    endD[1] = reservations_fields[8][9];
    endD[2] = '\0';

    int nNights = ourAtoi(endD) - ourAtoi(beginD);

    int price_per_night = ourAtoi(reservations_fields[9]);
    set_price_per_night(res, price_per_night);
    int city_tax = ourAtoi(reservations_fields[5]);
    cost = price_per_night * nNights + ((price_per_night * nNights) / (double)100) * city_tax;
    set_cost(res,cost);

    insert_reservations_c(res, reservsC, res->id);
    insert_usersReservations_c(res->id, reservsC, res->user_id);
    insert_hotelsReservations_c(res->id, reservsC, res->hotel_id);

    update_user_c(usersC,reservations_fields[1],cost);

    char year[6];
    char month[3];
    char day[3];
    sscanf(reservations_fields[7], "%4[^/]/%2[^/]/%2[^/]", year, month, day);

    char* concatenated = concat(year, month);

    insert_reservNumber_c(reservsC, concatenated, day);

    return 1;
}



