/**
 * @file query_result.c
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

#include "interactive/query_result.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/*
Ver primeiro o que o utilizador escolheu, caso tenha sido txt format, mostrar apenas uma mensagem
- caso contrário, ver a opção e adaptar
- acho que dá para fazer genérico para todas as queries
- txt format
- one by one
- per page by pages
- per page by outputs
- fazer botoes e meter tudo bonito
*/

void query_results(SETTINGS settings, int id, void* output){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WINDOW* win = newwin(20,55,0,0);
    refresh();

    int ch;
    char* title = "Query Results";

    BUTTONS options[3] = {
        create_button("Query id",2,3),
        create_button("[Run]",2,15),
        create_button("[Go Back]",55-strlen("[Go Back]")-2,15)
    };

    BUTTONS config[1] ={
        create_button("--------------- Results ---------------", 1,1),
    };

    int selectedOption = 0;
    int color = get_output_S(settings);

    for (int i = 0; i < 1; i++) {
        mvwprintw(win, get_y_B(config[i]), get_x_B(config[i]), "%s",get_label_B(config[i]));
    }

    char* f = (char*)malloc(sizeof(char) * 10);
    strcpy(f, "False");

    char** results = (char**) output;
    (void) results;

    /*for (int i = 0; i < 8; i++) {
        if(results[i] == NULL) mvwprintw(win, 10+i, 1, "%s",f);
        else if(strcmp(results[i],"T") == 0) mvwprintw(win, 10+i, 1, "%s",f);
        else mvwprintw(win, 10+i, 1, "%s",results[i]);
    }*/

    drawWindow(win, options, selectedOption, title, 3, color);

    (void) id;

    while ((ch = getch()) != 27) {
        int i = 0;
        i++;
    }

    delwin(win);
    endwin();
}
