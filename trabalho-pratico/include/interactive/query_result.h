/**
 * @file query_result.h
 * @brief Defintion of functions related to query results in interactive mode.
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

#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include "menuNdata/interactive.h"
#include "IO/output.h"
#include "utils/utils_i.h"
#include "utils/utils.h"
#include "interactive/settings_config.h"
#include "interactive/instructions.h"
#include "interactive/query_solver.h"
#include "menuNdata/queries.h"

/**
 * @typedef format_func
 * @brief Function pointer type for formatting query results.
 * @param settings The settings structure used for configuring the program.
 * @param id The identifier of the query result.
 * @param output The result data to be formatted.
 * @param args The arguments provided for the query.
 */
typedef void (*format_func)(SETTINGS, int, void*, char**);

/**
 * @brief Displays query results based on the specified format.
 *
 * This function acts as a controller for displaying query results. It determines the appropriate format
 * based on the settings and user input. It calls the specific formatting function corresponding to the selected format.
 *
 * @param settings The settings structure used for configuring the program.
 * @param id The identifier of the query result.
 * @param output The result data to be displayed.
 * @param args The arguments provided for the query.
 */
void query_results(SETTINGS settings, int id, void* output, char** args);

/**
 * @brief Displays query results in a simple text format.
 *
 * This function displays query results in a simple text format. It initializes the NCurses library, creates a window,
 * and prints the results along with relevant information such as query ID, arguments, and output info.
 *
 * @param settings The settings structure used for configuring the program.
 * @param id The identifier of the query result.
 * @param output The result data to be displayed.
 * @param args The arguments provided for the query.
 */
void txtFormat(SETTINGS settings, int id, void* output, char** args);

/**
 * @brief Displays query results in a paginated format using ncurses.
 *
 * This function initializes the ncurses library, creates a window for displaying
 * results, and allows users to navigate through the pages of query results.
 *
 * @param settings The settings used for the interactive display.
 * @param id The ID of the query.
 * @param output The query results.
 * @param args The arguments used in the query.
 */
void oneByOne(SETTINGS settings, int id, void* output, char** args);

/**
 * @brief Displays query results in a paginated format using ncurses with page numbers.
 *
 * This function initializes the ncurses library, creates a window for displaying
 * results, and allows users to navigate through the pages of query results.
 *
 * @param settings The settings used for the interactive display.
 * @param id The ID of the query.
 * @param output The query results.
 * @param args The arguments used in the query.
 */
void numberPage(SETTINGS settings, int id, void* output, char** args);

/**
 * @brief Displays the results page based on the query ID and output data.
 *
 * Initializes the curses environment and creates a window to display query results.
 *
 * @param settings The SETTINGS structure.
 * @param id The query ID.
 * @param output The query output data.
 * @param args The query arguments.
 */
void outputsPage(SETTINGS settings, int id, void* output, char** args);

#endif
