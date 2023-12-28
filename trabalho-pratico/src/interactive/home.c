/**
 * @file home.c
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

#include "interactive/home.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define MAX_OPTIONS 3

// Estrutura para representar um botão
typedef struct {
    int x, y; // Posição do botão
    char *label; // Texto do botão
} Buttons;

// Função para desenhar as opções
void drawWindow(WINDOW *win, Buttons *options, int selected, char* title){
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", title);
    // Imprime as opções
    for (int i = 0; i < MAX_OPTIONS; i++) {
        mvwprintw(win, options[i].y, options[i].x, "%s",options[i].label);
    }

    // Destaca a opção selecionada
    wattron(win, A_REVERSE); // Ativa a inversão de cores (para destacar)
    mvwprintw(win, options[selected].y, options[selected].x, "%s", options[selected].label);
    wattroff(win, A_REVERSE); // Desativa a inversão de cores

    // Atualiza a tela
    wrefresh(win);
}

void home(void) {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Criar uma janela principal
    WINDOW *home_win = newwin(10, 30, 2, 5);
    refresh();

    int ch;
    MEVENT event;
    char* title = "Interactive Mode";

    // Defina suas opções e suas posições aqui
    Buttons options[MAX_OPTIONS] = {
        {2, 2, "AirLine Query Solver"},
        {2, 4, "Instructions"},
        {2, 6, "Exit"}
    };

    // Índice da opção selecionada
    int selectedOption = 0;

    // Desenha as opções inicialmente
    drawWindow(home_win, options, selectedOption, title);

    while ((ch = getch()) != 27) {
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < MAX_OPTIONS; i++) {
                        if ((event.x >= options[i].x && event.x < options[i].x + (int)strlen(options[i].label)) &&
                            (event.y == options[i].y)) {
                            // Ação quando uma opção é selecionada (pode redirecionar para outra página, etc.)
                            mvprintw(15, 1, "Selecionado: %s", options[i].label);
                            refresh();
                            selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS; // com o - 1 ele sobe infinitamente
                            break; // perceber melhor o comportamento do rato
                        }
                    }
                }
                break;
            case KEY_UP:
                selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
                break;
            case KEY_DOWN:
                selectedOption = (selectedOption + 1) % MAX_OPTIONS;
                break;
            case '\n':
                selectedOption = selectedOption  % MAX_OPTIONS;
                char* option = options[selectedOption].label;
                if (strcmp(option, "Instructions") == 0){
                    werase(home_win); // ver como dar clean up da window
                    instructions();
                }
                break;
        }

        // Atualiza as opções na tela
        drawWindow(home_win, options, selectedOption, title);
    }

    endwin();
}


