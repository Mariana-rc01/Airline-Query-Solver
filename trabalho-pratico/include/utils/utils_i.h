/**
 * @file utils_i.h
 * @brief Module containg utility functions used throughout the interactive mode.
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

/**
 * @brief Typedef for struct button pointer.
 */
typedef struct button *BUTTONS;

/**
 * @brief Creates a new button with the specified label and position.
 *
 * @param label The label text of the button.
 * @param x The x-coordinate of the button.
 * @param y The y-coordinate of the button.
 * @return A pointer to the created button.
 */
BUTTONS create_button(char* label, int x, int y);

/**
 * @brief Gets the x-coordinate of a button.
 *
 * @param button The button.
 * @return The x-coordinate of the button.
 */
int get_x_B(BUTTONS button);

/**
 * @brief Gets the y-coordinate of a button.
 *
 * @param button The button.
 * @return The y-coordinate of the button.
 */
int get_y_B(BUTTONS button);

/**
 * @brief Gets the label text of a button.
 *
 * @param button The button.
 * @return The label text of the button.
 */
char* get_label_B(BUTTONS button);

/**
 * @brief Frees the memory allocated for a button.
 *
 * @param button The button to be freed.
 */
void free_button(BUTTONS button);

/**
 * @brief Draws a window with options using ncurses.
 *
 * @param win The ncurses window to draw on.
 * @param options An array of buttons representing the options.
 * @param selected The index of the currently selected option.
 * @param title The title of the window.
 * @param n The number of options.
 * @param color The color index for highlighting the selected option.
 */
void drawWindow(WINDOW *win, BUTTONS* options, int selected, char* title, int n, int color);

/**
 * @brief Verifies if the dataset path is valid.
 *
 * This function checks if the required CSV files are present in the specified path.
 *
 * @param path The dataset path to be verified.
 * @return 1 if the path is valid, 0 otherwise.
 */
int verify_datasetPath(char* path);

/**
 * @brief Draws a floating menu with options.
 *
 * @param floatWin The ncurses window to draw the floating menu on.
 * @param title The title of the floating menu.
 * @param options An array of buttons representing the options.
 * @param n The number of options.
 */
void drawFloatMenu(WINDOW* floatWin, char* title, BUTTONS* options, int n);

/**
 * @brief Destroys a floating menu.
 *
 * @param floatWin The ncurses window of the floating menu to be destroyed.
 */
void destroyFloatMenu(WINDOW* floatWin);

/**
 * @brief Prints a long text in a window with word wrapping.
 *
 * @param win The ncurses window to print the text.
 * @param text_y The current y-coordinate for printing.
 * @param text_x The x-coordinate for printing.
 * @param text The text to be printed.
 */
void printLongText(WINDOW* win, int* text_y, int text_x, const char* text);

#endif
