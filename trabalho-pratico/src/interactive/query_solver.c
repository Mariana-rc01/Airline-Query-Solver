/**
 * @file query_solver.c
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

#include "interactive/query_solver.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/*
O que fazer:
done - query 1
- query 2
- query 3
- query 4
- query 5
- query 6
- query 7
- query 8
- query 9
- query 10
*/

void solver(SETTINGS settings){
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
    char* title = "Query Solver";

    int MAX_OPTIONS = 3;

    BUTTONS options[3] = {
        create_button("Query ID",2,3),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[2] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("-------------------- Arguments ----------------------", 1,7)
    };

    int selectedOption = 0;

    for (int i = 0; i < 2; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

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

                if (strcmp(option, "Query ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "[Run]") == 0){
                    //janela a dizer que nao foi inserido id
                    WINDOW* floatWin = newwin(6, 40, 5, 4);
                    BUTTONS floatMenu1[2] ={
                        create_button("You didn't enter any Query ID! Try again :)", 1,2),
                        create_button("[Go Back]", 29,4)
                    };
                    drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                    getch();
                    destroyFloatMenu(floatWin);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                break;
        }

        // Atualiza as opções na tela
        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 2; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query1W(SETTINGS settings){
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
    char* title = "Query Solver 1";

    int MAX_OPTIONS = 4;

    BUTTONS options[4] = {
        create_button("Query ID",2,3),
        create_button("ID",2,9),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[3] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("1: List the summary of a user, flight or reservation.", 1,5),
        create_button("-------------------- Arguments ----------------------", 1,7)
    };

    int selectedOption = 0;

    for (int i = 0; i < 3; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;

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

                if (strcmp(option, "Query ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        // Verifica se a string contém apenas números
                        if (has_spaces(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a ID without spaces :)");
                            refresh();
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        void* result = query1(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,1,result);
                        exit(0);
                    }
                    else{
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                break;
        }

        // Atualiza as opções na tela
        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 3; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query2W(SETTINGS setts){
    (void) setts;
}

void query3W(SETTINGS setts){
    (void) setts;
}

void query4W(SETTINGS setts){
    (void) setts;
}

void query5W(SETTINGS setts){
    (void) setts;
}

void query6W(SETTINGS setts){
    (void) setts;
}

void query7W(SETTINGS setts){
    (void) setts;
}

void query8W(SETTINGS setts){
    (void) setts;
}

void query9W(SETTINGS setts){
    (void) setts;
}

void query10W(SETTINGS setts){
    (void) setts;
}
