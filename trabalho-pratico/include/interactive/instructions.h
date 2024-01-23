/**
 * @file instructions.h
 * @brief Definition of an interactive instructions menu.
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


#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "menuNdata/interactive.h"
#include "interactive/home.h"
#include "utils/utils_i.h"

/**
 * @brief Displays an interactive instructions menu allowing users to navigate between different pages.
 *
 * The function initializes the NCurses library, creates a window, and displays instructions loaded from text files.
 * Users can navigate between pages using arrow keys, mouse clicks, and scroll up/down.
 * The menu also provides an option to go back to the main menu.
 *
 * @param setts The settings structure used for configuring the program.
 */
void instructions(SETTINGS setts);

#endif
