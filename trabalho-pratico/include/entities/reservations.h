/**
 * @file reservations.h
 * @brief This file contains the definition of the reservations struct and related functions.
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

/**
 * @typedef RESERV
 * @brief Typedef for struct reservation pointer.
 */
typedef struct reservations *RESERV;

typedef struct users_catalog *USERS_C;

#include <glib.h>

/**
 * @brief Creates a new reservation struct with default values.
 * @return A pointer to the new created reservation.
 */
RESERV create_reservation(void);

/**
 * @brief Sets the reservation ID.
 * @param res A pointer to the reservations struct.
 * @param i The reservation ID.
 */
void set_reservation_id(RESERV res, char* i);

/**
 * @brief Sets the user ID associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @param u_id The user ID.
 */
void set_user_id_R(RESERV res, char* u_id);

/**
 * @brief Sets the hotel ID associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @param h_id The hotel ID.
 */
void set_hotel_id(RESERV res, char* h_id);

/**
 * @brief Sets the name of the hotel.
 * @param res A pointer to the reservations struct.
 * @param h_name The hotel name.
 */
void set_hotel_name(RESERV res, char* h_name);

/**
 * @brief Sets the star rating of the hotel.
 * @param res A pointer to the reservations struct.
 * @param stars The hotel star rating.
 */
void set_hotel_stars(RESERV res, char* stars);

/**
 * @brief Sets the start date of the reservation.
 * @param res A pointer to the reservations struct.
 * @param b_date The start date.
 */
void set_begin_date(RESERV res, char* b_date);

/**
 * @brief Sets the end date of the reservation.
 * @param res A pointer to the reservations struct.
 * @param e_date The end date.
 */
void set_end_date(RESERV res, char* e_date);

/**
 * @brief Sets information about breakfast inclusion for the reservation.
 * @param res A pointer to the reservations struct.
 * @param inc_breakfast Information about breakfast inclusion.
 */
void set_includes_breakfast(RESERV res, char* inc_breakfast);

/**
 * @brief Sets the rating associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @param ratin The rating.
 */
void set_rating(RESERV res, char* ratin);

/**
 * @brief Sets the reservation's cost.
 * @param res A pointer to the reservations struct.
 * @param cost The reservation's cost.
 */
void set_cost(RESERV res, double cost);

/**
 * @brief Sets the price per night for a given reservation.
 * @param res A pointer to the reservations struct.
 * @param ppn The new price per night to be set for the reservation.
 */
void set_price_per_night(RESERV res, int ppn);

/**
 * @brief Gets the reservation ID.
 * @param res A pointer to the reservations struct.
 * @return The reservation ID.
 */
char* get_reservation_id(RESERV res);

/**
 * @brief Gets the user ID associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @return The user ID.
 */
char* get_user_id_R(RESERV res);

/**
 * @brief Gets the hotel ID associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @return The hotel ID.
 */
char* get_hotel_id(RESERV res);

/**
 * @brief Gets the name of the hotel.
 * @param res A pointer to the reservations struct.
 * @return The hotel name.
 */
char* get_hotel_name(RESERV res);

/**
 * @brief Gets the star rating of the hotel.
 * @param res A pointer to the reservations struct.
 * @return The hotel star rating.
 */
char* get_hotel_stars(RESERV res);

/**
 * @brief Gets the start date of the reservation.
 * @param res A pointer to the reservations struct.
 * @return The start date.
 */
char* get_begin_date(RESERV res);

/**
 * @brief Gets the end date of the reservation.
 * @param res A pointer to the reservations struct.
 * @return The end date.
 */
char* get_end_date(RESERV res);

/**
 * @brief Gets information about breakfast inclusion for the reservation.
 * @param res A pointer to the reservations struct.
 * @return Information about breakfast inclusion.
 */
char* get_includes_breakfast(RESERV res);

/**
 * @brief Gets the rating associated with the reservation.
 * @param res A pointer to the reservations struct.
 * @return The rating.
 */
char* get_rating(RESERV res);

/**
 * @brief Gets the cost of the reservation.
 * @param res A pointer to the reservations struct.
 * @return The reservation's cost.
 */
double get_cost(RESERV res);

/**
 * @brief Gets the price per nigth of the reservation.
 * @param res A pointer to the reservations struct.
 * @return The reservation's price per night.
 */
int get_price_per_night(RESERV res);

/**
 * @brief Frees memory associated with a reserv struct.
 * @param res A pointer to the reservation struct.
 */
void free_reservations(RESERV res);

/**
 * @brief Verifies the validity of reservation data.
 * @param fields An array of reserv data fields.
 * @param users Catalog of users.
 * @return 1 if the user data is valid, 0 otherwise.
 */
int verify_reservations(char** fields, USERS_C users);

/**
 * @brief Builds a reservation struct from reservation data fields.
 * @param reservations_fields An array of reservation data fields.
 * @param catalog A pointer to the manager catalog.
 * @param stats A pointer to the statistics.
 *
 * @return 1 if the reservation is added to the catalog 0 if not
 */
int build_reservations(char** reservations_fields, void* catalog);

#endif
