/**
 * @file input.c
 * @brief Module that reads the input file and contains the file validations
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

#ifndef INPUT_H
#define INPUT_H

#include "utils/utils.h"

/**
 * @brief Function that validates the date format YYYY/MM/DD
 *
 * @param date_string Input date string
 * @return 0 if it's valid or 1 if it is not
 */
int validate_date_timeless(char* date_string);

/**
 * @brief Function that validates the date format YYYY/MM/DD hh:mm:ss
 *
 * @param date_string Input date string (with time)
 * @return 0 if it's valid or 1 if it's not
 */
int validate_date_time(char* date_string);

/**
 * @brief Function that compares two dates to validate them
 *
 * If the starting date is a later date then the ending one, thats an invalid entry
 *
 * @param date_string_start Starting date
 * @param date_string_end Ending date
 * @return 0 if starting date is after than ending date otherwise return 1
 */
int compare_date_timeless(char* date_string_start , char* date_string_end);

/**
 * @brief Function that compares two dates with time to validate them
 *
 * If the starting date is a later date then the ending one, thats an invalid entry
 *
 * @param date_string_start Starting date
 * @param date_string_end Ending date
 * @return 0 if starting date is after than ending date otherwise return 1
 */
int compare_date_time(char* date_string_start, char* date_string_end);

/**
 * @brief Function that validates if a string is a valid email
 *
 * Valid format: <username>@<domain>.<TLD>
 * Where <username> and <domain> have at least size 1 and <TLD> at least size 2
 *
 * @param email String in email format
 * @return 0 if it's valid or 1 if it's not
 */
int validate_email(char* email);

/**
 * @brief Function that validates if a country code is valid
 *
 * A country code must be a two letter code
 *
 * @param code
 * @return 0 if it's valid or 1 if it's not
 */
int validate_country_code(char* code);

/**
 * @brief Function that validates an account status
 *
 * The status account is either "Active" or "Inactive"
 * This field is not case sensitve
 *
 * @param status
 * @return 0 if it's valid or 1 if it's not
 */
int validate_account_status(char* status);

/**
 * @brief Validates the format of seat numbers.
 *
 * This function checks whether the given string contains only numerical digits,
 * ensuring that it represents a valid format for seat numbers.
 *
 * @param seats A string representing the seat numbers to be validated.
 * @return 1 if the seat numbers are valid (contains only digits), 0 otherwise.
 */
int validate_seats(char* seats);

/**
 * @brief Function that validates if the number of total seats is greater than the number of passengers
 *
 * @param seats String with the number of seats
 * @param passengers Number of passengers
 * @return 0 if it's valid or 1 if it's not
 */
int validate_total_seats(char* seats, int passengers);

/**
 * @brief Function that validates the airport reference
 *
 * This reference must have three letters only
 * This field is not case sensitve
 *
 * @param airport String with the airport reference
 * @return 0 if it's valid or 1 if it's not
 */
int validate_airports(char* airport);

/**
 * @brief This function validates if the number of hotel stars is a number between one and five
 *
 * Must be an integer
 *
 * @param stars String with the number of stars
 * @return 0 if it's valid or 1 if it's not
 */
int validate_hotel_stars(char* stars);

/**
 * @brief Function that validates the city tax
 *
 * Must be a non negative integer
 *
 * @param tax String that contains the city tax
 * @return 0 if it's valid or 1 if it's not
 */
int validate_city_tax(char* tax);

/**
 * @brief Function that validates the price per night
 *
 * Must be a positive integer
 *
 * @param price String that contains the price per night
 * @return 0 if it's valid or 1 if it's not
 */
int validate_price_per_night(char* price);

/**
 * @brief Function that verifies if a reservation has breakfast included
 *
 * It can be any of the following strings: "t", "f", "TRUE", "FALSE", "1", "0", ""
 *
 * @param boolean String with the information about the breakfast being included on the reservation
 * @return 0 if it's valid or 1 if it's not
 */
int validate_includes_breakfast(char* boolean);

/**
 * @brief Function that validates the rating
 *
 * Must be an integer between one and five
 * Can also be empty if the user didn't rate the hotel
 *
 * @param rating String that contains the rating
 * @return 0 if it's valid or 1 if it's not
 */
int validate_rating(char* rating);

/**
 * @brief Function that validates if a field exists
 *
 * Validates the remaining fields that don't need extra treatment
 *
 * @param string Can represent a lot of differente attributes
 * @return 0 if it's valid or 1 if it's not
 */
int validate_existence(char* string);

#endif
