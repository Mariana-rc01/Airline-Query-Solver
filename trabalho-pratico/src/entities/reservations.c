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

#include "menuNdata/statistics.h"
#include "IO/input.h"
#include "utils/utils.h"
#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>

/**
 * @struct reservations
 * @brief Represents a reservation record.
 */
struct reservations {
    gpointer id; /**< Unique reservation ID. */
    char* user_id; /**< User's ID associated with the reservation. */
    char* hotel_id; /**< Hotel's ID associated with the reservation. */
    char* hotel_name; /**< Name of the hotel. */
    char* hotel_stars; /**< Number of stars rating for the hotel. */
    char* city_tax; /**< City tax information. */
    char* address; /**< Hotel's address. */
    char* begin_date; /**< Start date of the reservation. */
    char* end_date; /**< End date of the reservation. */
    char* price_per_night; /**< Price per night for the reservation. */
    char* includes_breakfast; /**< Information about breakfast inclusion. */
    char* room_details; /**< Details about the room. */
    char* rating; /**< Rating associated with the reservation. */
    char* comment; /**< User's comment on the reservation. */
    double cost; /**< Cost of the reservation. */
};

RESERV create_reservation(void){
    RESERV new = malloc(sizeof(struct reservations));

    new->user_id = NULL;
    new->hotel_id = NULL;
    new->hotel_name = NULL;
    new->hotel_stars = 0;
    new->city_tax = NULL;
    new->address = NULL;
    new->begin_date = NULL;
    new->end_date = NULL;
    new->price_per_night = NULL;
    new->includes_breakfast = NULL;
    new->room_details = NULL;
    new->rating = NULL;
    new->comment = NULL;
    new->cost = 0;

    return new;
}

void set_reservation_id(RESERV res, gpointer id){
    res->id = id;
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

void set_city_tax(RESERV res, char* c_tax){
    res->city_tax = strdup(c_tax);
}

void set_address(RESERV res, char* address){
    res->address = strdup(address);
}

void set_begin_date(RESERV res, char* b_date){
    res->begin_date = strdup(b_date);
}

void set_end_date(RESERV res, char* e_date){
    res->end_date = strdup(e_date);
}

void set_price_per_night(RESERV res, char* price){
    res->price_per_night = strdup(price);
}

void set_includes_breakfast(RESERV res, char* inc_breakfast){
    if (inc_breakfast == NULL) res->includes_breakfast = NULL;
    else res->includes_breakfast = strdup(inc_breakfast);
}

void set_room_details(RESERV res, char* r_details){
    res->room_details = strdup(r_details);
}

void set_rating(RESERV res, char* ratin){
    if (!ratin) res->rating = NULL;
    else res->rating = strdup(ratin);
}

void set_comment(RESERV res, char* comm){
    res->comment = strdup(comm);
}

void set_cost(RESERV res, double cost){
    res->cost = cost;
}

int get_reservation_id(RESERV res){
    return GPOINTER_TO_INT(res->id);
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

char* get_city_tax(RESERV res){
    return strdup(res->city_tax);
}

char* get_address(RESERV res){
    return strdup(res->address);
}

char* get_begin_date(RESERV res){
    return strdup(res->begin_date);
}

char* get_end_date(RESERV res){
    return strdup(res->end_date);
}

char* get_price_per_night(RESERV res){
    return strdup(res->price_per_night);
}

char* get_includes_breakfast(RESERV res){
    if (!res->includes_breakfast) return NULL;
    else return strdup(res->includes_breakfast);
}

char* get_room_details(RESERV res){
    return strdup(res->room_details);
}

char* get_rating(RESERV res){
    if (!res->rating) return NULL;
    else return strdup(res->rating);
}

char* get_comment(RESERV res){
    return strdup(res->comment);
}

double get_cost(RESERV res){
    return (res->cost);
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

int build_reservations(char** reservations_fields, void* catalog, STATS stats){

    MANAGER managerC = (MANAGER)catalog;
    USERS_C usersC = get_users_c(managerC);
    RESERV_C reservsC = get_reserv_c(managerC);

    if (!verify_reservations(reservations_fields, usersC)) return 0;

    RESERV res = create_reservation();

    set_catalog_reserv(reservsC,res,reservations_fields[0]);
    set_user_id_R(res,reservations_fields[1]);
    set_hotel_id(res,reservations_fields[2]);
    set_hotel_name(res,reservations_fields[3]);
    set_hotel_stars(res,reservations_fields[4]);
    set_city_tax(res,reservations_fields[5]);
    set_address(res,reservations_fields[6]);
    set_begin_date(res,reservations_fields[7]);
    set_end_date(res,reservations_fields[8]);
    set_price_per_night(res,reservations_fields[9]);
    set_includes_breakfast(res,reservations_fields[10]);
    set_room_details(res,reservations_fields[11]);
    set_rating(res,reservations_fields[12]);
    set_comment(res,reservations_fields[13]);

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
    int city_tax = ourAtoi(reservations_fields[5]);
    cost = price_per_night * nNights + ((price_per_night * nNights) / 100) * city_tax;
    set_cost(res,cost);

    insert_reservations_c(res, reservsC, res->id);
    update_user_c(usersC,reservations_fields[1],cost);
    (void) stats;

    return 1;
}



