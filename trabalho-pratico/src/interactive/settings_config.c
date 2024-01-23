/**
 * @file settings.c
 * @brief Implementation of functions related to settings configuration.
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

#define MAX_FLOAT_MENU_OPTIONS 3

void settingsConfig(SETTINGS settings){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

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

    char* pathG = get_datasetPath_S(settings);
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 3, 4+strlen("Select Dataset Path"), "%s",pathG);
    mvwprintw(win, 11, 5+strlen("Number of pages"), "%d",get_nPages_S(settings));
    mvwprintw(win, 13, 5+strlen("Ouputs per page"), "%d",get_nOutputs_S(settings));
    wattroff(win, COLOR_PAIR(4));
    free(pathG);

    int selectedOption = 0;
    int color = get_output_S(settings);

    for (int i = 0; i < 2; i++) {
        char* labelC = get_label_B(config[i]);
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
        free(labelC);
    }
    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, color);

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

                    curs_set(1);
                    echo();

                    mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 15, path, 1024);
                    set_datasetPath_S(settings, path);

                    curs_set(0);
                    noecho();

                    set_changedPath_S(settings,1);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    free_button(floatMenu1[2]);
                    char* pathS = get_datasetPath_S(settings);
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, 3, 4+strlen("Select Dataset Path"), "%s",pathS);
                    wattroff(win, COLOR_PAIR(4));
                    free(pathS);
                }

                if (strcmp(option, "TXT Format") == 0){
                    set_output_S(settings,1);
                    color = 1;
                }
                if (strcmp(option, "One by one") == 0){
                    set_output_S(settings,2);
                    color = 2;
                }

                if (strcmp(option, "Number of pages") == 0){
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

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 25, number, 1024);

                        if (!isNumber(number) || ourAtoi(number) == 0) {
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        } else {
                            set_nPages_S(settings, ourAtoi(number));
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Number of pages", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, 11, 5+strlen("Number of pages"), "%d",get_nPages_S(settings));
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "Outputs per page") == 0){
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

                        curs_set(1);
                        echo();

                        mvwgetnstr(floatWin, get_y_B(floatMenu1[0]), get_x_B(floatMenu1[0]) + 36, number, 1024);

                        if (!isNumber(number) || ourAtoi(number) == 0) {
                            mvwprintw(floatWin, get_y_B(floatMenu1[0]) + 2, 2, "Please enter a valid number :)");
                            refresh();
                        } else {
                            set_nOutputs_S(settings, ourAtoi(number));
                        }

                        curs_set(0);
                        noecho();

                    }

                    drawFloatMenu(floatWin, "Number of Outputs", floatMenu1, 2);

                    destroyFloatMenu(floatWin);
                    free_button(floatMenu1[0]);
                    free_button(floatMenu1[1]);
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, 13, 5+strlen("Ouputs per page"), "%d",get_nOutputs_S(settings));
                    wattroff(win, COLOR_PAIR(4));
                }

                if (strcmp(option, "[Run]") == 0){
                    char* getPath = get_datasetPath_S(settings);
                    int verify = verify_datasetPath(getPath);
                    free(getPath);
                    if (!verify) {
                        WINDOW* floatWin = newwin(MAX_FLOAT_MENU_OPTIONS + 3, 40, 5, 4);
                        BUTTONS floatMenu1[2] ={
                        create_button("Invalid dataset path! Try again :)", 1,2),
                        create_button("[Go Back]", 29,4)
                        };
                        drawFloatMenu(floatWin, "Error", floatMenu1, 2);
                        getch();
                        free_button(floatMenu1[0]);
                        free_button(floatMenu1[1]);
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
                            char* path = get_datasetPath_S(settings);
                            set_catalogs(get_catalog_S(settings), path);
                            set_changedPath_S(settings,0);
                            free(path);
                        }
                        for (int i = 0; i < MAX_OPTIONS; i++){
                            free_button(options[i]);
                        }
                        for (int i = 0; i < 2; i++){
                            free_button(config[i]);
                        }
                        free(option);
                        werase(win);
                        wrefresh(win);
                        endwin();
                        solver(settings);
                        exit(0);
                    }
                }

                if (strcmp(option, "[Go Back]") == 0){
                    for (int i = 0; i < MAX_OPTIONS; i++){
                            free_button(options[i]);
                    }
                    for (int i = 0; i < 2; i++){
                        free_button(config[i]);
                    }
                    free(option);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }
                free(option);
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, color);
        for (int i = 0; i < 2; i++) {
            char* labelC = get_label_B(config[i]);
            mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",labelC);
            free(labelC);
        }
        char* pathG = get_datasetPath_S(settings);
        wattron(win, COLOR_PAIR(4));
        mvwprintw(win, 3, 4+strlen("Select Dataset Path"), "%s",pathG);
        mvwprintw(win, 11, 5+strlen("Number of pages"), "%d",get_nPages_S(settings));
        mvwprintw(win, 13, 5+strlen("Ouputs per page"), "%d",get_nOutputs_S(settings));
        wattroff(win, COLOR_PAIR(4));
        free(pathG);
    }

    delwin(win);
    endwin();
}
