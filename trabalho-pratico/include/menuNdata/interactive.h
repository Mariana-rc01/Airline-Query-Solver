/**
 * @file interactive.h
 * @brief Module that contains functions for executing the interactive execution mode aswell as functions 
 * for setting up the catalogs and executing queries.
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
#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "catalogs/manager_c.h"

typedef struct setting *SETTINGS;

#include "interactive/home.h"

SETTINGS create_settings(void);

void set_datasetPath_S(SETTINGS setts, char* path);

void set_changedPath_S(SETTINGS setts, int n);

void set_output_S(SETTINGS setts, int n);

void set_nPages_S(SETTINGS setts, int n);

void set_nOutputs_S(SETTINGS setts, int n);

void set_catalog_S(SETTINGS setts);

void set_nQueries_S(SETTINGS setts, int n);

char* get_datasetPath_S(SETTINGS setts);

int get_changedPath_S(SETTINGS setts);

int get_output_S(SETTINGS setts);

int get_nPages_S(SETTINGS setts);

int get_nOutputs_S(SETTINGS setts);

MANAGER get_catalog_S(SETTINGS setts);

int get_nQueries_S(SETTINGS setts);

void free_settings(SETTINGS setts);

void interactive(void);

#endif
