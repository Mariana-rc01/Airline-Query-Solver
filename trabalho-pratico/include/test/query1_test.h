/**
 * @file query1_test.h
 * @brief Test file for Query 1 function.
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

#ifndef QUERY1_TEST_H
#define QUERY1_TEST_H

#include "utils/utils.h"
#include "catalogs/manager_c.h"
#include "menuNdata/queries.h"

/**
 * @brief Test function for Query 1.
 *
 * This function tests the behavior and performance of Query 1 for different scenarios.
 *
 * @param manager manager.
 */
void query1_test(MANAGER manager);

#endif
