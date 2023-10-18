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

/**
 * @brief Function that validates the date format YYYY/MM/DD
 * 
 * @param date_string Input date string
 * @return 0 if it's valid or 1 if it is
 */
int validate_date_timeless(char* date_string);

/**
 * @brief Function that validates the date format YYYY/MM/DD hh:mm:ss
 * 
 * @param date_string Input date string (with time)
 * @return 0 if it's valid or 1 if it is
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

int validate_email(char* email);

int validate_country_code(char* code);

int validate_account_status(char* status);

int validate_total_seats(char* seats, char* passengers);

int validate_airports(char* airport);

int validate_hotel_stars(char* stars);

int validate_city_tax(char* tax);

int validate_price_per_night(char* price);

int validate_includes_breakfast(char* boolean);

int validate_rating(char* rating);

int validate_existence(char* string);

int ourAtoi(char* string);

#endif
