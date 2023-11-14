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

#include "IO/input.h"
#include "utils/utils.h"
#include "menuNdata/statistics.h"
#include "catalogs/users_c.h"

#include <stdlib.h>
#include <string.h>

/**
 * @struct user
 * @brief Represents user information.
 */
struct user {
    gpointer id; /**< Unique user ID. */
    char* name; /**< User's name. */
    char* email; /**< User's email address. */
    char* phone_number; /**< User's phone number. */
    int age; /**< User's birth date in YYYY/MM/DD format. */
    char* sex; /**< User's gender. */
    char* passport; /**< User's passport information. */
    char* country_code; /**< User's country code. */
    char* address; /**< User's address. */
    char* account_creation; /**< Account creation date and time. */
    char* pay_method; /**< User's payment method. */
    char* account_status; /**< User's account status. */
    double total_spent; /**< User's total spent on reservations. */
};

USER create_user(void){
    USER new = malloc(sizeof(struct user));
    new->name = NULL;
    new->email = NULL;
    new->phone_number = NULL;
    new->age = 0;
    new->sex = NULL;
    new->passport = NULL;
    new->country_code = NULL;
    new->address = NULL;
    new->account_creation = NULL;
    new->pay_method = NULL;
    new->account_status = NULL;
    new->total_spent = 0.0;

    return new;
}

void set_user_id(USER user, gpointer id){
    user->id = id;
}

void set_user_name(USER user, char* name){
    user->name = strdup(name);
}

void set_user_email(USER user, char* email){
    user->email = strdup(email);
}

void set_user_phone_number(USER user, char* phone_number){
    user->phone_number = strdup(phone_number);
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

void set_user_address(USER user, char* address){
    user->address = strdup(address);
}

void set_user_account_creation(USER user, char* account_creation){
    user->account_creation = strdup(account_creation);
}

void set_user_pay_method(USER user, char* pay_method){
    user->pay_method = strdup(pay_method);
}

void set_user_account_status(USER user, char* account_status){
    user->account_status = strdup(account_status);
}

void set_user_total_spent(USER user, double cost){
    user->total_spent = cost;
}

int get_user_id(USER user){
    return GPOINTER_TO_INT(user->id);
}

char* get_user_name(USER user){
    return strdup(user->name);
}

char* get_user_email(USER user){
    return strdup(user->email);
}

char* get_user_phone_number(USER user){
    return strdup(user->phone_number);
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

char* get_user_address(USER user){
    return strdup(user->address);
}

char* get_user_account_creation(USER user){
    return strdup(user->account_creation);
}

char* get_user_pay_method(USER user){
    return strdup(user->pay_method);
}

char* get_user_account_status(USER user){
    return strdup(user->account_status);
}

double get_user_total_spent(USER user){
    return (user->total_spent);
}

void free_user(USER user){
    free(user->name);
    free(user->email);
    free(user->phone_number);
    free(user->sex);
    free(user->passport);
    free(user->country_code);
    free(user->address);
    free(user->account_creation);
    free(user->pay_method);
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

int build_user(char  **user_fields, void *catalog, STATS stats){

    USERS_C usersC = (USERS_C)catalog;
    if (!verify_user(user_fields)) return 0;

    USER user = create_user();
    int age = calculate_user_age(SYSTEM_DATE, user_fields[4]);
    char* acc_status = case_insensitive(user_fields[11]);

    set_catalog_user(usersC, user, user_fields[0]);
    set_user_name(user,user_fields[1]);
    set_user_email(user,user_fields[2]);
    set_user_phone_number(user,user_fields[3]);
    set_user_age(user,age);
    set_user_sex(user,user_fields[5]);
    set_user_passport(user,user_fields[6]);
    set_user_country_code(user,user_fields[7]);
    set_user_address(user,user_fields[8]);
    set_user_account_creation(user,user_fields[9]);
    set_user_pay_method(user,user_fields[10]);
    set_user_account_status(user,acc_status);
    set_user_total_spent(user,0.0);

    insert_user_c(user,usersC,user->id);
    (void) stats;

    return 1;
}
