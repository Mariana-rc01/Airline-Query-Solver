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

#include "interactive/settings_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define MAX_OPTIONS 7

// Defina o número máximo de opções do menu flutuante
#define MAX_FLOAT_MENU_OPTIONS 3

void settingsConfig(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

    MEVENT event;
    int ch;
    char* title = "Settings";

    BUTTONS options[MAX_OPTIONS] = {
        create_button("Select Dataset Path",2,3),
        create_button("TXT Format",2,7),
        create_button("One by one",2,9),
        create_button("Number of pages",2,11),
        create_button("Outputs per page",2,13),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
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


    while (1){
        ch = getch();
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
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Path: $/", 1,2),
                        create_button("Default path: \".\"", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Dataset Path", floatMenu1, 3);

                    char path[1025];

                    curs_set(1); // Mostra o cursor
                    echo();      // Habilita a exibição do texto digitado

                    mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, path, 1024);
                    set_datasetPath_S(settings, path);

                    curs_set(0); // Esconde o cursor
                    noecho();    // Desabilita a exibição do texto digitado

                    set_changedPath_S(settings,1);

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

                if (strcmp(option, "Number of pages") == 0){
                    //Menu flutuante 2 e seleciona Per Page
                    set_output_S(settings,3);
                    color = 3;
                    WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 55, 5, 4);
                    BUTTONS floatMenu1[2] ={
                        create_button("Insert Number of pages: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Number of pages", floatMenu1, 2);

                    char number[1025] = "a";

                    while (!isNumber(number) || ourAtoi(number) == 0){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 25, number, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(number) || ourAtoi(number) == 0) {
                            // Exibe uma mensagem de erro e não permite salvar
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        } else {
                            set_nPages_S(settings, ourAtoi(number));
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Number of pages", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                }

                if (strcmp(option, "Outputs per page") == 0){
                    //Menu flutuante 2 e seleciona outputs Per Page
                    set_output_S(settings,4);
                    color = 4;

                    WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 55, 5, 4);
                    BUTTONS floatMenu1[2] ={
                        create_button("Insert number of outputs per pages: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Number of Outputs", floatMenu1, 2);

                    char number[1025] = "a";

                    while (!isNumber(number) || ourAtoi(number) == 0){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 36, number, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(number) || ourAtoi(number) == 0) {
                            // Exibe uma mensagem de erro e não permite salvar
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        } else {
                            set_nOutputs_S(settings, ourAtoi(number));
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Number of Outputs", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                }

                if (strcmp(option, "[Run]") == 0){
                    int verify = verify_datasetPath(get_datasetPath_S(settings));
                    if (!verify) {
                        WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                        create_button("Invalid dataset path! Try again :)", 1,2),
                        create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        if (get_changedPath_S(settings) == 1){
                            free_manager_c(get_catalog_S(settings));
                            set_catalog_S(settings);
                            char* path = get_datasetPath_S(settings);
                            set_catalogs(get_catalog_S(settings), path);
                            set_changedPath_S(settings,0);
                            free(path);
                        }
                        if (get_changedPath_S(settings) == 2){
                            set_catalog_S(settings);
                            char* path = get_datasetPath_S(settings);
                            set_catalogs(get_catalog_S(settings), path);
                            set_changedPath_S(settings,0);
                            free(path);
                        }
                        werase(win);
                        wrefresh(win);
                        endwin();
                        solver(settings);
                        exit(0);
                    }
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