/**
 * @file home.h
 * @brief Definition of an interactive home menu.
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

#ifndef HOME_H
#define HOME_H

#include "menuNdata/interactive.h"
#include "utils/utils_i.h"
#include "interactive/settings_config.h"
#include "interactive/instructions.h"

/**
 * @brief Displays an interactive home menu allowing users to select different options.
 *
 * The function initializes the NCurses library, creates a main window, and displays a menu with options.
 * Users can navigate through the options using arrow keys and select an option by pressing Enter.
 * Depending on the selected option, specific actions such as configuring settings, displaying instructions,
 * or exiting the program may be triggered.
 *
 * @param setts The settings structure used for configuring the program.
 */
void home(SETTINGS settings);

#endif
