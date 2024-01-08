/**
 * @file instructions.c
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

#include "interactive/instructions.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/* O que não está a dar bem nas instructions:
A linha vertical da direita nao está a ser bem colocada quando imprimimos texto que muda de linha
*/

// Deve ser mudado para os utils
void printLongText(WINDOW* win, int* text_y, int text_x, const char* text) {
    int max_x = 65;
    int max_y = 23;
    size_t text_len = strlen(text);

    while (text_len > 0 && *text_y < max_y - 2) {
        int available_width = max_x - text_x - 2; // Espaço disponível para a linha atual

        if (text_len > (size_t)available_width) {
            // Imprimir parte da string que cabe na largura disponível
            mvwprintw(win, (*text_y)++, text_x, "%.*s", available_width, text);
            text += available_width;
            text_len -= available_width;
        } else {
            mvwprintw(win, (*text_y)++, text_x, "%-*s", max_x - 2, text);
            text_len = 0;
        }
    }
}


void instructions(void){
    initscr();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    char option[] = "[Go Back]";
    char arrow_left[] = "<";
    char arrow_right[] = ">";

    int max_y = 23, max_x = 65;

    WINDOW* win = newwin(max_y, max_x, 0, 0);
    refresh();

    int ch;
    int current_text = 1;
    int max_texts = 3;
    int text_offset = 0;  // Offset vertical no texto

    while (1){
        wclear(win);
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Instructions");

        int text_y = 1;
        int text_x = 1;

        char filename[57];
        snprintf(filename, sizeof(filename), "src/interactive/instructions_page%d.txt", current_text);

        FILE *file = fopen(filename, "r");

        int verify = 0;

        if (file != NULL){
            char buffer[1024];
            // Ajuste: Pular linhas conforme o deslocamento vertical
            for (int i = 0; i < text_offset; ++i){
                if (fgets(buffer, sizeof(buffer), file) == NULL){
                    break;  // Chegamos ao final do arquivo
                }
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL && text_y < max_y - 2){
                printLongText(win, &text_y, text_x, buffer);
            }

            // Verificar se há mais linhas no arquivo
            if (fgets(buffer, sizeof(buffer), file) == NULL){
                verify = 1;
            }

            fclose(file);
        }
        else {
            mvwprintw(win, text_y++, text_x, "Erro ao abrir o ficheiro %s", filename);
        }

        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Instructions");


        mvwprintw(win, max_y - 2, 2, "%s", arrow_left);
        mvwprintw(win, max_y - 2, 4, "%s", arrow_right);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, max_y - 2, max_x - strlen(option) - 2, "%s", option);
        wattroff(win, COLOR_PAIR(1));

        wrefresh(win);

        ch = getch();
        MEVENT event;

        switch (ch){
            case KEY_MOUSE:
                if (ch == KEY_MOUSE && getmouse(&event) == OK) {
                    if (event.x == 2 && event.y == max_y - 2) {
                        current_text = (current_text - 2 + max_texts) % max_texts + 1;
                    }
                    else if (event.x == 4 && event.y == max_y - 2){
                        ch = KEY_RIGHT;
                    }
                    else {
                        wclear(win);
                        wrefresh(win);
                        endwin();
                        home();
                        exit(0);
                    }
                }
                else break;
            case KEY_LEFT:
                current_text = (current_text - 2 + max_texts) % max_texts + 1;
                break;
            case KEY_RIGHT:
                current_text = (current_text) % max_texts + 1;
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
                home();
                exit(0);
                break;
            default:
                break;
        }
    }
}
