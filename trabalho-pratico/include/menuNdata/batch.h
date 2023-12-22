/**
 * @file batch.h
 * @brief Module that contains functions for executing the batch execution mode aswell as functions 
 * for setting up the catalogs and executing queries.
 *
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

#ifndef BATCH_H
#define BATCH_H

#include "catalogs/manager_c.h"
#include "entities/flights.h"
#include "entities/passengers.h"
#include "entities/reservations.h"
#include "entities/users.h"
#include "menuNdata/queries.h"
#include "IO/parser.h"
#include "IO/input.h"
#include "IO/output.h"
#include "utils/utils.h"
#include "IO/interpreter.h"


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
 * @brief Performs batch processing by setting up the catalog and executing queries.
 *
 * Initializes catalog components, and, receiving the given arguments from main, executes
 * functions to sets up catalog and statistics, executes queries, and frees allocated resources.
 *
 * @param path1 The path containing input CSV files.
 * @param path2 The path to the file containing queries to be executed.
 */
void batch(char* path1, char* path2);

#endif
