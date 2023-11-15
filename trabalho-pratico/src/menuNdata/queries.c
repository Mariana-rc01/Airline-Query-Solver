/**
 * @file queries.c
 * @brief File that contains the struct and implementation of queries.
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
#include "menuNdata/queries.h"
#include "catalogs/manager_c.h"
#include "entities/flights.h"
#include "entities/users.h"
#include "entities/reservations.h"
#include "menuNdata/statistics.h"
#include "utils/utils.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* parser_query(MANAGER catalog, STATS stats, char* line){
    int i = 0;
    char** args = malloc(sizeof(char*) * MAX_ARGS);
    char* copia = strdup(line);
    char* token = strtok(copia, " ");

    while (token != NULL && i < MAX_ARGS) {
        if (token[0] == '"') {
            char temp[100];
            strcpy(temp, token);
            temp[strlen(temp)-1] = ' ';
            removeQuotes(temp);

            token = strtok(NULL,"\"");
            char* temp1 = concat(temp,token);
            args[i] = strdup(temp1);
            free(temp1);
            i++;
        } else {
            args[i] = strdup(token);
            i++;
        }

        token = strtok(NULL, " ");
    }

    free(copia);
    free(token);

    for (int j = 0; args[0][j] != '\0'; j++) {
        if (!isDigit(args[0][j])) {
            for (int k = 0; k < i; k++) free(args[k]);
            free(args);
            return NULL;
        }
    }

    int query = ourAtoi(args[0]);
    if ((query < 1) || (query > 10)){
        for (int k = 0; k < i; k++) free(args[k]);
        free(args);
        return NULL;
    }

    static queries_func queries[] = {query1, query2, query3,
                                    query4, query5, query6,
                                    query7, query8, query9, query10};

    void* result = queries[query-1](catalog, stats, args+1);

    for (int k = 0; k < i; k++) free(args[k]);
    free(args);

    return result;
}

void* query1(MANAGER manager, STATS stats, char** args){
    char* entity = args[0];
    char** result = malloc(sizeof(char*) * 8);
    int i = 0;
    while (isDigit(entity[i]) && entity[i] != '\0') i++;

    // o id do flight é formado apenas por digitos
    if ((i == (int)strlen(entity)) && get_flight_by_id(get_flights_c(manager),entity)) {
        FLIGHT flight = get_flight_by_id(get_flights_c(manager),entity);
        static flight_table_getters flight_functions[] = {
            get_flight_airline, get_flight_plane_model, get_flight_origin,
            get_flight_destination, get_flight_schedule_departure_date,
            get_flight_schedule_arrival_date
        };

        for(i = 0; i < 6; i++){
            result[i] = flight_functions[i](flight);
        }

        int flight_array_number = get_flight_array_number_by_id(get_pass_c(manager), entity);
        result[6] = strdup(int_to_string(flight_array_number));

        int flight_delay = get_flight_delay(flight);
        result[7] = strdup(int_to_string(flight_delay));
    }

    //o id das reservas começa sempre com book
    else if (strncmp(entity,"Book", 4) == 0 && get_reservations_by_id(get_reserv_c(manager),entity)){
        RESERV reserv = get_reservations_by_id(get_reserv_c(manager), entity);
        static reservation_table_getters reservation_functions[] = {
            get_hotel_id, get_hotel_name, get_hotel_stars, get_begin_date, get_end_date,
            get_includes_breakfast
        };

        for(i = 0; i < 6; i++){
            result[i] = reservation_functions[i](reserv);
        }

        int nNight = get_number_of_nights(reserv);
        result[6] = strdup(int_to_string(nNight));

        int cost = get_cost(reserv);
        result[7] = strdup(int_to_string(cost));
    }

    //se n for nem flight nem reserv pode ser user
    else if (get_user_by_id(get_users_c(manager),entity)){
        USER user = get_user_by_id(get_users_c(manager),entity);

        if (strcmp(get_user_account_status(user),"inactive") == 0) return NULL;

        static user_table_getters user_functions[] = {
            get_user_name, get_user_sex, get_user_sex,
            get_user_country_code, get_user_passport
        };

        for(i = 0; i < 5; i++){
            result[i] = user_functions[i](user);
        }

        int age = get_user_age(user);
        result[2] = strdup(int_to_string(age));

        int array_flight = get_user_array_number_id(get_pass_c(manager), entity);
        result[5] = strdup(int_to_string(array_flight));

        int array_reserv = get_user_array_reserv_id(get_reserv_c(manager), entity);
        result[6] = strdup(int_to_string(array_reserv));

        double total_spent = get_user_total_spent(user);
        result[7] = strdup(double_to_string(total_spent));

    }
    else return NULL;
    (void) stats;
    return result;
}

void* query2(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query3(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query4(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query5(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query6(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query7(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query8(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query9(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void* query10(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

void free_query(void* result, int query_id){

    static free_queries_func queries[] = {free_query1, free_query2, free_query3,
                                        free_query4, free_query5, free_query6,
                                        free_query7, free_query8, free_query9, free_query10};

    queries[query_id - 1](result);

}

void free_query1(void* result){
    (void) result;
}

void free_query2(void* result){
    (void) result;
}

void free_query3(void* result){
    (void) result;
}

void free_query4(void* result){
    (void) result;
}

void free_query5(void* result){
    (void) result;
}

void free_query6(void* result){
    (void) result;
}

void free_query7(void* result){
    (void) result;
}

void free_query8(void* result){
    (void) result;
}

void free_query9(void* result){
    (void) result;
}

void free_query10(void* result){
    (void) result;
}
