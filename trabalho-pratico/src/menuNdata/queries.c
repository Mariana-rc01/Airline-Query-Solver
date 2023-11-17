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
#include "catalogs/users_c.h"
#include "menuNdata/queries.h"
#include "catalogs/reservations_c.h"
#include "catalogs/flights_c.h"
#include "catalogs/manager_c.h"
#include "entities/flights.h"
#include "entities/users.h"
#include "entities/reservations.h"
#include "menuNdata/statistics.h"
#include "utils/utils.h"
#include "IO/input.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void* parser_query(MANAGER catalog, STATS stats, char* line){
    int i = 0;
    char** args = malloc(sizeof(char*) * MAX_ARGS);
    char* copia = strdup(line);
    char* token = strtok(copia, " ");

    while (token != NULL && i < MAX_ARGS) {
        if (token[0] == '"') {
            char temp[100];
            strcpy(temp, token);
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

    args[i] = NULL;

    free(copia);
    free(token);

    int query;
    if(args[0][1] != '0') query = args[0][0] - '0';
    else query = 10;

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
    char** result = malloc(sizeof(char*) * 9);
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
        result[6] = int_to_string(flight_array_number);

        int flight_delay = get_flight_delay(flight);
        result[7] = int_to_string(flight_delay);

        result[8] = "flight";
    }

    //o id das reservas começa sempre com book
    else if (strncmp(entity,"Book", 4) == 0 && get_reservations_by_id(get_reserv_c(manager),entity)){
        RESERV reserv = get_reservations_by_id(get_reserv_c(manager), entity);
        static reservation_table_getters reservation_functions[] = {
            get_hotel_name, get_hotel_name, get_hotel_stars, get_begin_date, get_end_date,
            get_includes_breakfast
        };

        for(i = 0; i < 6; i++){
            result[i] = reservation_functions[i](reserv);
        }

        result[0] = get_hotel_id(reserv);

        int nNight = get_number_of_nights(reserv);
        result[6] = int_to_string(nNight);

        double cost = get_cost(reserv);
        result[7] = double_to_string(cost);
        result[8] = "reservation";
    }

    //se n for nem flight nem reserv pode ser user
    else if (get_user_by_id(get_users_c(manager),entity)){
        USER user = get_user_by_id(get_users_c(manager),entity);

        if (strcmp(get_user_account_status(user),"INACTIVE") == 0){
            free(result);
            return NULL;
        }

        static user_table_getters user_functions[] = {
            get_user_name, get_user_sex, get_user_sex,
            get_user_country_code, get_user_passport
        };

        for(i = 0; i < 5; i++){
            result[i] = user_functions[i](user);
        }

        int age = get_user_age(user);
        result[2] = int_to_string(age);

        int array_flight = get_user_array_number_id(get_pass_c(manager), entity);
        result[5] = int_to_string(array_flight);

        int array_reserv = get_user_array_reserv_id(get_reserv_c(manager), entity);
        result[6] = int_to_string(array_reserv);

        double total_spent = get_user_total_spent(user);
        result[7] = double_to_string(total_spent);

        result[8] = "user";

    }
    else {
        free(result);
        return NULL;
    }
    (void) stats;
    return result;
}

typedef struct {
    char* id;
    char* date;
    char* type;
} ResultEntry;

// Função de comparação para qsort
int compare_datesF(char* itemA, char* itemB) {
    // Comparar anos
    int yearA, monthA, dayA, hourA, minA,segA;
    sscanf(itemA, "%d/%d/%d %d:%d:%d", &yearA, &monthA, &dayA, &hourA, &minA, &segA);

    int yearB, monthB, dayB, hourB, minB, segB;
    sscanf(itemB, "%d/%d/%d %d:%d:%d", &yearB, &monthB, &dayB, &hourB, &minB, &segB);

    if (yearA != yearB){
        return yearB - yearA;  // Ordenar por ano decrescente
    }

    // Comparar meses
    if (monthA != monthB){
        return monthB - monthA;  // Ordenar por mês decrescente
    }

    // Comparar dias
    if (dayB != dayA){
        return dayB - dayA;  // Ordenar por dia decrescente
    }

    if (hourB != hourA){
        return hourB - hourA;
    }

    if (minB != minA){
        return minB - minA;
    }

    return segB - segA;
}

