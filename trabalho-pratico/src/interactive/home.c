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

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define MAX_OPTIONS 3

void home(SETTINGS setts) {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Criar uma janela principal
    WINDOW* home_win = newwin(10, 30, 2, 5);
    refresh();

    int ch;
    MEVENT event;
    char* title = "Interactive Mode";

    // Defina suas opções e suas posições aqui
    BUTTONS options[MAX_OPTIONS] = {
        create_button("AirLine Query Solver",2,2),
        create_button("Instructions",2,4),
        create_button("Exit",2,6)
    };

    // Índice da opção selecionada
    int selectedOption = 0;

    // Desenha as opções inicialmente
    drawWindow(home_win, options, selectedOption, title, MAX_OPTIONS, 0);

    while ((ch = getch()) != 27) {
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < MAX_OPTIONS; i++) {
                        if ((event.x >= get_x_B(options[i]) && event.x < get_x_B(options[i]) + (int)strlen(get_label_B(options[i]))) &&
                            (event.y == get_y_B(options[i]))) {
                            // Ação quando uma opção é selecionada (pode redirecionar para outra página, etc.)
                            mvprintw(15, 1, "Selecionado: %s", get_label_B(options[i]));
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
                char* option = get_label_B(options[selectedOption]);

                if (strcmp(option, "AirLine Query Solver") == 0){
                    // Apaga a janela principal
                    werase(home_win);
                    // Atualiza a tela para garantir que a janela principal seja removida
                    wrefresh(home_win);
                    // Sai do modo ncurses
                    endwin();
                    // Chama a função de instruções
                    settingsConfig(setts);
                    // Sai do programa após exibir as instruções
                    exit(0);
                }
                if (strcmp(option, "Instructions") == 0){
                    // Apaga a janela principal
                    werase(home_win);
                    // Atualiza a tela para garantir que a janela principal seja removida
                    wrefresh(home_win);
                    // Sai do modo ncurses
                    endwin();
                    // Chama a função de instruções
                    instructions(setts);
                    // Sai do programa após exibir as instruções
                    exit(0);
                }
                if (strcmp(option, "Exit") == 0){
                    // Apaga a janela principal
                    werase(home_win);
                    // Atualiza a tela para garantir que a janela principal seja removida
                    wrefresh(home_win);
                    // Sai do modo ncurses
                    endwin();
                    exit(0);
                }
                break;
        }

        // Atualiza as opções na tela
        drawWindow(home_win, options, selectedOption, title, MAX_OPTIONS, 0);
    }
    delwin(home_win);
    endwin();
}


