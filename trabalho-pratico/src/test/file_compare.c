/**
 * @file file_compare.c
 * @brief File containing functions to compare output files with expected results for testing purposes.
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

#include "test/file_compare.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void compare_files(char* pathO, int n) {
    int i = 1, errors = 0;
    FILE *incongruities_file = fopen("Resultados/incongruities.txt", "w");

    if (incongruities_file == NULL) {
        perror("Error opening incongruities.txt for writing");
        return;
    }

    printf("Running tests...\n");

    while (i != n) {
        char pathV[256];
        sprintf(pathV, "Resultados/command%d_output.txt", i);

        char command[256];
        sprintf(command, "/command%d_output.txt", i);
        char *pathE = concat(pathO, command);

        FILE *file1 = fopen(pathE, "r");
        FILE *file2 = fopen(pathV, "r");

        if (file1 == NULL || file2 == NULL) {
            perror("Error opening files for comparison");
            fclose(incongruities_file);
            return;
        }

        char *line1 = NULL;
        char *line2 = NULL;
        size_t len1 = 0;
        size_t len2 = 0;
        ssize_t read1, read2;
        int line_number = 1;

        while (1) {
            read1 = getline(&line1, &len1, file1);
            read2 = getline(&line2, &len2, file2);

            // Compare lines
            if (read1 != read2 || (read1 != -1 && read2 != -1 && strcmp(line1, line2) != 0)) {
                fprintf(incongruities_file, "Discrepancy found at line %d of the command%d_output.txt file:\n",line_number,i);
                fprintf(incongruities_file, "Expected: %s", read1 != -1 ? line1 : "");
                fprintf(incongruities_file, "Obtained: %s\n", read2 != -1 ? line2 : "\n");
                errors++;
                break;
            }

            if (read1 == -1 && read2 == -1) {
                break;
            }

            line_number++;
        }

        free(line1);
        free(line2);
        fclose(file1);
        fclose(file2);
        free(pathE);
        i++;
    }

    fclose(incongruities_file);

    printf("Executed all tests successfully!\n");
    printf("%d anomalies found!\n", errors);
    printf("Verify anomalies in the incongruities.txt file in the Resultados folder\n");

}
