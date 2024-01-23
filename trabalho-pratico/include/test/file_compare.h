/**
 * @file file_compare.h
 * @brief File containing definition of functions to compare output files with expected results for testing purposes.
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

#ifndef FILE_COMPARE_H
#define FILE_COMPARE_H

#include "utils/utils.h"

/**
 * @brief Compare output files with expected results.
 *
 * This function compares the contents of the generated output files with the expected results.
 * If any discrepancies are found, the function writes the details to the incongruities.txt file.
 *
 * @param pathO The path to the folder containing the expected output files.
 * @param n The number of tests to run.
 */
void compare_files(char* pathO, int n);

#endif
