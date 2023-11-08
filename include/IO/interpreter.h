/**
 * @file interpreter.h
 * @brief Module that interprets the file with the queries
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

#include <stdio.h>

/**
 * @brief Function that divides a single query in to its parts
 *
 * We need to create a function that divides a string by spaces(" ") having in 
 * mind that anything in between quotation marks should be a single argument
 * 
 * @param line String with the query
 * @return An array with each argument in string format
 */
void divideInToArguments(char* line);

/**
 * @brief Function that removes quotation marks at the beginning and end of a string
 * 
 * @param s String with quotation marks
 * @return The same string without quotation marks
 */
void removeQuotationMarks(char* s);

/**
 * @brief Function that interprets the queries file
 * 
 * @param queries_file Text file containing the queries
 */
void interpreter(FILE queries_file);

#endif


