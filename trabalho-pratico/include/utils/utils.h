/**
 * @file utils.h
 * @brief Module containg utility functions used throughout the program.
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

#ifndef UTILS_H
#define UTILS_H

#include "catalogs/manager_c.h"
#include "entities/flights.h"
#include "entities/passengers.h"
#include "entities/users.h"
#include "entities/reservations.h"
#include "IO/parser.h"

#include <glib.h>
#include <stdio.h>

#define SYSTEM_DATE "2023/10/01"

/**
 * @brief Sets up the catalog using input files and parses data into catalogs.
 *
 * This function initializes the catalog and statistics, reads and parses data from CSV files,
 * and write the information to each catalog.
 * It also checks for errors during parsing and creates error files if needed.
 *
 * @param manager_catalog The catalog manager conataing a catalog for each entity type(users, flights, reservations and passengers).
 * @param path1 The path  to the folder containing input CSV files.
 * @return 0 on success, -1 on failure.
 */
int set_catalogs(MANAGER manager_catalog, char* path1);

/**
 * @brief Verifies if a character is a digit
 *
 * @param c Character to be verified
 * @return Bool
 */
int isDigit(char c);

/**
 * @brief Checks if a given string represents a number.
 *
 * @param str The input string.
 * @return 1 if the string represents a number, 0 otherwise.
 */
int isNumber(const char* str);

/**
 * @brief Verifies if a character is a letter
 *
 * @param c Character to be verified
 * @return Bool
 */
int isLetter(char c);

/**
 * @brief This function casts any String to Int.
 *
 * We can't just cast a String to number, we have to pay attention to units
 * E.g. Thousands, Hundreds, Tens, Ones...
 * For this, we need to raise 10 to the power of the length of the string minus 2
 * This is the Invanriant of this function
 *
 *
 * @param string Accepts any type of string
 * @return Cast from string to int
 */
int ourAtoi(char* string);

/**
 * @brief This function concatenates 2 strings resulting in a separate string
 *
 * This function is used instead of strcat because it doesn't modify the first 
 * string, instead returning a separate result argument
 *
 * @param s1 path to the file we want to open
 * @param s2 name of the file we want to open
 * @param result string we want to change
 * @return result
 */
char* concat(char* s1, char* s2);

/**
 * @brief This function verifies if a given file is empty
 *
 * @param file File to be verified
 * @return Bool
 */
int isFileEmpty(FILE *file);

/**
 * @brief This function removes quotation marks from a string
 *
 * @param s String with quotes at the beggining and end
 */
void removeQuotes(char* s);

/**
 * @brief Creates an output file for a query.
 *
 * @param n The command number
 * @return The pointer to the created output file.
 */
FILE* create_output_file(int n);

/**
 * @brief Frees memory allocated for a pointer array.
 *
 * @param data The pointer to the GPtrArray to be freed.
 */
void free_ptr_array(gpointer data);

/**
 * @brief Calculates the age of a user based on current and birth dates.
 *
 * @param currentDate The current date in the format "YYYY/MM/DD".
 * @param birthDate The user's birth date in the format "YYYY/MM/DD".
 * @return The calculated age.
 */
int calculate_user_age(char* currentDate, char* birthDate);

/**
 * @brief Converts a string to uppercase.
 *
 * @param string The input string to be converted.
 * @return The converted case_insensitive string.
 */
char* case_insensitive(char* string);

/**
 * @brief Converts the first letter of a string to uppercase.
 *
 * @param string The input string to be converted.
 * @return The converted string.
 */
char* first_letter_to_upper(char* string);

/**
 * @brief Calculates the delay of a flight based on schedule and actual departure dates.
 *
 * @param scheduleDate The scheduled departure date in the format "YYYY/MM/DD HH:MM:SS".
 * @param actualDate The actual departure date in the format "YYYY/MM/DD HH:MM:SS".
 * @return The calculated delay in seconds.
 */
int calculate_flight_delay(char* scheduleDate, char* actualDate);

/**
 * @brief Gets the delay of a flight given its information.
 *
 * @param flight Flight details.
 * @return The calculated delay in seconds.
 */
int get_flight_delay(FLIGHT flight);

/**
 * @brief Calculates the time span in days between two dates.
 *
 * @param begin The start date string in the format "yyyy/mm/dd".
 * @param end The end date string in the format "yyyy/mm/dd".
 * @return The time span in days.
 */
int dates_timespan ( char* begin, char* end);

/**
 * @brief Gets the number of nights for a reservation.
 *
 * @param reserv Reservation details.
 * @return The number of nights for the reservation.
 */
int get_number_of_nights(RESERV reserv);

/**
 * @brief Converts an integer to a string.
 *
 * @param number The integer to be converted.
 * @return The converted string.
 */
char* int_to_string(int number);

/**
 * @brief Converts a double to a string with three decimal places.
 *
 * @param number The double to be converted.
 * @return The converted string.
 */
char* double_to_string(double number);

/**
 * @brief Check if a string contains spaces.
 *
 * @param str The input string to be checked.
 * @return 1 if the string contains at least one space, 0 otherwise.
 */
int has_spaces(char* str);

/**
 * @brief Replace the first two lines of a file with new lines.
 *
 * This function reads the content of a file, replaces the first two lines
 * with the provided new lines, and writes the modified content back to the file.
 *
 * @param file_name The name of the file to be modified.
 * @param new_line1 The new content for the first line.
 * @param new_line2 The new content for the second line.
 */
void replace_lines_at_start(const char* file_name, const char* new_line1, const char* new_line2);

#endif
