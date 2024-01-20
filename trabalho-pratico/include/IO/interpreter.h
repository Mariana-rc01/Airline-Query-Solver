/**
 * @file interpreter.h
 * @brief Module for parsing and executing queries from an input file
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

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "catalogs/manager_c.h"
#include "menuNdata/queries.h"
#include "IO/output.h"

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
 * @brief Executes queries read from a file, writes results to output files, and frees resources.
 *
 * This function reads queries from a file, parses and executes them storing their result in a 
 * corresponding output file.
 * Frees any allocated memory.
 *
 * @param manager_catalog The catalog manager containing a catalog for each entity type(users, flights, reservations and passengers).
 * @param path2 The path to the file containing queries to be executed.
 * @return 0 on success, -1 on failure.
 */
int execute_queries(MANAGER manager_catalog, char* path2, int flag);

#endif