int compare_results(const void* a, const void* b) {
    ResultEntry* entryA = (ResultEntry*)a;
    ResultEntry* entryB = (ResultEntry*)b;

    // Compare as datas
    int dateComparison = compare_datesF(entryA->date, entryB->date);
    if (dateComparison != 0) {
        return dateComparison;
    }

    // Em caso de empate, compare os IDs
    return strcmp(entryA->id, entryB->id);
}

// Função para ordenar o array de resultados com base nos nomes dos usuários e IDs em caso de empate
void sort_results2(char** id, int result_count, char** date, char** types) {
    ResultEntry* result_array = malloc(sizeof(ResultEntry) * result_count);

    // Preencher o array de UserInfo com os dados dos usuários
    for (int i = 0; i < result_count; i++) {
        result_array[i].id = id[i];
        result_array[i].date = date[i];
        result_array[i].type = types[i];
    }

    // Ordenar o array de Users
    qsort(result_array, result_count, sizeof(ResultEntry), compare_results);

    // Reorganizar o array de resultados com base na ordem dos UserInfo ordenados
    for (int i = 0; i < result_count; i++) {
        id[i] = result_array[i].id;
        date[i] = result_array[i].date;
        types[i] = result_array[i].type;
    }

    // Liberar a memória alocada
    free(result_array);
}

void* query2(MANAGER manager, STATS stats, char** args){
    char* user = args[0];
    int length_args = 0;
    while (args[length_args] != NULL) length_args++;
    USER userE = get_user_by_id(get_users_c(manager),user);
    FLIGHTS_C flightsC = get_flights_c(manager);
    RESERV_C reservC = get_reserv_c(manager);

    char** ids = malloc(sizeof(char*)*256);
    char** dates = malloc(sizeof(char*)*256);
    char** types = malloc(sizeof(char*)*256);
    int count = 0;

    //primeiro ver se o user_id existe ou se é inactive
    if (!userE){
        return NULL;
    }
    else if (strcmp(get_user_account_status(userE), "INACTIVE") == 0){
        return NULL;
    }
    else if (length_args == 1){ //listar todos com os tipos
        GPtrArray* flights = get_user_array_by_id(get_pass_c(manager),user);
        GPtrArray* reservations = get_user_reserv_array_by_id(reservC,user);

        // Iterar sobre os voos
        for (int i = 0; i < (int)flights->len; i++) {
            char* flightI = g_ptr_array_index(flights, i);
            FLIGHT flight = get_flight_by_id(flightsC,flightI);
            char* date = get_flight_schedule_departure_date(flight);

            char* id_flight = strdup(flightI);
            ids[count] = id_flight;
            dates[count] = date;
            types[count] = "flight";
            count++;
        }

        // Iterar sobre as reservas
        if (reservations == NULL){
            for (int i = 0; i < (int)reservations->len; i++) {
                char* reservationI = g_ptr_array_index(reservations, i);
                RESERV reservation = get_reservations_by_id(reservC,reservationI);
                char* date = get_begin_date(reservation);

                char* id_reserv = strdup(reservationI);
                ids[count] = id_reserv;
                dates[count] = concat(date," 00:00:00");
                types[count] = "reservation";
                count++;
            }
        }
    }
    else if (strcmp(args[1],"reservations") == 0){
        GPtrArray* reservations = get_user_reserv_array_by_id(reservC,user);

        if (reservations == NULL){
            // Iterar sobre as reservas
            for (int i = 0; i < (int)reservations->len; i++) {
                char* reservationI = g_ptr_array_index(reservations, i);
                RESERV reservation = get_reservations_by_id(reservC,reservationI);
                char* date = get_begin_date(reservation);

                char* id_reserv = strdup(reservationI);
                ids[count] = id_reserv;
                dates[count] = concat(date," 00:00:00");
                types[count] = "reservation";
                count++;
            }
        }
    }
    else if (strcmp(args[1],"flights") == 0){
        GPtrArray* flights = get_user_array_by_id(get_pass_c(manager), user);

        // Iterar sobre os voos
        for (int i = 0; i < (int)flights->len; i++) {
            char* flightI = g_ptr_array_index(flights, i);
            FLIGHT flight = get_flight_by_id(flightsC,flightI);
            char* date = get_flight_schedule_departure_date(flight);

            char* id_flight = strdup(flightI);
            ids[count] = id_flight;
            dates[count] = date;
            types[count] = "flight";
            count++;
        }
    }
    else return NULL;

    // Ordenar os resultados
    char** finalResult = malloc(sizeof(char*)*256);
    finalResult[0] = int_to_string(count);
    sort_results2(ids, count, dates, types);

    if (length_args == 1) finalResult[1] = "all";
    else finalResult[1] = strdup(args[1]);
    for (int j = 2; j < count+2; j++) {
        char *date = strndup(dates[j-2], 10);
        int total_size = snprintf(NULL, 0,"%s;%s;%s\n", ids[j-2], date, types[j-2]) + 1;

        // Alocar memória para a string formatada
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Criar a string formatada
        snprintf(formatted_string, total_size, "%s;%s;%s\n", ids[j-2], date, types[j-2]);

        finalResult[j] = formatted_string;
        printf("%s",finalResult[j]);
        free(ids[j-2]);
        free(dates[j-2]);
        //free(types[j-1]);
    }
    printf("\n");

    free(ids);
    free(dates);
    free(types);
    (void) stats;
    return finalResult;
}

