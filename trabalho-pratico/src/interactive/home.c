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

void home(void){
    initscr();

    //char* options[3] = {"AirLine Query Solver","Instructions","Exit"};
    // creating a window;
    // with height = 15 and width = 20
    // also with start x axis 2 and start y axis = 10
    // (height, width,x,y)
    // A janela tem que ficar centrada
    // A janela ajusta-se consoante o numero de opçoes e qual o maior tamanho 
    WINDOW* win = newwin(15, 20, 2, 10);
    refresh();

    // making box border with default border styles
    box(win, 0, 0);

    // move and print in window
    mvwprintw(win, 0, 1, "Interactive Mode");
    // Mostrar aqui os botoes de options

    // Selecionar uma opçao e meter cores quando anda pelas opções e quando carregar, mudar para essa página

    // refreshing the window
    wrefresh(win);

    getch();
    endwin();
}
