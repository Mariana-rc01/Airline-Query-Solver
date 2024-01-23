/**
 * @file query_solver.c
 * @brief Implementation of query solver functionality and menu.
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

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* configL = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",configL);
        free(configL);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    while (1){
        ch = getch();
        switch (ch){
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

                        curs_set(1); // Show the cursor
                        echo();      // Enable display of entered text

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        // Check if the string contains only numbers
                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            // Display an error message and do not allow saving
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }

                        curs_set(0); // Hide the cursor
                        noecho();    // Disable display of entered text

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    free_button(floatMenu1[2]);
                    free_button(options[0]);
                    free_button(options[1]);
                    free_button(options[2]);
                    free_button(config[0]);
                    free_button(config[1]);
                    // Go to the function of each query
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "[Run]") == 0){
                    // Window saying that no ID was entered
                    WINDOW* floatWin = newwin(6, 40, 5, 4);
                    BUTTONS floatMenu1[2] ={
                        create_button("You didn't enter any Query ID! Try again :)", 1,2),
                        create_button("[Go Back]", 29,4)
                    };
                    drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                    getch();
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    destroyFloatMenu(floatWin);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    free_button(options[0]);
                    free_button(options[1]);
                    free_button(options[2]);
                    free_button(config[0]);
                    free_button(config[1]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 2; i++) {
            char* configG = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",configG);
            free(configG);
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

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* labelC = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
        free(labelC);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("ID"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "ID") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        if (has_spaces(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = id;

                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("ID"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        void* result = query1(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 4;  i++) free_button(options[i]);
                        for (int i = 0; i < 3;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,1,result, args);
                        exit(0);
                    }
                    else{
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 3; i++) {
            char* label = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
            free(label);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("ID"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query2W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* labelC = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
        free(labelC);
    }
    drawWindow(win, options, selectedOption, title, 7, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("User ID"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 7;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "User ID") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert User ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "User ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 16, id, 1024);

                        if (has_spaces(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "User ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "User ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = id;

                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("User ID"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
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
                        char* verify = get_label_B(options[color]);
                        if (strcmp(verify, "Both") == 0) args[1] = NULL;
                        else if (strcmp(verify, "Flights") == 0) args[1] = "flights";
                        else args[1] = "reservations";
                        free(verify);

                        void* result = query2(get_catalog_S(settings),args);
                        for (int i = 0; i < 7;  i++) free_button(options[i]);
                        for (int i = 0; i < 3;  i++) free_button(config[i]);
                        free(option);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,2,result,args);
                        exit(0);
                    }
                    else{
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    for (int i = 0; i < 7;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    free(option);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, 7, color);
        for (int i = 0; i < 3; i++) {
            char* label = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
            free(label);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("User ID"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query3W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");

                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        if (has_spaces(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = id;
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        //realiza a query
                        void* result = query3(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 4;  i++) free_button(options[i]);
                        for (int i = 0; i < 3;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,3,result,args);
                        exit(0);
                    }
                    else{
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 3; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query4W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        if (has_spaces(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0);
                        noecho();
                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = id;
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        void* result = query4(get_catalog_S(settings),args);
                        for (int i = 0; i < 4;  i++) free_button(options[i]);
                        for (int i = 0; i < 3;  i++) free_button(config[i]);
                        free(option);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,4,result,args);
                        exit(0);
                    }
                    else{
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    free(option);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 3; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query5W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, 6, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    args[2] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Airport name"), "%s",args[0]);
    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
    if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 6;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Airport name") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert airport name: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);

                    char id[200] = " ";

                    while (!validate_airports(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, id, 1024);

                        if (!validate_airports(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid airport :)");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Airport name", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = strdup(id);
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Airport name"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "Begin date") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert begin date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                    mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");


                    char date[200] = " ";

                    while (!validate_date_time(date)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, date, 1024);

                        if (!validate_date_time(date)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[1] = strdup(date);
                    wattron(win, COLOR_PAIR(4));
                    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "End date") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert end date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                    mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");

                    char Edate[200] = " ";

                    while (!validate_date_time(Edate)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, Edate, 1024);

                        if (!validate_date_time(Edate)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "YYYY/MM/DD HH:MM:SS");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[2] = strdup(Edate);
                    wattron(win, COLOR_PAIR(4));
                    if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any name! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                    else if (args[1] == NULL || args[2] == NULL || !compare_date_timeless(args[1], args[2])){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Start date is later than the end date.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                    else{
                        void* result = query5(get_catalog_S(settings),args);
                        for (int i = 0; i < 6;  i++) free_button(options[i]);
                        for (int i = 0; i < 4;  i++) free_button(config[i]);
                        free(option);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,5,result,args);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    for (int i = 0; i < 6;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    free(option);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, 6, color);
        for (int i = 0; i < 4; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Airport name"), "%s",args[0]);
        if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
        if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query6W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("N"), "%s",args[1]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 5;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Year") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a year: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Year", floatMenu1, 2);

                    char id[200] = " ";

                    while (!isNumber(id) || strlen(id) != 4){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        if (!isNumber(id) || strlen(id) != 4) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Year", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Year Format: YYYY :)");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Year", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    args[0] = strdup(id);
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                    free(option);
                    break;
                }

                if (strcmp(option, "N") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a N: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    char N[200] = " ";

                    while (!isNumber(N)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 12, N, 1024);

                        if (!isNumber(N)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Top N", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a number :)");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    args[1] = strdup(N);
                    wattron(win, COLOR_PAIR(4));
                    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("N"), "%s",args[1]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any Year! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    }
                    else if (args[1] == NULL){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any N! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    }
                    else{
                        void* result = query6(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 5;  i++) free_button(options[i]);
                        for (int i = 0; i < 4;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,6,result,args);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 5;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 4; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
        if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("N"), "%s",args[1]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query7W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("N"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "N") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Enter a N: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    char id[200] = " ";

                    while (!isNumber(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 12, id, 1024);

                        if (!isNumber(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Top N", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a number :)");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Top N", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = strdup(id);
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("N"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any N! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                    else{
                        void* result = query7(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 4;  i++) free_button(options[i]);
                        for (int i = 0; i < 4;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,7,result,args);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 4; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("N"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query8W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(3 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;
    args[2] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
    if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 6;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Hotel ID") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Hotel ID: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    char id[200] = " ";

                    while (has_spaces(id)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, id, 1024);

                        if (has_spaces(id)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a ID without spaces");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Hotel ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[0] = strdup(id);
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "Begin date") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert begin date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                    mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");

                    char date[200] = " ";

                    while (!validate_date_timeless(date)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, date, 1024);

                        if (!validate_date_timeless(date)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Begin date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[1] = strdup(date);
                    wattron(win, COLOR_PAIR(4));
                    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "End date") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert end date: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                    mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");


                    char Edate[200] = " ";

                    while (!validate_date_timeless(Edate)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, Edate, 1024);

                        if (!validate_date_timeless(Edate)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "End date", floatMenu1, 2);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Date Format: YYYY/MM/DD");
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "End date", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    args[2] = strdup(Edate);
                    wattron(win, COLOR_PAIR(4));
                    if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL){
                        WINDOW* floatWin = newwin(6, 45, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You didn't enter any hotel ID! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                    else if (args[1] == NULL || args[2] == NULL || !compare_date_timeless(args[1], args[2])){
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Start date is later than the end date.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
                    }
                    else{
                        void* result = query8(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 6;  i++) free_button(options[i]);
                        for (int i = 0; i < 4;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,8,result,args);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 6;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 4; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Hotel ID"), "%s",args[0]);
        if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Begin date"), "%s",args[1]);
        if (args[2] != NULL) mvwprintw(win, 13, 3+strlen("End date"), "%s",args[2]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query9W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Prefix"), "%s",args[0]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Prefix") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Prefix: ", 1,2),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    char id[200] = " ";

                    curs_set(1);
                    echo();
                    mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                    curs_set(0);
                    noecho();

                    drawFloatMenu(floatWin, "ID", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    args[0] = id;
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Prefix"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] != NULL){
                        void* result = query9(get_catalog_S(settings),args);
                        free(option);
                        for (int i = 0; i < 4;  i++) free_button(options[i]);
                        for (int i = 0; i < 3;  i++) free_button(config[i]);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,9,result,args);
                        exit(0);
                    }
                    else{
                        WINDOW* floatWin = newwin(6, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("Didn't enter any prefix! Try again :)", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        for (int i = 0; i < 2;  i++) free_button(config[i]);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(option);
                    for (int i = 0; i < 4;  i++) free_button(options[i]);
                    for (int i = 0; i < 3;  i++) free_button(config[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
        for (int i = 0; i < 3; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Prefix"), "%s",args[0]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}

void query10W(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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
        char* label = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",label);
        free(label);
    }
    drawWindow(win, options, selectedOption, title, 5, color);

    static query_window_func queries_window[] = {
    query1W, query2W, query3W, query4W, query5W,
    query6W, query7W, query8W, query9W, query10W};

    char** args = malloc(2 * sizeof(char*));
    args[0] = NULL;
    args[1] = NULL;

    wattron(win, COLOR_PAIR(4));
    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Month"), "%s",args[1]);
    wattroff(win, COLOR_PAIR(4));

    while (1){
        ch = getch();
        switch (ch){
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
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert Query ID: ", 1,2),
                        create_button("Number between 1 and 10.", 1,4),
                        create_button("[Save & Go Back]", 35,4)
                    };
                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    char number[200] = "a";

                    while (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 17, number, 1024);

                        if (!isNumber(number) || (ourAtoi(number) > 10 || ourAtoi(number) < 1)) {
                            wclear(floatWin);
                            drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 1, "Please enter a valid number :)");
                        }
                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Query ID", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    free(option);
                    for (int i = 0; i < 5;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    queries_window[ourAtoi(number) - 1](settings);
                }

                if (strcmp(option, "Year") == 0){
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

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, id, 1024);

                        wclear(floatWin);
                        drawFloatMenu(floatWin, "Year", floatMenu1, 3);

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Year", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    if (strcmp(id, "0") != 0) args[0] = strdup(id);
                    wattron(win, COLOR_PAIR(4));
                    if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "Month") == 0){
                    WINDOW* floatWin = newwin(6, 55, 5, 4);
                    BUTTONS floatMenu1[3] ={
                        create_button("Insert month: ", 1,2),
                        create_button("[Save & Go Back]", 35,4),
                        create_button("Month Format: MM or 00 for none",1,get_y_B(floatMenu1[0]) + 2)
                    };
                    drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                    char m[200] = "a";

                    while (!isNumber(m) || (ourAtoi(m) < 0 || ourAtoi(m) > 12) || strlen(m) != 2){

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 21, m, 1024);

                        wclear(floatWin);
                        drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Month", floatMenu1, 3);

                    destroyFloatMenu(floatWin);
                    for (int i = 0; i < 3;  i++) free_button(floatMenu1[i]);
                    if (strcmp(m, "00") != 0) args[1] = strdup(m);
                    wattron(win, COLOR_PAIR(4));
                    if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Month"), "%s",args[1]);
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    if (args[0] == NULL && args[1] != NULL){
                        WINDOW* floatWin = newwin(6, 45, 5, 4);
                        BUTTONS floatMenu1[2] ={
                            create_button("You entered the month but forgot the year.", 1,2),
                            create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        destroyFloatMenu(floatWin);
                        for (int i = 0; i < 2;  i++) free_button(floatMenu1[i]);
                    }
                    else{
                        void* result = query10(get_catalog_S(settings),args);
                        for (int i = 0; i < 5;  i++) free_button(options[i]);
                        for (int i = 0; i < 4;  i++) free_button(config[i]);
                        free(option);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        query_results(settings,10,result,args);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    for (int i = 0; i < 5;  i++) free_button(options[i]);
                    for (int i = 0; i < 4;  i++) free_button(config[i]);
                    free(option);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, 5, color);
        for (int i = 0; i < 4; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        wattron(win, COLOR_PAIR(4));
        if (args[0] != NULL) mvwprintw(win, 9, 3+strlen("Year"), "%s",args[0]);
        if (args[1] != NULL) mvwprintw(win, 11, 3+strlen("Month"), "%s",args[1]);
        wattroff(win, COLOR_PAIR(4));
    }

    delwin(win);
    endwin();
}
