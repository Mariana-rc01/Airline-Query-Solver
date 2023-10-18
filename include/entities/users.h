/**
 * @file users.h
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

#ifndef USERS_H
#define USERS_H

typedef struct user *USER;

#include "menuNdata/statistics.h"

USER create_user(void);

void build_user(char  **user_fields, void *catalog, STATS stats);

void set_user_id(USER user, char* id);

void set_user_name(USER user, char* name);

void set_user_email(USER user, char* email);

void set_user_phone_number(USER user, char* phone_number);

void set_user_birth_date(USER user, char* birth_date);

void set_user_sex(USER user, char* sex);

void set_user_passport(USER user, char* passport);

void set_user_country_code(USER user, char* country_code);

void set_user_address(USER user, char* address);

void set_user_account_creation(USER user, char* account_creation);

void set_user_pay_method(USER user, char* pay_method);

void set_user_account_status(USER user, char* account_status);


char* get_user_id(USER user);

char* get_user_name(USER user);

char* get_user_email(USER user);

char* get_user_phone_number(USER user);

int get_user_birth_date(USER user);

char get_user_sex(USER user);

char* get_user_passport(USER user);

char* get_user_country_code(USER user);

char* get_user_address(USER user);

char* get_user_account_creation(USER user);

char* get_user_pay_method(USER user);

char* get_user_account_status(USER user);


void free_user(USER user);

int verify_user(char** fields);

#endif
