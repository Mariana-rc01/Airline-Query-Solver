/**
 * @file instructions.c
 * @brief Implementation of an interactive instructions menu.
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

#include "interactive/instructions.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define PINK 5

void instructions(SETTINGS setts){
    initscr();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_color(PINK,650,15,400);
    init_pair(5,PINK,COLOR_BLACK);

    char option[] = "[Go Back]";
    char arrow_left[] = "<";
    char arrow_right[] = ">";

    int max_y = 23, max_x = 65;

    WINDOW* win = newwin(max_y, max_x, 0, 0);
    refresh();

    int ch;
    int current_text = 1;
    int max_texts = 3;
    int text_offset = 0;  // Vertical offset in the text

    while (1){
        wclear(win);
        wattron(win, A_BOLD | COLOR_PAIR(5));
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Instructions");
        wattroff(win, A_BOLD | COLOR_PAIR(5));

        int text_y = 1;
        int text_x = 1;

        char filename[57];
        snprintf(filename, sizeof(filename), "src/interactive/instructions_page%d.txt", current_text);

        FILE *file = fopen(filename, "r");

        int verify = 0;

        if (file != NULL){
            char buffer[1024];
            // Adjust: Skip lines based on vertical offset
            for (int i = 0; i < text_offset; ++i){
                if (fgets(buffer, sizeof(buffer), file) == NULL){
                    break;  // Reached the end of the file
                }
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL && text_y < max_y - 2){
                printLongText(win, &text_y, text_x, buffer);
            }

            // Check if there are more lines in the file
            if (fgets(buffer, sizeof(buffer), file) == NULL){
                verify = 1;
            }

            fclose(file);
        }
        else {
            mvwprintw(win, text_y++, text_x, "Erro ao abrir o ficheiro %s", filename);
        }

        wattron(win, A_BOLD | COLOR_PAIR(5));
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Instructions");
        wattroff(win, A_BOLD | COLOR_PAIR(5));


        mvwprintw(win, max_y - 2, 2, "%s", arrow_left);
        mvwprintw(win, max_y - 2, 4, "%s", arrow_right);

        wattron(win, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(win, max_y - 2, max_x - strlen(option) - 2, "%s", option);
        wattroff(win, COLOR_PAIR(1) | A_BOLD);

        wrefresh(win);

        ch = getch();
        MEVENT event;

        switch (ch){
            case KEY_MOUSE:
                if (ch == KEY_MOUSE && getmouse(&event) == OK) {
                    if (event.x == 2 && event.y == max_y - 2) {
                        current_text = (current_text + 1 + max_texts) % max_texts - 1;
                        text_offset = 0;
                    }
                    else if (event.x == 4 && event.y == max_y - 2){
                        current_text = (current_text - 2 + max_texts) % max_texts + 1;
                        text_offset = 0;
                    }
                    else {
                        wclear(win);
                        wrefresh(win);
                        endwin();
                        home(setts);
                        exit(0);
                    }
                }
                else break;
            case KEY_LEFT:
                current_text = (current_text - 2 + max_texts) % max_texts + 1;
                text_offset = 0;
                break;
            case KEY_RIGHT:
                current_text = (current_text) % max_texts + 1;
                text_offset = 0;
                break;
            case KEY_UP:
                if (text_offset > 0) {
                    text_offset--;
                    verify = 0;
                }
                break;
            case KEY_DOWN:
                if (!verify) text_offset++;
                break;
            case '\n':
                wclear(win);
                wrefresh(win);
                endwin();
                home(setts);
                exit(0);
                break;
            default:
                break;
        }
    }
}
