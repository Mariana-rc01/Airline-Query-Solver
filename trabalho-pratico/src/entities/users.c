/**
 * @file users.c
 * @brief This file contains the implementation of the user struct and related functions.
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

#include "entities/users.h"

#include <stdlib.h>
#include <string.h>
#include <glib.h>

/**
 * @struct user
 * @brief Represents user information.
 */
struct user {
    char* id; /**< Unique user ID. */
    char* name; /**< User's name. */
    int age; /**< User's birth date in YYYY/MM/DD format. */
    char* sex; /**< User's gender. */
    char* passport; /**< User's passport information. */
    char* country_code; /**< User's country code. */
    char* account_status; /**< User's account status. */
    double total_spent; /**< User's total spent on reservations. */
};

USER create_user(void){
    USER new = malloc(sizeof(struct user));
    new->id = NULL;
    new->name = NULL;
    new->age = 0;
    new->sex = NULL;
    new->passport = NULL;
    new->country_code = NULL;
    new->account_status = NULL;
    new->total_spent = 0.0;

    return new;
}

void set_user_id(USER user, char* id){
    user->id = strdup(id);
}

void set_user_name(USER user, char* name){
    user->name = strdup(name);
}

void set_user_age(USER user, int age){
    user->age = age;
}

void set_user_sex(USER user, char* sex){
    user->sex = strdup(sex);
}

void set_user_passport(USER user, char* passport){
    user->passport = strdup(passport);
}

void set_user_country_code(USER user, char* country_code){
    user->country_code = strdup(country_code);
}

void set_user_account_status(USER user, char* account_status){
    user->account_status = strdup(account_status);
}

void set_user_total_spent(USER user, double cost){
    user->total_spent = cost;
}

char* get_user_id(USER user){
    return strdup(user->id);
}

char* get_user_name(USER user){
    return strdup(user->name);
}

int get_user_age(USER user){
    return user->age;
}

char* get_user_sex(USER user){
    return strdup(user->sex);
}

char* get_user_passport(USER user){
    return strdup(user->passport);
}

char* get_user_country_code(USER user){
    return strdup(user->country_code);
}

char* get_user_account_status(USER user){
    return strdup(user->account_status);
}

double get_user_total_spent(USER user){
    return (user->total_spent);
}

void free_user(USER user){
    free(user->name);
    free(user->sex);
    free(user->passport);
    free(user->country_code);
    free(user->account_status);

    free(user);
}

int verify_user(char** fields){
    if (!(fields[0]) || !(fields[1]) || !(fields[3]) ||
        !(fields[5]) || !(fields[6]) || !(fields[8]) ||
        !(fields[10])|| !(fields[4]) || !(fields[9])) return 0;

    if (!(validate_email(fields[2]))) return 0;

    if (!(validate_date_timeless(fields[4]))) return 0;

    if (!(validate_country_code(fields[7]))) return 0;

    if (!(validate_date_time(fields[9]))) return 0;

    if (!(validate_account_status(fields[11]))) return 0;

    if (!(compare_date_timeless(fields[4],fields[9]))) return 0;

    return 1;
}

int build_user(char  **user_fields, void *catalog){

    USERS_C usersC = (USERS_C)catalog;
    if (!verify_user(user_fields)) return 0;

    USER user = create_user();
    int age = calculate_user_age(SYSTEM_DATE, user_fields[4]);
    char* acc_status = case_insensitive(user_fields[11]);

    set_user_id(user, user_fields[0]);
    set_user_name(user,user_fields[1]);
    set_user_age(user,age);
    set_user_sex(user,user_fields[5]);
    set_user_passport(user,user_fields[6]);
    set_user_country_code(user,user_fields[7]);
    set_user_account_status(user,acc_status);
    set_user_total_spent(user,0.0);

    insert_user_c(user,usersC,user->id);

    char year[6];
    char month[3];
    char day[3];
    sscanf(user_fields[9], "%4[^/]/%2[^/]/%2[^/]", year, month, day);

    char* concatenated = concat(year, month);

    insert_userNumber_c(usersC, concatenated, day);

    return 1;
}
