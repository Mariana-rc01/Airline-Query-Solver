/**
 * @file instructions.c
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

#include "interactive/instructions.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void instructions(void){
    initscr();

    // Cada text aparece numa página em separado, é suposto haver setas para mudar entre os textos, mas
    // a página mantém-se
    char text1[] = "Introdução do programa, o que é e o que faz (em inglês)";

    char text2[] = "Como usar o progama; preencher com os setups desejados, explicar settings e o seu funcionamento detalhadamente";

    char text3[] = "Explicação detalhada de cada query e aqui vai aparecer menu deslizante";

    // Este botão aparece no canto inferior direito
    char option[] = "[Go Back]";

    // creating a window;
    WINDOW* win = newwin(15, 50, 2, 10);
    refresh();

    // making box border with default border styles
    box(win, 0, 0);

    // move and print in window
    mvwprintw(win, 0, 1, "Instructions");
    mvwprintw(win, 1, 1, "%s", text1);
    (void) text2;
    (void) text3;
    (void) option;


    // refreshing the window
    wrefresh(win);

    getch();
    endwin();
}