void* query3(MANAGER catalog, STATS stats, char** args){
    (void) catalog;
    (void) stats;
    return args;
}

typedef struct {
    char* id;
    char* date;
} RESERVInfo;

// Função de comparação para qsort
int compare_dates(const void* a, const void* b) {
    char* itemA = (char*)a;
    char* itemB = (char*)b;

    // Comparar anos
    int yearA, monthA, dayA;
    sscanf(itemA, "%d/%d/%d", &yearA, &monthA, &dayA);

    int yearB, monthB, dayB;
    sscanf(itemB, "%d/%d/%d", &yearB, &monthB, &dayB);

    if (yearA != yearB){
        return yearB - yearA;  // Ordenar por ano decrescente
    }

    // Comparar meses
    if (monthA != monthB){
        return monthB - monthA;  // Ordenar por mês decrescente
    }

    // Comparar dias
    return dayB - dayA;  // Ordenar por dia decrescente
}

// Função para comparar duas reservas para ordenação
int compare_reservations(const void* a, const void* b) {
    RESERVInfo* res_a = (RESERVInfo*)a;
    RESERVInfo* res_b = (RESERVInfo*)b;

    // Comparar as datas de início
    int date_compare = compare_dates(res_a->date, res_b->date);
    if (date_compare != 0) {
        return date_compare;
    }

    int compare = strcmp(res_a->id, res_b->id);

    // Se as datas de início forem iguais, usar o identificador da reserva como critério de desempate
    return compare;
}

// Função para ordenar o array de resultados com base nos nomes dos usuários e IDs em caso de empate
void sort_resultsR(char** id, int result_count, char** date) {
    RESERVInfo* reserv_array = malloc(sizeof(RESERVInfo) * result_count);

    // Preencher o array de UserInfo com os dados dos usuários
    for (int i = 0; i < result_count; i++) {
        reserv_array[i].id = id[i];
        reserv_array[i].date = date[i];
    }

    // Ordenar o array de Users
    qsort(reserv_array, result_count, sizeof(RESERVInfo), compare_reservations);

    // Reorganizar o array de resultados com base na ordem dos UserInfo ordenados
    for (int i = 0; i < result_count; i++) {
        id[i] = reserv_array[i].id;
        date[i] = reserv_array[i].date;
    }

    free(reserv_array);
}

void* query4(MANAGER manager, STATS stats, char** args){
    char* hotel_id = args[0];
    RESERV_C catalog = get_reserv_c(manager);

    // Criar um array para armazenar ponteiros para as reservas
    char** reservations_array = malloc(get_number_reserv_id(catalog) * sizeof(char*));
    char** dates_array = malloc(get_number_reserv_id(catalog) * sizeof(char*));
    int i = 0;

    GHashTable* reserv = get_hash_table_reserv(catalog);

    // Iterar sobre as reservas no catálogo
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reserv);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERV reservation = (RESERV)value;

        // Verificar se a reserva pertence ao hotel desejado
        if (strcmp(get_hotel_id(reservation), hotel_id) == 0) {
            reservations_array[i] = get_reserv_from_key(catalog,GINT_TO_POINTER(get_reservation_id(reservation)));
            dates_array[i] = get_begin_date(reservation);
            i++;
        }
    }

    // Ordenar as reservas usando a função de comparação
    sort_resultsR(reservations_array,i,dates_array);

    char** finalResult = malloc(sizeof(char*)*600);
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1; j++) {
        RESERV reservation = get_reservations_by_id(catalog,reservations_array[j-1]);
        int total_size = snprintf(NULL, 0,"%s;%s;%s;%s;%s;%f\n", reservations_array[j-1],
        get_begin_date(reservation), get_end_date(reservation),
        get_user_from_key(catalog, GINT_TO_POINTER(get_user_id_R(reservation))),
        get_rating(reservation), get_cost(reservation)) + 1;

        // Alocar memória para a string formatada
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Criar a string formatada
        snprintf(formatted_string, total_size, "%s;%s;%s;%s;%s;%.3f\n",reservations_array[j-1],
        get_begin_date(reservation), get_end_date(reservation),
        get_user_from_key(catalog, GINT_TO_POINTER(get_user_id_R(reservation))),
        get_rating(reservation), get_cost(reservation));

        finalResult[j] = formatted_string;
    }

    free(reservations_array);

    (void) stats;
    return finalResult;
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

