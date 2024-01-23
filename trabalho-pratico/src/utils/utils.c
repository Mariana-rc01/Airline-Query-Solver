/**
 * @file utils.c
 * @brief Module containg utility functions used throughout the program.
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

#include "utils/utils.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>

int set_catalogs(MANAGER manager_catalog, char* path1){
    FILE *flights_file, *passengers_file, *users_file, *reservations_file;
    FILE *flights_error_file, *passengers_error_file, *users_error_file, *reservations_error_file;

    char* flight_path = concat(path1, "/flights.csv");
    flights_file = fopen(flight_path, "r");

    char* passenger_path = concat(path1, "/passengers.csv");
    passengers_file = fopen(passenger_path, "r");

    char* user_path = concat(path1, "/users.csv");
    users_file = fopen(user_path, "r");

    char* reservation_path = concat(path1, "/reservations.csv");
    reservations_file = fopen(reservation_path, "r");

    flights_error_file = fopen("Resultados/flights_errors.csv", "w");
    passengers_error_file = fopen("Resultados/passengers_errors.csv", "w");
    users_error_file = fopen("Resultados/users_errors.csv", "w");
    reservations_error_file = fopen("Resultados/reservations_errors.csv", "w");

    USERS_C users = get_users_c(manager_catalog);
    parseF(users_file, 12, build_user, users, users_error_file);

    FLIGHTS_C flights = get_flights_c(manager_catalog);
    parseF(flights_file, 13, build_flight, flights, flights_error_file);
    parseF(reservations_file, 14, build_reservations, manager_catalog, reservations_error_file);
    parseF(passengers_file, 2, build_passengers, manager_catalog, passengers_error_file);

    free(flight_path);
    free(passenger_path);
    free(user_path);
    free(reservation_path);

    fclose(flights_file);
    fclose(passengers_file);
    fclose(users_file);
    fclose(reservations_file);

    // Verifies if the error files contain any data
    if (isFileEmpty(flights_error_file)) {
        remove("flights_errors.csv");
    }
    if (isFileEmpty(passengers_error_file)) {
        remove("passengers_errors.csv");
    }
    if (isFileEmpty(users_error_file)) {
        remove("users_errors.csv");
    }
    if (isFileEmpty(reservations_error_file)) {
        remove("reservations_errors.csv");
    }

    fclose(flights_error_file);
    fclose(passengers_error_file);
    fclose(users_error_file);
    fclose(reservations_error_file);

    return 0;
}

int isDigit(char c){
    return(c >= '0' && c <= '9');
}

int isNumber(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isDigit(str[i])) {
            return 0; // It isn't a number
        }
    }
    return 1; // It is a number
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
    for(int i = 0; s[i]!= '\0'; i++) {
        s[i] = s[i+1];
    }
    s[strlen(s)] = ' ';
}

FILE* create_output_file(int n){

    char* path = malloc(sizeof(char*)*512);
    sprintf(path, "Resultados/command%d_output.txt", n);
    FILE* f = fopen(path, "w");
    free(path);

    return f;
}

void free_ptr_array(gpointer data){
    GPtrArray* array = (GPtrArray *)data;
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
        string[i] = toupper(string[i]);
    }

    return string;
}

char* first_letter_to_upper(char* string){
    if(string == NULL || string[0] == '\0') return NULL;
    string[0] = toupper(string[0]);
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

int get_flight_delay(FLIGHT flight){
    char* scheduleDate = get_flight_schedule_departure_date(flight);
    char* arrivalDate = get_flight_real_departure_date(flight);

    int result = calculate_flight_delay(scheduleDate, arrivalDate);

    free(scheduleDate);
    free(arrivalDate);

    return result;
}

int dates_timespan ( char* begin, char* end) {
    int yearB, monthB, dayB, dayE, monthE, yearE;
    int result = 0;
    sscanf(begin,"%d/%d/%d",&yearB, &monthB, &dayB);
    sscanf(end,"%d/%d/%d",&yearE, &monthE, &dayE);

    free(begin);
    free(end);

    result =  (dayE-dayB);
    return (result);
}

int get_number_of_nights(RESERV reserv){
    int yearB, monthB, dayB, dayE, monthE, yearE;
    char* begin = get_begin_date(reserv);
    char* end = get_end_date(reserv);

    sscanf(begin,"%d/%d/%d",&yearB, &monthB, &dayB);
    sscanf(end,"%d/%d/%d",&yearE, &monthE, &dayE);

    free(begin);
    free(end);

    return(dayE-dayB);

}

char* int_to_string(int number){
    char* result = malloc(20 * sizeof(char));
    snprintf(result, 20, "%d", number);
    return result;
}

char* double_to_string(double number){
    char* result = malloc(20 * sizeof(char));
    snprintf(result, 20, "%.3f", number);
    return result;
}

int has_spaces(char* str){
    while (*str) {
        if (*str == ' ') return 1;
        str++;
    }
    return 0;
}

void replace_lines_at_start(const char* file_name, const char* new_line1, const char* new_line2) {

    FILE* original_file = fopen(file_name, "r");

    if (original_file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    FILE* new_stream = NULL;
    char* buffer = NULL;
    size_t size = 0;

    new_stream = open_memstream(&buffer, &size);

    if (new_stream == NULL) {
        perror("Error creating memory stream");
        fclose(original_file);
        return;
    }

    fprintf(new_stream, "%s\n%s\n", new_line1, new_line2);

    char line[256];
    while (fgets(line, sizeof(line), original_file) != NULL) {
        fprintf(new_stream, "%s", line);
    }

    // Close the files
    fclose(original_file);
    fclose(new_stream);

    // Open the original file for writing
    FILE* original_file_write = fopen(file_name, "w");

    if (original_file_write == NULL) {
        perror("Error opening file for writing");
        free(buffer);
        return;
    }

    fwrite(buffer, 1, size, original_file_write);

    fclose(original_file_write);

    free(buffer);
}
