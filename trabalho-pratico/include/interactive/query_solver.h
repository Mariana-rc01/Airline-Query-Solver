/**
 * @file query_solver.h
 * @brief Definition of query solver functionality and menu.
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

#ifndef QUERY_SOLVER_H
#define QUERY_SOLVER_H

#include "menuNdata/interactive.h"
#include "utils/utils_i.h"
#include "interactive/settings_config.h"
#include "interactive/instructions.h"
#include "interactive/query_result.h"
#include "menuNdata/queries.h"
#include "IO/input.h"

/**
 * @brief Function pointer type for query window functions.
 * @param settings The SETTINGS structure.
 */
typedef void (*query_window_func)(SETTINGS);

/**
 * @brief Main function for query solver interface.
 *
 * Initializes the curses environment and sets up the query solver interface.
 *
 * @param settings The SETTINGS structure.
 */
void solver(SETTINGS settings);

/**
 * @brief Query solver interface for Query 1.
 *
 * Initializes the curses environment and sets up the interface for Query 1.
 *
 * @param settings The SETTINGS structure.
 */
void query1W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 2.
 *
 * Initializes the curses environment and sets up the interface for Query 2.
 *
 * @param settings The SETTINGS structure.
 */
void query2W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 3.
 *
 * Initializes the curses environment and sets up the interface for Query 3.
 *
 * @param settings The SETTINGS structure.
 */
void query3W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 4.
 *
 * Initializes the curses environment and sets up the interface for Query 4.
 *
 * @param settings The SETTINGS structure.
 */
void query4W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 5.
 *
 * Initializes the curses environment and sets up the interface for Query 5.
 *
 * @param settings The SETTINGS structure.
 */
void query5W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 6.
 *
 * Initializes the curses environment and sets up the interface for Query 6.
 *
 * @param settings The SETTINGS structure.
 */
void query6W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 7.
 *
 * Initializes the curses environment and sets up the interface for Query 7.
 *
 * @param settings The SETTINGS structure.
 */
void query7W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 8.
 *
 * Initializes the curses environment and sets up the interface for Query 8.
 *
 * @param settings The SETTINGS structure.
 */
void query8W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 9.
 *
 * Initializes the curses environment and sets up the interface for Query 9.
 *
 * @param settings The SETTINGS structure.
 */
void query9W(SETTINGS setts);

/**
 * @brief Query solver interface for Query 10.
 *
 * Initializes the curses environment and sets up the interface for Query 10.
 *
 * @param settings The SETTINGS structure.
 */
void query10W(SETTINGS setts);

#endif
