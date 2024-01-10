/**
 * @file query_result.h
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

#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include "menuNdata/interactive.h"
#include "utils/utils_i.h"
#include "interactive/settings_config.h"
#include "interactive/instructions.h"
#include "interactive/query_solver.h"

void query_results(SETTINGS settings, int id, void* output);

#endif
