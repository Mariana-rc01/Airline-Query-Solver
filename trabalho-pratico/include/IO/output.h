/**
 * @file output.h
 * @brief This file contains the definition of queries output related functions.
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

#ifndef OUTPUT_H
#define OUTPUT_H

#include "utils/utils.h"

#include <stdio.h>

/**
 * @typedef output_query_func
 * @brief Function pointer type for outputting query results to a file.
 *
 * This typedef defines a function pointer type 'output_query_func'
 * that represents a function used to output query results to a file.
 */
typedef void (*output_query_func)(FILE*, void*);

/**
 * @brief Output the result of a specific query to a file.
 *
 * This function outputs the result of a specific query to a file based on the provided query identifier.
 *
 * @param output_file The file where the query result will be written.
 * @param output A pointer to the query result data.
 * @param query_id The identifier of the query to determine which output function to use.
 *
 * @note If the 'output' parameter is NULL, no output is performed.
 */
void output_query(FILE* output_file, void* output, int query_id);

/**
 * @brief Output the result of query 1 to a file.
 *
 * This function is responsible for outputting the result of query 1 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query1(FILE* file, void* output);

/**
 * @brief Output the result of query 1 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 1 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query1F(FILE* file, void* output);

/**
 * @brief Output the result of query 2 to a file.
 *
 * This function is responsible for outputting the result of query 2 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query2(FILE* file, void* output);

/**
 * @brief Output the result of query 2 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 2 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query2F(FILE* file, void* output);

/**
 * @brief Output the result of query 3 to a file.
 *
 * This function is responsible for outputting the result of query 3 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query3(FILE* file, void* output);

/**
 * @brief Output the result of query 3 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 3 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query3F(FILE* file, void* output);

/**
 * @brief Output the result of query 4 to a file.
 *
 * This function is responsible for outputting the result of query 4 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query4(FILE* file, void* output);

/**
 * @brief Output the result of query 4 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 4 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query4F(FILE* file, void* output);

/**
 * @brief Output the result of query 5 to a file.
 *
 * This function is responsible for outputting the result of query 5 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query5(FILE* file, void* output);

/**
 * @brief Output the result of query 5 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 5 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query5F(FILE* file, void* output);

/**
 * @brief Output the result of query 6 to a file.
 *
 * This function is responsible for outputting the result of query 6 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query6(FILE* file, void* output);

/**
 * @brief Output the result of query 6 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 6 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query6F(FILE* file, void* output);

/**
 * @brief Output the result of query 7 to a file.
 *
 * This function is responsible for outputting the result of query 7 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query7(FILE* file, void* output);

/**
 * @brief Output the result of query 7 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 7 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query7F(FILE* file, void* output);

/**
 * @brief Output the result of query 8 to a file.
 *
 * This function is responsible for outputting the result of query 8 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query8(FILE* file, void* output);

/**
 * @brief Output the result of query 8 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 8 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query8F(FILE* file, void* output);

/**
 * @brief Output the result of query 9 to a file.
 *
 * This function is responsible for outputting the result of query 9 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query9(FILE* file, void* output);

/**
 * @brief Output the result of query 9 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 9 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query9F(FILE* file, void* output);

/**
 * @brief Output the result of query 10 to a file.
 *
 * This function is responsible for outputting the result of query 10 to a specified file.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query10(FILE* file, void* output);

/**
 * @brief Output the result of query 10 with flag 'F' to a file.
 *
 * This function is responsible for outputting the result of query 10 to a specified file, with format 'field: value'.
 *
 * @param file The file where the query result will be written.
 * @param output A pointer to the query result data.
 */
void output_query10F(FILE* file, void* output);

#endif
