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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
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
                        query_results(settings,1,result, args);
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

void query2W(SETTINGS settings){
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
    char* title = "Query Solver 2";
    int color = 2;

    int MAX_OPTIONS = 7;

    BUTTONS options[7] = {
        create_button("Query ID",2,3),
        create_button("User ID",2,9),
        create_button("Flights",2,11),
        create_button("Reservations",2,13),
        create_button("Both",2,15),
        create_button("[Run]",2,17),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,17)
    };

    BUTTONS config[3] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("2: List the flights or reservations of a user.", 1,5),
        create_button("-------------------- Arguments ----------------------", 1,7),
    };

    int selectedOption = 0;

    for (int i = 0; i < 3; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, 7, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

    while (1){
        ch = getch();
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < 7; i++) {
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "User ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert User ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "User ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 16, id, 1024);

                        // Verifica se a string contém apenas números
                        if (has_spaces(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "User ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "User ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "Flights") == 0){
                    color = 2;
                }

                if (strcmp(option, "Reservations") == 0){
                    color = 3;
                }

                if (strcmp(option, "Both") == 0){
                    color = 4;
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        args[1] = get_label_B(options[color]);
                        if (strcmp(args[1], "Both") == 0) args[1] = NULL;
                        else if (strcmp(args[1], "Flights") == 0) args[1] = "flights";
                        else args[1] = "reservations";

                        void* result = query2(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,2,result,args);
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
        drawWindow(win, options, selectedOption, title, 7, color);
        for (int i = 0; i < 3; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query3W(SETTINGS settings){
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
    char* title = "Query Solver 3";

    int MAX_OPTIONS = 4;

    BUTTONS options[4] = {
        create_button("Query ID",2,3),
        create_button("Hotel ID",2,9),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[3] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("3: Present the average rating of a hotel.", 1,5),
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
    args[1] = NULL;

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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");

                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        // Verifica se a string contém apenas números
                        if (has_spaces(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        void* result = query3(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,3,result,args);
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

void query4W(SETTINGS settings){
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
    char* title = "Query Solver 4";

    int MAX_OPTIONS = 4;

    BUTTONS options[4] = {
        create_button("Query ID",2,3),
        create_button("Hotel ID",2,9),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[3] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("4: List the reservations of a hotel.", 1,5),
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
    args[1] = NULL;

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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        // Verifica se a string contém apenas números
                        if (has_spaces(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        void* result = query4(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,4,result,args);
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

void query5W(SETTINGS settings){
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
    char* title = "Query Solver 5";
    int color = 0;

    int MAX_OPTIONS = 6;

    BUTTONS options[6] = {
        create_button("Query ID",2,3),
        create_button("Airport name",2,9),
        create_button("Begin date",2,11),
        create_button("End date",2,13),
        create_button("[Run]",2,17),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,17)
    };

    BUTTONS config[4] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("5: List the flights departing from a given airport ", 1,5),
        create_button("between two dates.", 1,6),
        create_button("-------------------- Arguments ----------------------", 1,7),
    };

    int selectedOption = 0;

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, 6, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    args[2] = NULL;

    while (1){
        ch = getch();
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < 6; i++) {
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Airport name") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert airport name: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_airports(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!validate_airports(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid airport :)");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "Begin date") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert begin date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_date_time(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!validate_date_time(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[1] = strdup(id);
                }

                if (strcmp(option, "End date") == 0){
                                        //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert end date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_date_time(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!validate_date_time(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[2] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any name! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else if (args[1] == NULL || args[2] == NULL || !compare_date_timeless(args[1], args[2])){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Start date is later than the end date.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        //realiza a query
                        void* result = query5(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,5,result,args);
                        exit(0);
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
        drawWindow(win, options, selectedOption, title, 6, color);
        for (int i = 0; i < 4; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query6W(SETTINGS settings){
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
    char* title = "Query Solver 6";

    int MAX_OPTIONS = 5;

    BUTTONS options[5] = {
        create_button("Query ID",2,3),
        create_button("Year",2,9),
        create_button("N",2,11),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[4] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("6: List the top N airports with the most passengers ", 1,5),
        create_button("for a given year.", 1,6),
        create_button("-------------------- Arguments ----------------------", 1,7)
    };

    int selectedOption = 0;

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Year") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a year: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Year", floatMenu1, 2);

                    char id[200] = " ";

                    while (!isNumber(id) || strlen(id) != 4){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(id) || strlen(id) != 4) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Year", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Year Format: YYYY :)");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Year", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "N") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a N: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    char id[200] = " ";

                    while (!isNumber(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 12, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Top N", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a number :)");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[1] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any Year! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else if (args[1] == NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any N! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        //realiza a query
                        void* result = query6(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,6,result,args);
                        exit(0);
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
        for (int i = 0; i < 4; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query7W(SETTINGS settings){
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
    char* title = "Query Solver 7";

    int MAX_OPTIONS = 4;

    BUTTONS options[4] = {
        create_button("Query ID",2,3),
        create_button("N",2,9),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[4] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("7: List the top N airports with the highest", 1,5),
        create_button("median delays.", 1,6),
        create_button("-------------------- Arguments ----------------------", 1,7)
    };

    int selectedOption = 0;

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "N") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a N: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    char id[200] = " ";

                    while (!isNumber(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 12, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!isNumber(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Top N", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a number :)");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any N! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        //realiza a query
                        void* result = query7(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,7,result,args);
                        exit(0);
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
        for (int i = 0; i < 4; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query8W(SETTINGS settings){
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
    char* title = "Query Solver 8";

    int MAX_OPTIONS = 6;

    BUTTONS options[6] = {
        create_button("Query ID",2,3),
        create_button("Hotel ID",2,9),
        create_button("Begin date",2,11),
        create_button("End date",2,13),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[4] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("8: Present the total revenue of a hotel between ", 1,5),
        create_button("two dates (inclusive).", 1,6),
        create_button("-------------------- Arguments ----------------------", 1,7)
    };

    int selectedOption = 0;

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    args[2] = NULL;

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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        // Verifica se a string contém apenas números
                        if (has_spaces(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "Begin date") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert begin date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_date_timeless(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!validate_date_timeless(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[1] = strdup(id);
                }

                if (strcmp(option, "End date") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert end date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_date_timeless(id)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        // Verifica se a string contém apenas números
                        if (!validate_date_timeless(id)) {
                            // Exibe uma mensagem de erro e não permite salvar
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");
                        }

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[2] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 45, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any hotel ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else if (args[1] == NULL || args[2] == NULL || !compare_date_timeless(args[1], args[2])){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Start date is later than the end date.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        //realiza a query
                        void* result = query8(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,8,result,args);
                        exit(0);
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
        for (int i = 0; i < 4; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}

void query9W(SETTINGS settings){
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
    char* title = "Query Solver 9";

    int MAX_OPTIONS = 4;

    BUTTONS options[4] = {
        create_button("Query ID",2,3),
        create_button("Prefix",2,9),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[3] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("9: List all users whose names start with the prefix.", 1,5),
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Prefix") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Prefix: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    char id[200] = " ";

                    curs_set(1); // Mostra o cursor
                    echo();      // Habilita a exibição do texto digitado

                    mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                    curs_set(0); // Esconde o cursor
                    noecho();    // Desabilita a exibição do texto digitado

                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        void* result = query9(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,9,result,args);
                        exit(0);
                    }
                    else{
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Didn't enter any prefix! Try again :)", 1,2),
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

void query10W(SETTINGS settings){
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
    char* title = "Query Solver 10";
    int color = 0;

    int MAX_OPTIONS = 5;

    BUTTONS options[5] = {
        create_button("Query ID",2,3),
        create_button("Year",2,9),
        create_button("Month",2,11),
        create_button("[Run]",2,17),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,17)
    };

    BUTTONS config[4] ={
        create_button("-------------------- Query ID -----------------------", 1,1),
        create_button("10: Present various general metrics of the application", 1,5),
        create_button("application.", 1,6),
        create_button("-------------------- Arguments ----------------------", 1,7),
    };

    int selectedOption = 0;

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }
    drawWindow(win, options, selectedOption, title, 5, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

    while (1){
        ch = getch();
        switch (ch){
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    // Verifica se o clique do mouse ocorreu dentro de uma opção
                    for (int i = 0; i < 6; i++) {
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
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    //vai para a função de cada query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Year") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert year: ", 1,2),
                        create_button("[Save & Go Back]", 35,4),
                        create_button("Year Format: YYYY or 0 for none",1,get_y_B(floatMenu1[0]) + 2)
                    };
                    drawFloatMenu(floatWin, "Year", floatMenu1, 3);

                    char id[200] = "a";

                    while (!isNumber(id) || strlen(id) != 4){
                        if (ourAtoi(id) == 0) break;

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        wclear(floatWin);
                        drawFloatMenu(floatWin, "Year", floatMenu1, 3);

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Year", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    args[0] = strdup(id);
                }

                if (strcmp(option, "Month") == 0){
                    //Menu flutuante 1
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert month: ", 1,2),
                        create_button("[Save & Go Back]", 35,4),
                        create_button("Month Format: MM or 0 for none",1,get_y_B(floatMenu1[0]) + 2)
                    };
                    drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                    char id[200] = "a";

                    while (!isNumber(id) || (ourAtoi(id) < 0 || ourAtoi(id) > 12)){

                        curs_set(1); // Mostra o cursor
                        echo();      // Habilita a exibição do texto digitado

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        wclear(floatWin);
                        drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                        curs_set(0); // Esconde o cursor
                        noecho();    // Desabilita a exibição do texto digitado

                    }

                    drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    args[1] = strdup(id);
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL && args[1] != NULL){
                        //janela a dizer que nao foi inserido id
                        WINDOW* floatWin = newwin(6, 45, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You entered the month but forgot the year.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                    }
                    else{
                        //realiza a query
                        void* result = query10(get_catalog_S(settings),args);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,10,result,args);
                        exit(0);
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
        drawWindow(win, options, selectedOption, title, 5, color);
        for (int i = 0; i < 4; i++) {
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
        }
    }

    delwin(win);
    endwin();
}
