/**
 * @file queries.h
 * @brief File that contains the definition of queries.
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
#include "menuNdata/statistics.h"

#define MAX_ARGS 4

/**
 * @typedef queries_func
 * @brief Function pointer type for query functions.
 *
 * This typedef defines a function pointer type 'queries_func' used to represent query functions.
 * These functions represent the implementation of the query itself.
 */
typedef void* (*queries_func)(MANAGER catalog, STATS stats, char** query_args);

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
void* parser_query(MANAGER catalog, STATS stats, char* line);

void* query1(MANAGER catalog, STATS stats, char** args);

void* query2(MANAGER catalog, STATS stats, char** args);

void* query3(MANAGER catalog, STATS stats, char** args);

void* query4(MANAGER catalog, STATS stats, char** args);

void* query5(MANAGER catalog, STATS stats, char** args);

void* query6(MANAGER catalog, STATS stats, char** args);

void* query7(MANAGER catalog, STATS stats, char** args);

void* query8(MANAGER catalog, STATS stats, char** args);

void* query9(MANAGER catalog, STATS stats, char** args);

void* query10(MANAGER catalog, STATS stats, char** args);

void free_query(void* result, char query_id);

void free_query1(void* result);

void free_query2(void* result);

void free_query3(void* result);

void free_query4(void* result);

void free_query5(void* result);

void free_query6(void* result);

void free_query7(void* result);

void free_query8(void* result);

void free_query9(void* result);

void free_query10(void* result);

#endif
