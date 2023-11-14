/**
 * @file utils.c
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

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>

int isDigit(char c){
    return(c >= '0' && c <= '9');
}

int isLetter(char c){
    return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ourAtoi(char* string){
    int i, r = 0;
    double n = pow(10.0,(double)(strlen(string)-1));
    for(i = 0; string[i] != '\0'; i++){
        r += (string[i] - '0') * (int) n;
        n /= 10;
    }

    return r;
}

char* concat(char *s1, char *s2) {

    char *result = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

int isFileEmpty(FILE *file) {

    //File is empty
    if (file == NULL) {
        printf("Invalid csv.\n");
        return -1;
    }

    size_t lsize = 0;
    char *line = NULL;
    int lines = 0;

    while (getline(&line, &lsize, file) != -1) {
        lines++;

        // File isn't empty
        if (lines > 1) {
            free(line);
            return 0;
        }
    }

    free(line);

    return 1;
}

void removeQuotes(char* s) {
    s[strlen(s) - 1] = '\0';
    for(int i = 0; s[i]!= '\0'; i++) {
        s[i] = s[i+1];
    }
}

FILE* create_output_file(int n){

    char* path = malloc(sizeof(char*)*512);
    sprintf(path, "Resultados/comand%d_output.txt", n);
    FILE* f = fopen(path, "w");
    free(path);

    return f;
}

void free_ptr_array(gpointer data){
    GPtrArray *array = (GPtrArray *)data;
    for (guint i = 0; i < array->len; i++) {
        g_free(g_ptr_array_index(array, i));
    }

    g_ptr_array_free(array, TRUE);
}

int calculate_user_age(char* currentDate, char* birthDate){
    int currentYear, currentMonth, currentDay;
    int birthYear, birthMonth, birthDay;

    sscanf(currentDate, "%d/%d/%d", &currentYear, &currentMonth, &currentDay);
    sscanf(birthDate, "%d/%d/%d", &birthYear, &birthMonth, &birthDay);

    int age = currentYear - birthYear;

    // Making sure if the user's birthday has already occured this year
    if (birthMonth > currentMonth || (birthMonth == currentMonth && birthDay > currentDay)) {
        age--;
    }

    return age;
}

char* case_insensitive(char* string){
    for(int i = 0; string[i] != '\0'; i++){
        string[i] = tolower(string[i]);
    }

    return string;
}

int calculate_flight_delay(char* scheduleDate, char* actualDate){
    int scheduleYear, scheduleMonth, scheduleDay, scheduleHour, scheduleMinute, scheduleSecond;
    int actualYear, actualMonth, actualDay, actualHour, actualMinute, actualSecond;

    sscanf(scheduleDate, "%d/%d/%d %d:%d:%d", &scheduleYear, &scheduleMonth, &scheduleDay, &scheduleHour, &scheduleMinute, &scheduleSecond);
    sscanf(actualDate, "%d/%d/%d %d:%d:%d", &actualYear, &actualMonth, &actualDay, &actualHour, &actualMinute, &actualSecond);

    int delay = 0;

    delay += (actualDay - scheduleDay) * 24 * 60 * 60;
    delay += (actualHour - scheduleHour) * 60 * 60;
    delay += (actualMinute - scheduleMinute) * 60;
    delay += actualSecond - scheduleSecond;

    return delay;

}
