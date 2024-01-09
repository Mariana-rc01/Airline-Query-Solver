/**
 * @file utils_i.h
 * @brief 
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

#ifndef UTILS_I
#define UTILS_I

#include <ncurses.h>

typedef struct button *BUTTONS;

BUTTONS create_button(char* label, int x, int y);

int get_x_B(BUTTONS button);

int get_y_B(BUTTONS button);

char* get_label_B(BUTTONS button);

void drawWindow(WINDOW *win, BUTTONS* options, int selected, char* title, int n, int color);

#endif