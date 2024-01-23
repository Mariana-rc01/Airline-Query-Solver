/**
 * @file utils_i.c
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

#include "utils/utils_i.h"

#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define PINK 5

/**
 * @struct button
 * @brief Structure representing a button in the interactive mode.
 *
 * The button structure contains the position (x, y) and label text of a button.
 */
struct button {
    int x, y; /**< x-coordinate of the button */
    char* label; /**< Text label of the button */
};

BUTTONS create_button(char* label, int x, int y){
    BUTTONS new = malloc(sizeof(struct button));
    new->label = strdup(label);
    new->x = x;
    new->y = y;

    return new;
}

int get_x_B(BUTTONS button){
    return button->x;
}

int get_y_B(BUTTONS button){
    return button->y;
}

char* get_label_B(BUTTONS button){
    return strdup(button->label);
}

void free_button(BUTTONS button){
    free(button->label);
    free(button);
}

// Função para desenhar as opções
void drawWindow(WINDOW *win, BUTTONS* options, int selected, char* title, int n, int color){

    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_color(PINK,650,15,400);
    init_pair(5,PINK,COLOR_BLACK);

    wattron(win, A_BOLD | COLOR_PAIR(5));
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", title);
    wattroff(win, A_BOLD | COLOR_PAIR(5));


    // Imprime as opções
    if (strcmp(title,"Interactive Mode") == 0){
        char* label0 = get_label_B(options[0]);
        wattron(win, A_BOLD | COLOR_PAIR(2));
        mvwprintw(win, get_y_B(options[0]), get_x_B(options[0]), "%s",label0);
        wattroff(win, A_BOLD | COLOR_PAIR(2));
        free(label0);

        char* label1 = get_label_B(options[1]);
        wattron(win, A_BOLD | COLOR_PAIR(4));
        mvwprintw(win, get_y_B(options[1]), get_x_B(options[1]), "%s",label1);
        wattroff(win, A_BOLD | COLOR_PAIR(4));
        free(label1);

        char* label2 = get_label_B(options[2]);
        wattron(win, A_BOLD | COLOR_PAIR(3));
        mvwprintw(win, get_y_B(options[2]), get_x_B(options[2]), "%s",label2);
        wattroff(win, A_BOLD | COLOR_PAIR(3));
        free(label2);
    }
    else{
        for (int i = 0; i < n; i++) {
            char* label = get_label_B(options[i]);
            if (strcmp(label,"[Run]") == 0 || strcmp(label,"[Try Again]") == 0 || strcmp(label,"[Cancel]") == 0){
                wattron(win, A_BOLD | COLOR_PAIR(2));
                mvwprintw(win, get_y_B(options[i]), get_x_B(options[i]), "%s",label);
                wattroff(win, A_BOLD | COLOR_PAIR(2));
            }
            else if (strcmp(label,"[Go Back]") == 0 || strcmp(label,"[Leave]") == 0){
                wattron(win, A_BOLD | COLOR_PAIR(3));
                mvwprintw(win, get_y_B(options[i]), get_x_B(options[i]), "%s",label);
                wattroff(win, A_BOLD | COLOR_PAIR(3));
            }
            else if (strcmp(label,"[Home]") == 0){
                wattron(win, A_BOLD | COLOR_PAIR(4));
                mvwprintw(win, get_y_B(options[i]), get_x_B(options[i]), "%s",label);
                wattroff(win, A_BOLD | COLOR_PAIR(4));
            }
            else mvwprintw(win, get_y_B(options[i]), get_x_B(options[i]), "%s",label);
            free(label);
        }
    }

    if (color >= 1 && color <= 4){
        char* labelC = get_label_B(options[color]);
        // Destaca a opção selecionada
        wattron(win, A_BOLD | COLOR_PAIR(1) | A_REVERSE);
        mvwprintw(win, get_y_B(options[color]), get_x_B(options[color]), "%s", labelC);
        wattroff(win, A_BOLD | COLOR_PAIR(1) | A_REVERSE);
        free(labelC);
    }

    char* labelR = get_label_B(options[selected]);
    // Destaca a opção selecionada
    wattron(win, A_REVERSE); // Ativa a inversão de cores (para destacar)
    mvwprintw(win, get_y_B(options[selected]), get_x_B(options[selected]), "%s", labelR);
    wattroff(win, A_REVERSE); // Desativa a inversão de cores
    free(labelR);

    // Atualiza a tela
    wrefresh(win);
}

int verify_datasetPath(char* path){
    char filePath[2048];
    char* filenames[4] = {"flights.csv","passengers.csv","users.csv","reservations.csv"};

    for(int i = 0; i < 4; i++){
        snprintf(filePath, sizeof(filePath), "%s/%s", path, filenames[i]);
        FILE *file = fopen(filePath, "r");
        if (!file){
            return 0; // Arquivo não encontrado
        }
        fclose(file);
    }

    return 1; // Arquivo encontrado
}

void drawFloatMenu(WINDOW* floatWin, char* title, BUTTONS* options, int n) {

    wattron(floatWin, A_BOLD | COLOR_PAIR(5));
    box(floatWin, 0, 0);
    mvwprintw(floatWin, 0, 1, "%s", title);
    wattroff(floatWin, A_BOLD | COLOR_PAIR(5));

    for (int i = 0; i < n; i++) {
        char* label = get_label_B(options[i]);
        mvwprintw(floatWin, get_y_B(options[i]), get_x_B(options[i]), "%s", label);
        free(label);
    }

    wrefresh(floatWin);
}

void destroyFloatMenu(WINDOW* floatWin) {
    werase(floatWin);
    wrefresh(floatWin);
    delwin(floatWin);
}

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
