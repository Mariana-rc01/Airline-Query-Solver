/**
 * @file utils.h
 * @brief Module that connects all the entities
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
#ifndef UTILS_H
#define UTILS_H

#define SYSTEM_DATE "2023/10/01";

/**
 * @brief Verifies if a character is a digit
 *
 * @param c Character to be verified
 * @return Bool
 */
int isDigit(char c);

/**
 * @brief Verifies if a character is a letter
 *
 * @param c Character to be verified
 * @return Bool
 */
int isLetter(char c);

/**
 * @brief This function casts any String to Int.
 *
 * We can't just cast a String to number, we have to pay attention to units
 * E.g. Thousands, Hundreds, Tens, Ones...
 * For this, we need to raise 10 to the power of the length of the string minus 2
 * This is the Invanriant of this function
 *
 *
 * @param string Accepts any type of string
 * @return Cast from string to int
 */
int ourAtoi(char* string);


#endif
