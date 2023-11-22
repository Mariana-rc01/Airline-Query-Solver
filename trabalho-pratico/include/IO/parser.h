/**
 * @file parser.h
 * @brief Module that parses any given file
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

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef int (*void_function)(char**, void*);

/**
 * @brief Function to parse a file
 *
 * This function reads data from a file, writes to the error csv,
 * separates the line into fields and verifies for any errors.
 *
 * @param f Pointer to given file
 * @param max_fields Number of attributes of the csv file
 * @param func Function that loads the data into the structs
 * @param catalog The catalog of the respective file
 * @param error_f Pointer to the error file
*/
void parseF (FILE* f, int max_fields, void_function func, void *catalog, FILE* error_f);

/**
 * @brief Function to parse a line
 *
 * This function takes a line and splits it into fields based on the delimiter ';'.
 *
 * @param line Pointer to given line
 * @param max_fields Number of attributes of the csv file
*/
char** parseL (char* line, int max_fields);

#endif