typedef struct {
    char* user_id;
    char* user_name;
} UserInfo;

// Função de comparação para qsort
int compare_user_info(const void* a, const void* b) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    UserInfo* user_info_a = (UserInfo*) a;
    UserInfo* user_info_b = (UserInfo*) b;

    // Comparar os nomes dos usuários
    int name_comparison = strcoll(user_info_a->user_name, user_info_b->user_name);

    if (name_comparison == 0) {
        // Se os nomes são iguais, comparar pelos IDs
        return strcoll(user_info_a->user_id, user_info_b->user_id);
    }

    return name_comparison;
}

// Função para ordenar o array de resultados com base nos nomes dos usuários e IDs em caso de empate
void sort_results(char** result, int result_count, char** names) {
    UserInfo* user_info_array = malloc(sizeof(UserInfo) * result_count);

    // Preencher o array de UserInfo com os dados dos usuários
    for (int i = 0; i < result_count; i++) {
        user_info_array[i].user_id = result[i];
        user_info_array[i].user_name = names[i];
    }

    // Ordenar o array de Users
    qsort(user_info_array, result_count, sizeof(UserInfo), compare_user_info);

    // Reorganizar o array de resultados com base na ordem dos UserInfo ordenados
    for (int i = 0; i < result_count; i++) {
        result[i] = user_info_array[i].user_id;
        names[i] = user_info_array[i].user_name;
    }

    // Liberar a memória alocada
    free(user_info_array);
}

void* query9(MANAGER catalog, STATS stats, char** args) {
    char* prefix = args[0];
    USERS_C usersC = get_users_c(catalog);

    // Obter um array de chaves (gpointer)
    gpointer* keysArray = get_keys_as_array(usersC);
    if (keysArray == NULL){
        return NULL;
    }

    char** result = malloc(sizeof(char*) * 256);
    char** names = malloc(sizeof(char*) * 256);
    int result_count = 0;

    int i = 0;
    int length = calculate_array_length(usersC);
    // Iterar sobre o array de keys
    while(i < length && (keysArray[i] != NULL)){
        gpointer key = keysArray[i];
        USER user = get_user_by_gpointer(usersC, key);

        if (user != NULL){
            if(strcmp(get_user_account_status(user),"ACTIVE") == 0) {
                char* user_name = get_user_name(user);
                char *truncatedString = strndup(user_name, strlen(prefix));

                // Verificar se o nome do utilizador começa com o prefixo
                if (strcoll(truncatedString, prefix) == 0) {
                    result[result_count] = strdup(get_key_by_value(usersC,key));
                    names[result_count] = strdup(user_name);
                    result_count++;
                }
            }
        }
        i++;
    }

    g_free(keysArray);

    sort_results(result, result_count, names);

    char** finalResult = malloc(sizeof(char*)*256);
    finalResult[0] = int_to_string(result_count);
    for (int i = 1; i < result_count+1; i++){
        int total_size = snprintf(NULL, 0, "%s;%s\n", result[i-1], names[i-1]) + 1;

        // Alocar memória para a string formatada
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Criar a string formatada
        snprintf(formatted_string, total_size, "%s;%s\n", result[i-1], names[i-1]);
        finalResult[i] = formatted_string;
        free(result[i-1]);
        free(names[i-1]);
    }

    free(result);
    free(names);

    (void) stats;

    return finalResult;
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
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    for (int i = 0; i < 7; i++) {
        free(resultF[i]);
    }
    free(resultF);
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

void free_query9(void* result) {
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int length = ourAtoi(resultF[0]);
    for (int i = 1; i < length; i++) {
        free(resultF[i]);
    }
    free(resultF);
}


void free_query10(void* result){
    (void) result;
}
