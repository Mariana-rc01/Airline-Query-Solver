/**
 * @file test.h
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

#ifndef TEST_H
#define TEST_H

#include "catalogs/manager_c.h"
#include "entities/flights.h"
#include "entities/passengers.h"
#include "entities/reservations.h"
#include "entities/users.h"
#include "menuNdata/queries.h"
#include "IO/parser.h"
#include "IO/input.h"
#include "IO/output.h"
#include "utils/utils.h"
#include "IO/interpreter.h"
#include "menuNdata/batch.h"

#include "test/file_compare.h"
#include "test/query1_test.h"
#include "test/query2_test.h"
#include "test/query3_test.h"
#include "test/query4_test.h"
#include "test/query5_test.h"
#include "test/query6_test.h"
#include "test/query7_test.h"
#include "test/query8_test.h"
#include "test/query9_test.h"
#include "test/query10_test.h"

typedef void (*queries_test)(MANAGER catalog);

void test(char* pathD, char* pathI, char* pathO);

#endif
