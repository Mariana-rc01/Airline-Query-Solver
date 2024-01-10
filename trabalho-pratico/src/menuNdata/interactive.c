/**
 * @file interactive.c
 * @brief Contains the code related to the interactive mode
 *
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

#include "menuNdata/interactive.h"
#include <string.h>


struct setting {
    char* datasetPath;
    int changedPath;
    int output; // 1 - txt format, 2 - oneByOne, 3 - number page per Page, 4 - outputs per page
    int nPages;
    int nOutputs;
    MANAGER manager;
};

SETTINGS create_settings(void){
    SETTINGS new = malloc(sizeof(struct setting));
    new->datasetPath = ".";
    new->changedPath = 2;
    new->output = 1;
    new->nPages = 0;
    new->nOutputs = 0;
    USERS_C users_catalog = create_user_c();
    FLIGHTS_C flights_catalog = create_flight_c();
    RESERV_C reservations_catalog = create_reservations_c();
    PASS_C passengers_catalog = create_passengers_c();
    MANAGER manager_catalog = create_manager_c(users_catalog,flights_catalog,reservations_catalog,passengers_catalog);
    new->manager = manager_catalog;

    return new;
}

void set_datasetPath_S(SETTINGS setts, char* path){
    setts->datasetPath = strdup(path);
}

void set_changedPath_S(SETTINGS setts, int n){
    setts->changedPath = n;
}

void set_output_S(SETTINGS setts, int n){
    setts->output = n;
}

void set_nPages_S(SETTINGS setts, int n){
    setts->nPages = n;
}

void set_nOutputs_S(SETTINGS setts, int n){
    setts->nOutputs = n;
}

void set_catalog_S(SETTINGS setts){
    USERS_C users_catalog = create_user_c();
    FLIGHTS_C flights_catalog = create_flight_c();
    RESERV_C reservations_catalog = create_reservations_c();
    PASS_C passengers_catalog = create_passengers_c();
    MANAGER manager_catalog = create_manager_c(users_catalog,flights_catalog,reservations_catalog,passengers_catalog);
    setts->manager = manager_catalog;
}

char* get_datasetPath_S(SETTINGS setts){
     return strdup(setts->datasetPath);
}

int get_changedPath_S(SETTINGS setts){
    return (setts->changedPath);
}

int get_output_S(SETTINGS setts){
    return setts->output;
}

int get_nPages_S(SETTINGS setts){
    return setts->nPages;
}

int get_nOutputs_S(SETTINGS setts){
    return setts->nOutputs;
}

MANAGER get_catalog_S(SETTINGS setts){
    return setts->manager;
}

void interactive(void){

    SETTINGS settings = create_settings();

    home(settings);

    //free_manager_c(settings->manager_catalog);

}
