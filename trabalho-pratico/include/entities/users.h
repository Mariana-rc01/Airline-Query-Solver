/**
 * @file users.h
 * @brief This file contains the definition of the user struct and related functions.
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

/**
 * @typedef USER
 * @brief Typedef for struct user pointer.
 */
typedef struct user *USER;

#include "menuNdata/statistics.h"
#include "catalogs/users_c.h"

/**
 * @brief Creates a new user struct with default values.
 * @return A pointer to the newly created user.
 */
USER create_user(void);

/**
 * @brief Sets the user ID.
 * @param user A pointer to the user struct.
 * @param id The user ID.
 */
void set_user_id(USER user, char* id);

/**
 * @brief Sets the user's name.
 * @param user A pointer to the user struct.
 * @param name The user's name.
 */
void set_user_name(USER user, char* name);

/**
 * @brief Sets the user's email address.
 * @param user A pointer to the user struct.
 * @param email The user's email address.
 */
void set_user_email(USER user, char* email);

/**
 * @brief Sets the user's phone number.
 * @param user A pointer to the user struct.
 * @param phone_number The user's phone number.
 */
void set_user_phone_number(USER user, char* phone_number);

/**
 * @brief Sets the user's birth date.
 * @param user A pointer to the user struct.
 * @param birth_date The user's birth date.
 */
void set_user_birth_date(USER user, char* birth_date);

/**
 * @brief Sets the user's gender.
 * @param user A pointer to the user struct.
 * @param sex The user's gender (single character).
 */
void set_user_sex(USER user, char* sex);

/**
 * @brief Sets the user's passport information.
 * @param user A pointer to the user struct.
 * @param passport The user's passport information.
 */
void set_user_passport(USER user, char* passport);

/**
 * @brief Sets the user's country code.
 * @param user A pointer to the user struct.
 * @param country_code The user's country code.
 */
void set_user_country_code(USER user, char* country_code);

/**
 * @brief Sets the user's address.
 * @param user A pointer to the user struct.
 * @param address The user's address.
 */
void set_user_address(USER user, char* address);

/**
 * @brief Sets the user's account creation date and time.
 * @param user A pointer to the user struct.
 * @param account_creation The account creation date and time.
 */
void set_user_account_creation(USER user, char* account_creation);

/**
 * @brief Sets the user's payment method.
 * @param user A pointer to the user struct.
 * @param pay_method The user's payment method.
 */
void set_user_pay_method(USER user, char* pay_method);

/**
 * @brief Sets the user's account status.
 * @param user A pointer to the user struct.
 * @param account_status The user's account status.
 */
void set_user_account_status(USER user, char* account_status);

/**
 * @brief Sets the user's total spent.
 * @param user A pointer to the user struct.
 * @param total_spent The user's total spent.
 */
void set_user_total_spent(USER user, double total_spent);

/**
 * @brief Gets the user ID.
 * @param user A pointer to the user struct.
 * @return The user ID.
 */
char* get_user_id(USER user);

/**
 * @brief Gets the user's name.
 * @param user A pointer to the user struct.
 * @return The user's name.
 */
char* get_user_name(USER user);

/**
 * @brief Gets the user's email address.
 * @param user A pointer to the user struct.
 * @return The user's email address.
 */
char* get_user_email(USER user);

/**
 * @brief Gets the user's phone number.
 * @param user A pointer to the user struct.
 * @return The user's phone number.
 */
char* get_user_phone_number(USER user);

/**
 * @brief Gets the user's birth date.
 * @param user A pointer to the user struct.
 * @return The user's birth date.
 */
char* get_user_birth_date(USER user);

/**
 * @brief Gets the user's gender.
 * @param user A pointer to the user struct.
 * @return The user's gender.
 */
char* get_user_sex(USER user);

/**
 * @brief Gets the user's passport information.
 * @param user A pointer to the user struct.
 * @return The user's passport information.
 */
char* get_user_passport(USER user);

/**
 * @brief Gets the user's country code.
 * @param user A pointer to the user struct.
 * @return The user's country code.
 */
char* get_user_country_code(USER user);

/**
 * @brief Gets the user's address.
 * @param user A pointer to the user struct.
 * @return The user's address.
 */
char* get_user_address(USER user);

/**
 * @brief Gets the user's account creation date and time.
 * @param user A pointer to the user struct.
 * @return The account creation date and time.
 */
char* get_user_account_creation(USER user);

/**
 * @brief Gets the user's payment method.
 * @param user A pointer to the user struct.
 * @return The user's payment method.
 */
char* get_user_pay_method(USER user);

/**
 * @brief Gets the user's account status.
 * @param user A pointer to the user struct.
 * @return The user's account status.
 */
char* get_user_account_status(USER user);

/**
 * @brief Gets the user's total spent.
 * @param user A pointer to the user struct.
 * @return The user's total spent.
 */
double get_user_total_spent(USER user);

/**
 * @brief Frees memory associated with a user struct.
 * @param user A pointer to the user struct.
 */
void free_user(USER user);

/**
 * @brief Verifies the validity of user data.
 * @param fields An array of user data fields.
 * @return 1 if the user data is valid, 0 otherwise.
 */
int verify_user(char** fields, USERS_C users);

/**
 * @brief Builds a user struct from user data fields.
 * @param user_fields An array of user data fields.
 * @param catalog A pointer to the respective catalog.
 * @param stats A pointer to the statistics.
 *
 * @return 1 if the user is added to the catalog 0 if not
 */
int build_user(char **user_fields, void *catalog, STATS stats);

#endif
