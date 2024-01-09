/**
 * @file settings.c
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

#include "interactive/settingsConfig.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/*
O que é preciso fazer aqui:
done - desenhar box de settings
done - dataset configuration -> menuflutuante1
done - output configuration -> botões com opções
- na opção per page -> menuflutuante2
done - [RUN] [Go Back]
done - menuflutuante1 - insere a path
- menuflutuante2 - insere o nº de páginas ou o nº de outputs por página

- ao clicar em RUN -> verificar se existem os ficheiros csv's com a path dada e se nao tiverem
diz para corrigir ou usar o default
quando clica em RUN se der tudo okay, preenche os catálogos, apagando possíveis preenchimentos
que lá estejam caso a path tenha sido mudada apenas, só se changedPath estiver a 1
*/

#include "interactive/settingsConfig.h"

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define MAX_OPTIONS 6

// Defina o número máximo de opções do menu flutuante
#define MAX_FLOAT_MENU_OPTIONS 3

void drawFloatMenu(WINDOW* floatWin, char* title, BUTTONS* options, int n) {
    box(floatWin, 0, 0);
    mvwprintw(floatWin, 0, 1, "%s", title);

    for (int i = 0; i < n; i++) {
        mvwprintw(floatWin, get_y_B(options[i]), get_x_B(options[i]), "%s", get_label_B(options[i]));
    }

    wrefresh(floatWin);
}

void destroyFloatMenu(WINDOW* floatWin) {
    werase(floatWin);
    wrefresh(floatWin);
    delwin(floatWin);
}

#include <ctype.h>

void menuFloat2(SETTINGS settings) {
    int selectedOption = 0;
    (void) settings;

    WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 55, 5, 4);
    BUTTONS floatMenu2[3] = {
        create_button("Number of Pages: ", 1, 2),
        create_button("Number of Outputs per Page: ", 2, 3),
        create_button("[Save & Go Back]", 35, 4),
    };

    drawFloatMenu(floatWin, "Per Page", floatMenu2, 3);

    int ch;

    while ((ch = wgetch(floatWin)) != 27) {
        switch (ch) {
            case KEY_UP:
                selectedOption = (selectedOption - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                selectedOption = (selectedOption + 1) % 3;
                break;
            case '\n':
                break;
        }

        // Atualiza as opções na tela
        drawFloatMenu(floatWin, "Output Configuration", floatMenu2, 3);
    }
}

void settingsConfig(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(23,55,0,0);
    refresh();

    MEVENT event;
    int ch;
    char* title = "Settings";

    BUTTONS options[MAX_OPTIONS] = {
        create_button("Select Dataset Path",2,3),
        create_button("TXT Format",2,7),
        create_button("One by one",2,9),
        create_button("Per Page",2,11),
        create_button("[Run]",2,13),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,13)
    };

    BUTTONS config[2] ={
        create_button("--------------- Dataset Configuration ---------------", 1,1),
        create_button("--------------- Output Configuration ----------------", 1,5)
    };

    int selectedOption = 0;
    int color = get_output_S(settings);

    for (int i = 0; i < 2; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, color);

    while ((ch = getch()) != 27){
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < MAX_OPTIONS; i++) {
                        if ((event.x >= get_x_B(options[i]) && event.x < get_x_B(options[i]) + (int)strlen(get_label_B(options[i]))) &&
                            (event.y == get_y_B(options[i]))) {
                            selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
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
            case KEY_LEFT:
                selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
                break;
            case KEY_RIGHT:
                selectedOption = (selectedOption + 1) % MAX_OPTIONS;
                break;
            case '\n':
                selectedOption = selectedOption  % MAX_OPTIONS;
                char* option = get_label_B(options[selectedOption]);

                if (strcmp(option, "Select Dataset Path") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 55, 5, 4);
                    BUTTONS floatMenu1[2] ={
                        create_button("Insert Path: $/", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Dataset Path", floatMenu1, 2);

                    char path[1025];

                    curs_set(1); // Mostra o cursor
                    echo();      // Habilita a exibição do texto digitado

                    mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, path, 1024);
                    set_datasetPath_S(settings, path);

                    curs_set(0); // Esconde o cursor
                    noecho();    // Desabilita a exibição do texto digitado

                    destroyFloatMenu(floatWin);
                }

                if (strcmp(option, "TXT Format") == 0){
                    set_output_S(settings,1);
                    color = 1;
                }
                if (strcmp(option, "One by one") == 0){
                    //Seleciona one by one
                    set_output_S(settings,2);
                    color = 2;
                }

                if (strcmp(option, "Per Page") == 0){
                    //Menu flutuante 2 e seleciona Per Page
                    set_output_S(settings,3);
                    menuFloat2(settings);
                    color = 3;
                }

                if (strcmp(option, "[Run]") == 0){
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }
                break;
        }

        // Atualiza as opções na tela
        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, color);
        for (int i = 0; i < 2; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}
