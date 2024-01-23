/**
 * @file query_result.c
 * @brief Implementation of functions related to query results in interactive mode.
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

void query_results(SETTINGS settings, int id, void* output, char** args){

    int optionFormat = get_output_S(settings);

    //1- Txt format, 2 - oneByOne, 3 - number page per Page, 4 - outputs per page

    static format_func format_window[] = {txtFormat, oneByOne, numberPage, outputsPage};

    format_window[optionFormat - 1](settings, id, output, args);
}

void txtFormat(SETTINGS settings, int id, void* output, char** args){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    WINDOW* win = newwin(20,78,0,0);
    refresh();

    int ch;
    char* title = "Query Results";

    int MAX_OPTIONS = 3;

    BUTTONS options[3] = {
        create_button("[Try Again]",2,15),
        create_button("[Home]",38,15),
        create_button("[Go Back]",78-strlen("[Go Back]")-2,15)
    };

    int selectedOption = 0;
    int color = 0;

    char* info[10] = {
        "1",
        "id;date[;type]",
        "rating",
        "id;begin_date;end_date;user_id;rating;total_price",
        "id;schedule_departure_date;destination;airline;plane_model",
        "name;passengers",
        "name;median",
        "revenue",
        "id;name",
        "(year|month|day);users;flights;passengers;unique_pass..;reservations"
    };

    if (id == 1 || id == 3 || id == 4 || id == 7 || id == 9){
        mvwprintw(win, 1, 1, "Query ID: %d; arg: %s", id, args[0]);
        mvwprintw(win, 2, 1, "Output info: %s", info[id-1]);
    }
    else if (id == 2 || id == 6 || id == 10){
        if (args[1] == NULL) args[1] = "Both";
        mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s", id, args[0], args[1]);
        mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
    }
    else{ // 5 e 8
        mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s, arg3: %s", id, args[0], args[1], args[2]);
        mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
    }

    //criar ficheiro txt

    int n = get_nQueries_S(settings);

    FILE* output_file = create_output_file(n);

    if (output != NULL){
        output_query(output_file, output, id);
        free_query(output,id);
    }
    fclose(output_file);

    mvwprintw(win, 4, 1, "------------------------------------ Results --------------------------------");
    mvwprintw(win, 5, 1, "Text file created successfully in Resultados:");
    mvwprintw(win, 6, 1, "      command%d_output.txt.", n);

    set_nQueries_S(settings,n+1);

    drawWindow(win, options, selectedOption, title, 3, color);

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

                if (strcmp(option, "[Try Again]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 3; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    solver(settings);
                    exit(0);
                }

                if (strcmp(option, "[Home]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 3; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 3; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
    }

    delwin(win);
    endwin();
}

void oneByOne(SETTINGS settings, int id, void* output, char** args){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    WINDOW* win = newwin(23,78,0,0);
    refresh();

    int ch;
    char* title = "Query Results";

    int MAX_OPTIONS = 5;

    BUTTONS options[5] = {
        create_button(" < ",38,19),
        create_button(" > ",41,19),
        create_button("[Try Again]",2,21),
        create_button("[Home]",38,21),
        create_button("[Go Back]",78-strlen("[Go Back]")-2,21)
    };

    int selectedOption = 0;

    drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

    int q = get_nQueries_S(settings);

    set_nQueries_S(settings, q+1);

    int currentPage = 1;
    char** results = (char**)output;
    int nArgs = 0;
    if (output != NULL && (id != 3 && id != 8)){
        nArgs = ourAtoi(results[0]);
    }

    int resultsPerPage = 12;
    int nPages = 1;
    int n = 1;
    int verify = 0;

    char* info[10] = {
        "1",
        "id;date[;type]",
        "rating",
        "id;begin_date;end_date;user_id;rating;total_price",
        "id;schedule_departure_date;destination;airline;plane_model",
        "name;passengers",
        "name;median",
        "revenue",
        "id;name",
        "(year|month|day);users;flights;passengers;unique_pass..;reservations"
    };

    while (1) {
        wclear(win);

        if (id == 1 || id == 3 || id == 4 || id == 7 || id == 9){
            mvwprintw(win, 1, 1, "Query ID: %d; arg: %s", id, args[0]);
            mvwprintw(win, 2, 1, "Output info: %s", info[id-1]);
        }
        else if (id == 2 || id == 6 || id == 10){
            if (args[1] == NULL) args[1] = "Both";
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s", id, args[0], args[1]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }
        else{ // 5 e 8
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s, arg3: %s", id, args[0], args[1], args[2]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }

        mvwprintw(win, 4, 1, "------------------------------------ Results --------------------------------");

        if (output != NULL){
            mvwprintw(win, 5, 1, "--  ---   ---   ---   ---   ---  --- Page %d ---   ---   ---   ---   ---  ---", currentPage);
            if (id == 1){
                if (currentPage == 1){
                    for (int i = 0; i < 8; i++) {
                        if (results[i] == NULL) {
                            results[i] = "False";
                        } else if (strcmp(results[i], "T") == 0) {
                            results[i] = "True";
                        }
                        mvwprintw(win, 6+i, 1, "%s", results[i]);
                    }
                }
                mvwprintw(win, 19, 1, "All outputs are displayed :)  ");
            }
            else if (id == 3 || id == 8){
                char* result = (char*)output;
                if (currentPage == 1){
                    int total_size = snprintf(NULL, 0, "%s", result) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", result);
                    mvwprintw(win, 6, 1, "%s", formatted_string);
                    free(formatted_string);
                }
                mvwprintw(win, 19, 1, "All outputs are displayed :)  ");
            }
            else if (id == 2 || id == 10) {
                int startIdx = (currentPage == 1) ? 2 : 2 + 12*(currentPage - 1);
                int endIdx = (currentPage == 1) ? 2 + startIdx + n : startIdx + n;

                if (verify == 1){
                    endIdx = startIdx + 12;
                }

                // Array bounds
                if (endIdx > nArgs + 2) {
                    endIdx = nArgs + 2;
                    verify = 1;
                }

                for (int j = startIdx; j < endIdx ; j++) {
                    // Display only results belonging to the current page
                    int total_size = snprintf(NULL, 0, "%s", results[j]) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", results[j]);
                    mvwprintw(win, 6 + (j-2) % resultsPerPage, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            else {

                int startIdx = (currentPage == 1) ? 1 : 1 + 12*(currentPage - 1);
                int endIdx = (currentPage == 1) ? 1 + startIdx + n : startIdx + n;

                if (verify == 1){
                    endIdx = startIdx + 12;
                }

                // Ensure not to exceed array bounds
                if (endIdx > nArgs + 1) {
                    endIdx = nArgs + 1;
                    verify = 1;
                }

                for (int j = startIdx; j < endIdx ; j++) {
                    // Display only results belonging to the current page
                    int total_size = snprintf(NULL, 0, "%s", results[j]) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", results[j]);
                    mvwprintw(win, 6 + (j-1) % resultsPerPage, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            if ((id != 1 && id != 3 && id != 8) && verify == 1)
                mvwprintw(win, 19, 1, "All outputs are displayed");
            else if (id != 1 && id != 3 && id != 8) mvwprintw(win, 19, 1, "Press c to see the next");
        }
        else mvwprintw(win, 5, 3, "Nothing to show");

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

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

                if (strcmp(option, " < ") == 0) {
                    if (output != NULL){
                        currentPage = (currentPage - 2 + nPages) % nPages + 1;
                    }
                }

                if (strcmp(option, " > ") == 0){
                    if (output != NULL){
                        currentPage = (currentPage) % nPages + 1;
                    }
                }

                if (strcmp(option, "[Try Again]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    solver(settings);
                    exit(0);
                }

                if (strcmp(option, "[Home]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    settingsConfig(settings);
                    exit(0);
                }
                free(option);
                break;

            case 'c':
                if (n < nArgs && output != NULL) {
                    n++;
                    if (n == resultsPerPage) {
                        currentPage++;
                        nPages++;
                        n = 0;
                    }
                }
                break;
        }

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);
    }

    delwin(win);
    endwin();
}

void numberPage(SETTINGS settings, int id, void* output, char** args){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    WINDOW* win = newwin(23,78,0,0);
    refresh();

    int ch;
    char* title = "Query Results";

    int MAX_OPTIONS = 5;

    BUTTONS options[5] = {
        create_button(" < ",38,19),
        create_button(" > ",41,19),
        create_button("[Try Again]",2,21),
        create_button("[Home]",38,21),
        create_button("[Go Back]",78-strlen("[Go Back]")-2,21)
    };

    int selectedOption = 0;

    int n = get_nQueries_S(settings);

    set_nQueries_S(settings, n+1);

    int currentPage = 1; // Variable to control the current page
    char** results = (char**)output;
    int nPages = get_nPages_S(settings);
    int nArgs = 0;
    int resultsPerPage = 0;
    if (output != NULL && (id != 3 && id != 8)){
        nArgs = ourAtoi(results[0]);
        resultsPerPage = (nArgs / nPages) + ((nArgs % nPages) > 0); // Number of results per page
    }

    int pageSize = 12;
    int scrollStart = 1;
    int scrollEnd = pageSize;

    ch = 'u';

    char* info[10] = {
        "1",
        "id;date[;type]",
        "rating",
        "id;begin_date;end_date;user_id;rating;total_price",
        "id;schedule_departure_date;destination;airline;plane_model",
        "name;passengers",
        "name;median",
        "revenue",
        "id;name",
        "(year|month|day);users;flights;passengers;unique_pass..;reservations"
    };

    while (1) {
        wclear(win);

        if (id == 1 || id == 3 || id == 4 || id == 7 || id == 9){
            mvwprintw(win, 1, 1, "Query ID: %d; arg: %s", id, args[0]);
            mvwprintw(win, 2, 1, "Output info: %s", info[id-1]);
        }
        else if (id == 2 || id == 6 || id == 10){
            if (args[1] == NULL) args[1] = "Both";
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s", id, args[0], args[1]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }
        else{ // 5 e 8
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s, arg3: %s", id, args[0], args[1], args[2]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }

        mvwprintw(win, 4, 1, "------------------------------------ Results --------------------------------");

        if (output != NULL){
            mvwprintw(win, 5, 1, "--  ---   ---   ---   ---   ---  --- Page %d ---   ---   ---   ---   ---  ---", currentPage);

            if (id == 1){
                if (currentPage == 1){
                    for (int i = 0; i < 8; i++) {
                        if (results[i] == NULL) {
                            results[i] = "False";
                        } else if (strcmp(results[i], "T") == 0) {
                            results[i] = "True";
                        }
                        mvwprintw(win, 6+i, 1, "%s", results[i]);
                    }
                }
            }
            else if (id == 2 || id == 10){
                int startIdx = 2 + resultsPerPage * (currentPage - 1);
                int endIdx = startIdx + resultsPerPage;

                // Array limits
                if (endIdx > nArgs + 2) {
                    endIdx = nArgs + 2;
                }

                 // Page scroll
                if (ch == 'u' && scrollStart > 1) {
                    scrollStart--;
                    scrollEnd--;
                }

                if (ch == 'd' && scrollEnd < endIdx) {
                    scrollStart++;
                    scrollEnd++;
                }

                // Ensure not to exceed array limits
                if (scrollEnd > endIdx) {
                    scrollEnd = endIdx;
                }

                if (resultsPerPage <= 12){
                    for (int j = startIdx; j <= endIdx; j++) {
                        // Display only results belonging to the current page
                        int total_size = snprintf(NULL, 0, "%s", results[j - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j - 1]);
                        mvwprintw(win, 6 + (j - 1) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }
                else {
                    mvwprintw(win, 19, 1, "press 'u' to go up");
                    mvwprintw(win, 19, 55, "press 'd' to go down");
                    for (int j = scrollStart; j <= scrollEnd && scrollEnd < endIdx && (j + startIdx - 1)< nArgs; j++) {
                        // Display only results belonging to the current page
                        int total_size = snprintf(NULL, 0, "%s", results[j + startIdx - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j + startIdx - 1]);
                        mvwprintw(win, 6 + (j - scrollStart) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }

            }
            else if (id == 3 || id == 8){
                char* result = (char*)output;
                if (currentPage == 1){
                    int total_size = snprintf(NULL, 0, "%s", result) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", result);
                    mvwprintw(win, 6, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            else{

            int startIdx = 1 + resultsPerPage * (currentPage - 1);
            int endIdx = startIdx + resultsPerPage;

            if (endIdx > nArgs + 1) {
                endIdx = nArgs + 1;
            }

            if (ch == 'u' && scrollStart > 1) {
                scrollStart--;
                scrollEnd--;
            }

            if (ch == 'd' && scrollEnd < endIdx) {
                scrollStart++;
                scrollEnd++;
            }

            if (scrollEnd > endIdx) {
                scrollEnd = endIdx;
            }

            if (resultsPerPage <= 12){
                    for (int j = startIdx; j <= endIdx; j++) {
                        int total_size = snprintf(NULL, 0, "%s", results[j - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j - 1]);
                        mvwprintw(win, 6 + (j - 1) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }
            else {
                mvwprintw(win, 19, 1, "press 'u' to go up");
                mvwprintw(win, 19, 55, "press 'd' to go down");
                for (int j = scrollStart; j <= scrollEnd && scrollEnd < endIdx && (j + startIdx -1)< nArgs; j++) {
                    int total_size = snprintf(NULL, 0, "%s", results[j + startIdx - 1]) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", results[j + startIdx - 1]);
                    mvwprintw(win, 6 + (j - scrollStart) % resultsPerPage, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            }
        }
        else mvwprintw(win, 5 , 3, "Nothing to show");

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

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

                if (strcmp(option, " < ") == 0) {
                    if (output != NULL){
                        currentPage = (currentPage - 2 + nPages) % nPages + 1;
                        pageSize = 12;
                        scrollStart = 1;
                        scrollEnd = pageSize;
                    }
                }

                if (strcmp(option, " > ") == 0){
                    if (output != NULL){
                        currentPage = (currentPage) % nPages + 1;
                        pageSize = 12;
                        scrollStart = 1;
                        scrollEnd = pageSize;
                    }
                }

                if (strcmp(option, "[Try Again]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    solver(settings);
                    exit(0);
                }

                if (strcmp(option, "[Home]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
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
    }

    delwin(win);
    endwin();
}

void outputsPage(SETTINGS settings, int id, void* output, char** args){
    initscr();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);

    WINDOW* win = newwin(23,78,0,0);
    refresh();

    int ch;
    char* title = "Query Results";

    int MAX_OPTIONS = 5;

    BUTTONS options[5] = {
        create_button(" < ",38,19),
        create_button(" > ",41,19),
        create_button("[Try Again]",2,21),
        create_button("[Home]",38,21),
        create_button("[Go Back]",78-strlen("[Go Back]")-2,21)
    };

    int selectedOption = 0;

    int n = get_nQueries_S(settings);

    set_nQueries_S(settings, n+1);

    int currentPage = 1; // Variable to control the current page
    char** results = (char**)output;
    int nPages = 0;
    int nArgs = 0;
    int resultsPerPage = get_nOutputs_S(settings);
    if (output != NULL && (id != 3 && id != 8)){
        nArgs = ourAtoi(results[0]);
        nPages = (nArgs / resultsPerPage) + ((nArgs % resultsPerPage) > 0); // Number of results per page
    }

    int pageSize = 12;
    int scrollStart = 1;
    int scrollEnd = pageSize;

    ch = 'u';

    char* info[10] = {
        "1",
        "id;date[;type]",
        "rating",
        "id;begin_date;end_date;user_id;rating;total_price",
        "id;schedule_departure_date;destination;airline;plane_model",
        "name;passengers",
        "name;median",
        "revenue",
        "id;name",
        "(year|month|day);users;flights;passengers;unique_pass..;reservations"
    };

    while (1) {
        wclear(win);

        if (id == 1 || id == 3 || id == 4 || id == 7 || id == 9){
            mvwprintw(win, 1, 1, "Query ID: %d; arg: %s", id, args[0]);
            mvwprintw(win, 2, 1, "Output info: %s", info[id-1]);
        }
        else if (id == 2 || id == 6 || id == 10){
            if (args[1] == NULL) args[1] = "Both";
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s", id, args[0], args[1]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }
        else{ // 5 e 8
            mvwprintw(win, 1, 1, "Query ID: %d; arg1: %s, arg2: %s, arg3: %s", id, args[0], args[1], args[2]);
            mvwprintw(win, 3, 1, "Output info: %s", info[id-1]);
        }

        mvwprintw(win, 4, 1, "------------------------------------ Results --------------------------------");

        if (output != NULL){
            mvwprintw(win, 5, 1, "--  ---   ---   ---   ---   ---  --- Page %d ---   ---   ---   ---   ---  ---", currentPage);

            if (id == 1){
                if (currentPage == 1){
                    for (int i = 0; i < 8; i++) {
                        if (results[i] == NULL) {
                            results[i] = "False";
                        } else if (strcmp(results[i], "T") == 0) {
                            results[i] = "True";
                        }
                        mvwprintw(win, 6+i, 1, "%s", results[i]);
                    }
                }
            }
            else if (id == 2 || id == 10){
                int startIdx = 2 + resultsPerPage * (currentPage - 1);
                int endIdx = startIdx + resultsPerPage;

                // Array limits
                if (endIdx > nArgs + 2) {
                    endIdx = nArgs + 2;
                }

                // Page scroll
                if (ch == 'u' && scrollStart > 1) {
                    scrollStart--;
                    scrollEnd--;
                }

                if (ch == 'd' && scrollEnd < endIdx) {
                    scrollStart++;
                    scrollEnd++;
                }

                // Ensure not to exceed array limits
                if (scrollEnd > endIdx) {
                    scrollEnd = endIdx;
                }

                if (resultsPerPage <= 12){
                    for (int j = startIdx; j <= endIdx; j++) {
                        // Display only results belonging to the current page
                        int total_size = snprintf(NULL, 0, "%s", results[j - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j - 1]);
                        mvwprintw(win, 6 + (j - 1) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }
                else {
                    mvwprintw(win, 19, 1, "press 'u' to go up");
                    mvwprintw(win, 19, 55, "press 'd' to go down");
                    for (int j = scrollStart; j <= scrollEnd && scrollEnd < endIdx && (j + startIdx - 1)< nArgs; j++) {
                        // Display only results belonging to the current page
                        int total_size = snprintf(NULL, 0, "%s", results[j + startIdx - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j + startIdx - 1]);
                        mvwprintw(win, 6 + (j - scrollStart) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }

            }
            else if (id == 3 || id == 8){
                char* result = (char*)output;
                if (currentPage == 1){
                    int total_size = snprintf(NULL, 0, "%s", result) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", result);
                    mvwprintw(win, 6, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            else{

            int startIdx = 1 + resultsPerPage * (currentPage - 1);
            int endIdx = startIdx + resultsPerPage;

            if (endIdx > nArgs + 1) {
                endIdx = nArgs + 1;
            }

            if (ch == 'u' && scrollStart > 1) {
                scrollStart--;
                scrollEnd--;
            }

            if (ch == 'd' && scrollEnd < endIdx) {
                scrollStart++;
                scrollEnd++;
            }

            if (scrollEnd > endIdx) {
                scrollEnd = endIdx;
            }

            if (resultsPerPage <= 12){
                    for (int j = startIdx; j <= endIdx; j++) {
                        int total_size = snprintf(NULL, 0, "%s", results[j - 1]) + 1;
                        char* formatted_string = malloc(total_size);
                        snprintf(formatted_string, total_size, "%s", results[j - 1]);
                        mvwprintw(win, 6 + (j - 1) % resultsPerPage, 1, "%s", formatted_string);
                        free(formatted_string);
                    }
                }
            else {
                mvwprintw(win, 19, 1, "press 'u' to go up");
                mvwprintw(win, 19, 55, "press 'd' to go down");
                for (int j = scrollStart; j <= scrollEnd && scrollEnd < endIdx && (j + startIdx -1)< nArgs; j++) {
                    int total_size = snprintf(NULL, 0, "%s", results[j + startIdx - 1]) + 1;
                    char* formatted_string = malloc(total_size);
                    snprintf(formatted_string, total_size, "%s", results[j + startIdx - 1]);
                    mvwprintw(win, 6 + (j - scrollStart) % resultsPerPage, 1, "%s", formatted_string);
                    free(formatted_string);
                }
            }
            }
        }
        else mvwprintw(win, 5 , 3, "Nothing to show");

        drawWindow(win, options, selectedOption, title, MAX_OPTIONS, 0);

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

                if (strcmp(option, " < ") == 0) {
                    if (output != NULL){
                        currentPage = (currentPage - 2 + nPages) % nPages + 1;
                        pageSize = 12;
                        scrollStart = 1;
                        scrollEnd = pageSize;
                    }
                }

                if (strcmp(option, " > ") == 0){
                    if (output != NULL){
                        currentPage = (currentPage) % nPages + 1;
                        pageSize = 12;
                        scrollStart = 1;
                        scrollEnd = pageSize;
                    }
                }

                if (strcmp(option, "[Try Again]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    solver(settings);
                    exit(0);
                }

                if (strcmp(option, "[Home]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
                    werase(win);
                    wrefresh(win);
                    endwin();
                    home(settings);
                    exit(0);
                }

                if (strcmp(option, "[Go Back]") == 0){
                    free(args);
                    free(option);
                    for (int i = 0; i < 5; i++) free_button(options[i]);
                    free_query(output,id);
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
    }

    delwin(win);
    endwin();
}

