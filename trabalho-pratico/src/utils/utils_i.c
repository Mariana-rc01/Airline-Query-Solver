/**
 * @file utils_i.c
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

#include "utils/utils_i.h"

#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

// Estrutura para representar um botão
struct button {
    int x, y; // Posição do botão
    char *label; // Texto do botão
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

// Função para desenhar as opções
void drawWindow(WINDOW *win, BUTTONS* options, int selected, char* title, int n, int color){
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", title);

    init_pair(1, COLOR_BLUE, COLOR_WHITE);

    // Imprime as opções
    for (int i = 0; i < n; i++) {
        mvwprintw(win, get_y_B(options[i]), get_x_B(options[i]), "%s",get_label_B(options[i]));
    }

    if (color >= 1 && color <= 4){
        // Destaca a opção selecionada
        wattron(win, A_BOLD | COLOR_PAIR(1) | A_REVERSE); // Ativa a inversão de cores (para destacar)
        mvwprintw(win, get_y_B(options[color]), get_x_B(options[color]), "%s", get_label_B(options[color]));
        wattroff(win, A_BOLD | COLOR_PAIR(1) | A_REVERSE); // Desativa a inversão de cores
    }

    // Destaca a opção selecionada
    wattron(win, A_REVERSE); // Ativa a inversão de cores (para destacar)
    mvwprintw(win, get_y_B(options[selected]), get_x_B(options[selected]), "%s", get_label_B(options[selected]));
    wattroff(win, A_REVERSE); // Desativa a inversão de cores

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
