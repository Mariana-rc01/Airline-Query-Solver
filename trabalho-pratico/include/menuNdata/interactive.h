/**
 * @file interactive.h
 * @brief Module that contains functions for executing the interactive execution mode aswell as functions 
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
#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "catalogs/manager_c.h"

/**
 * @typedef SETTINGS
 * @brief A pointer to the structure representing settings for interactive mode.
 */
typedef struct setting *SETTINGS;

#include "interactive/home.h"

/**
 * @brief Creates a new SETTINGS structure with default values.
 *
 * Initializes a new SETTINGS structure with default values for interactive mode.
 *
 * @return A newly created SETTINGS structure.
 */
SETTINGS create_settings(void);

/**
 * @brief Sets the dataset path in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param path The dataset path to be set.
 */
void set_datasetPath_S(SETTINGS setts, char* path);

/**
 * @brief Sets the flag indicating a changed dataset path in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param n The flag value (2 - predefined, 1 - changed, 0 - catalogs already filled).
 */
void set_changedPath_S(SETTINGS setts, int n);

/**
 * @brief Sets the output format in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param n The output format (1 - TXT format, 2 - One by One, 3 - Number Page per Page, 4 - Outputs per page).
 */
void set_output_S(SETTINGS setts, int n);

/**
 * @brief Sets the number of pages in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param n The number of pages to be set.
 */
void set_nPages_S(SETTINGS setts, int n);

/**
 * @brief Sets the number of outputs in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param n The number of outputs to be set.
 */
void set_nOutputs_S(SETTINGS setts, int n);

/**
 * @brief Sets the catalogs in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 */
void set_catalog_S(SETTINGS setts);

/**
 * @brief Sets the number of queries in the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @param n The number of queries to be set.
 */
void set_nQueries_S(SETTINGS setts, int n);

/**
 * @brief Gets the dataset path from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return A dynamically allocated string containing the dataset path.
 */
char* get_datasetPath_S(SETTINGS setts);

/**
 * @brief Gets the flag indicating a changed dataset path from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The flag value (2 - predefined, 1 - changed, 0 - catalogs already filled).
 */
int get_changedPath_S(SETTINGS setts);

/**
 * @brief Gets the output format from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The output format (1 - TXT format, 2 - One by One, 3 - Number Page per Page, 4 - Outputs per page).
 */
int get_output_S(SETTINGS setts);

/**
 * @brief Gets the number of pages from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The number of pages.
 */
int get_nPages_S(SETTINGS setts);

/**
 * @brief Gets the number of outputs from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The number of outputs.
 */
int get_nOutputs_S(SETTINGS setts);

/**
 * @brief Gets the catalogs from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The MANAGER structure containing catalogs.
 */
MANAGER get_catalog_S(SETTINGS setts);

/**
 * @brief Gets the number of queries from the SETTINGS structure.
 *
 * @param setts The SETTINGS structure.
 * @return The number of queries.
 */
int get_nQueries_S(SETTINGS setts);

/**
 * @brief Frees the memory allocated for the SETTINGS structure.
 *
 * @param setts The SETTINGS structure to be freed.
 */
void free_settings(SETTINGS setts);

/**
 * @brief Entry point for the interactive mode.
 *
 * Initializes the interactive mode by creating the necessary settings and
 * starting the home screen for user interaction.
 */
void interactive(void);

#endif
