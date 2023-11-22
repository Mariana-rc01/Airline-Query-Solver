/**
 * @file queries.h
 * @brief Module that contains the definition of queries.
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
#ifndef QUERIES_H
#define QUERIES_H

#include "catalogs/manager_c.h"
#include "catalogs/users_c.h"
#include "catalogs/reservations_c.h"
#include "catalogs/flights_c.h"
#include "entities/flights.h"
#include "entities/users.h"
#include "entities/reservations.h"
#include "utils/utils.h"
#include "IO/input.h"

#define MAX_ARGS 7

/**
 * @typedef queries_func
 * @brief Function pointer type for query functions.
 *
 * This typedef defines a function pointer type 'queries_func' used to represent query functions.
 * These functions represent the implementation of the query itself.
 */
typedef void* (*queries_func)(MANAGER catalog, char** query_args);

/**
 * @typedef free_queries_func
 * @brief Function pointer type for free_query functions.
 *
 * This typedef defines a function pointer type 'free_queries_func' used to represent free_query functions.
 * These functions free the memory allocated to the result of the corresponding executed query-.
 */
typedef void (*free_queries_func)(void* result);

/**
 * @brief Parse and execute a query based on input line.
 *
 * This function parses an input line containing a query identifier and its arguments, then executes the corresponding query function. The query function is determined by the identifier in the input line.
 *
 * @param catalog The catalog data manager.
 * @param stats The statistics data.
 * @param line The input line containing the query identifier and arguments.
 *
 * @return A pointer to the result data of the executed query function. The type of data returned may vary and should be cast to the appropriate type.
 *
 * @note This function allocates memory for the 'query_args' array, which should be freed after query execution. The query identifier is expected to be a single character ('1', '2', '3', etc.).
 */

void* parser_query(MANAGER catalog,  char* line);

/**
 * @typedef flight_table_getters
 * @brief Function pointer type for get_flight functions.
 *
 * This typedef defines a function pointer type 'flight_table_getter' used to represent get_flight functions.
 * These functions get the corresponding records from a flight.
 */
typedef char* (*flight_table_getters)(FLIGHT flight);

/**
 * @typedef reservation_table_getters
 * @brief Function pointer type for get_reservation functions.
 *
 * This typedef defines a function pointer type 'reservation_table_getter' used to represent get_reservation functions.
 * These functions get the corresponding records from a reservation.
 */
typedef char* (*reservation_table_getters)(RESERV reserv);

/**
 * @typedef user_table_getters
 * @brief Function pointer type for get_user functions.
 *
 * This typedef defines a function pointer type 'user_table_getter' used to represent get_user functions.
 * These functions get the corresponding records from a user.
 */
typedef char* (*user_table_getters)(USER user);

/**
 * @brief Execute query 1
 *
 * Lists the information about a flight, reservation, or user.
 *
 * @param manager Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query1(MANAGER manager, char** args);

/**
 * Executes Query 2: Retrieve reservations or flights for a given user.
 *
 * @param manager Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query2(MANAGER manager, char** args);

/**
 * @brief Execute query 3
 *
 * Returns the average rating of a hotel.
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query3(MANAGER catalog, char** args);

/**
 * @brief Execute query 4
 *
 * Lists reservations for a given hotel, sorted by their begin date.
 *
 * @param manager Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query4(MANAGER manager, char** args);

/**
 * @brief Executes Query 5
 *
 * Lists flights with origin in a given airport, between 2 dates, sorted by estimated begin date.
 * If two flights have the same date, sort them by their flight_id
 *
 * @param manager Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query5(MANAGER manager, char** args);

/**
 * @brief Executes Query 6
 *
 * List the top N airports with most passengers in a given year.
 * In case of a tie, sort the airports by their name.
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query6(MANAGER catalog, char** args);

/**
 * @brief Executes Query 7
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query7(MANAGER catalog, char** args);

/**
 * @brief Executes Query 8
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query8(MANAGER catalog, char** args);

/**
 * @brief Executes Query 9
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query9(MANAGER catalog, char** args);

/**
 * @brief Executes Query 10
 *
 * @param catalog Catalog manager.
 * @param args    Array of arguments for the query.
 * @return        The result of the query.
 */
void* query10(MANAGER catalog, char** args);


/**
 * @brief Frees the memory allocated for the result of a specific query.
 *
 * Executes the corrresponding function to free the memory allocated of the result of a given query.
 *
 * @param result The result of the query to be freed.
 * @param query_id The identifier of the query.
 */
void free_query(void* result, int query_id);

/**
 * @brief Frees the memory allocated for the result of Query 1.
 *
 * This function frees the memory allocated during the execution of Query 1.
 *
 * @param result The result of Query 1.
 */
void free_query1(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 2.
 *
 * This function frees the memory allocated during the execution of Query 2.
 *
 * @param result The result of Query 2.
 */
void free_query2(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 3.
 *
 * This function frees the memory allocated during the execution of Query 3.
 *
 * @param result The result of Query 3.
 */
void free_query3(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 4.
 *
 * This function frees the memory allocated during the execution of Query 4.
 *
 * @param result The result of Query 4.
 */
void free_query4(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 5.
 *
 * This function frees the memory allocated during the execution of Query 5.
 *
 * @param result The result of Query 5.
 */
void free_query5(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 6.
 *
 * This function frees the memory allocated during the execution of Query 6.
 *
 * @param result The result of Query 6.
 */
void free_query6(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 7.
 *
 * This function frees the memory allocated during the execution of Query 7.
 *
 * @param result The result of Query 7.
 */
void free_query7(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 8.
 *
 * This function frees the memory allocated during the execution of Query 8.
 *
 * @param result The result of Query 8.
 */
void free_query8(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 9.
 *
 * This function frees the memory allocated during the execution of Query 9.
 *
 * @param result The result of Query 9.
 */
void free_query9(void* result);

/**
 * @brief Frees the memory allocated for the result of Query 10.
 *
 * This function frees the memory allocated during the execution of Query 10.
 *
 * @param result The result of Query 10.
 */
void free_query10(void* result);

#endif
