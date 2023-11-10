/**
 * @file main.c
 * @brief Contains the entry point to the program
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

#include "entities/flights.h"
#include "entities/passengers.h"
#include "entities/reservations.h"
#include "entities/users.h"
#include "catalogs/manager_c.h"
#include "menuNdata/statistics.h"
#include "IO/parser.h"
#include "IO/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Function main that receives the arguments from the command line
 *
 * Depending on number of arguments starts wither batch mode(2 arguments) or interactive mode (no arguments)
 *
 * @param argc Number of arguments
 * @param argsv Array containing the arguments
 */

int main(int argc, char** argsv){   
    if(argc == 2) {
        batch(argsv[0], argsv[1]);
        
        return 0;
    }
    if(argc == 0) {
        printf("Interactive mode not yet implemented");
        return 0;
    }
    else{
        printf("Invalid number of arguments, must be either 0 or 2\n");
        //perror("Error");
        return 0;
    }
}

