/**
 * @file settings.h
 * @brief Definition of functions related to settings configuration.
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


#ifndef SETTINGS_CONFIG_H
#define SETTINGS_CONFIG_H

#include "menuNdata/interactive.h"
#include "interactive/home.h"
#include "interactive/query_solver.h"
#include "utils/utils_i.h"
#include "utils/utils.h"

/**
 * @brief Main function for configuring application settings.
 *
 * Initializes the curses environment and sets up the user interface for configuring
 * various application settings such as dataset path, output format, etc.
 *
 * @param settings The SETTINGS structure.
 */
void settingsConfig(SETTINGS setts);

#endif
