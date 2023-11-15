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
        result[6] = int_to_string(flight_array_number);

        int flight_delay = get_flight_delay(flight);
        result[7] = int_to_string(flight_delay);
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
        result[6] = int_to_string(nNight);

        int cost = get_cost(reserv);
        result[7] = int_to_string(cost);
    }

    //se n for nem flight nem reserv pode ser user
    else if (get_user_by_id(get_users_c(manager),entity)){
        USER user = get_user_by_id(get_users_c(manager),entity);

        if (strcmp(get_user_account_status(user),"inactive") == 0){
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

    }
    else {
        free(result);
        return NULL;
    }

    (void) stats;
    return result;
}

// é suposto devolver o id dos voos / reservas
// date = schedule_departure_date e begin_date, sem devolver horas
//caso sejam os dois dizer se é flight ou reserva
void* query2(MANAGER manager, STATS stats, char** args){
    /*char* user = args[0];
    USER userE = get_user_by_id(get_users_c(manager),user);
    char** result = malloc(sizeof(char*)*256);

    //primeiro ver se o user_id existe ou se é inactive
    //ver se não é inactive
    if (!userE){
        return NULL;
    }
    else if (strcmp(get_user_account_status(userE), "inactive") == 0){
        return NULL;
    }
    else if (args[1] == NULL){ //listar todos com os tipos

    }
    else if (strcmp(args[1],"reservations") == 0){
        GPtrArray* reservations = get_user_reserv_array_by_id(get_reserv_c(manager),user);

        for (int i = 0; i < (int)reservations->len; i++) {
            RESERV reservation = g_ptr_array_index(reservations, i);
            int reservation_id = get_reservation_id(reservation);
            result[i] = malloc(sizeof(char) * 20);
            snprintf(result[i], 20, "%d", reservation_id);
        }

    }
    else if (strcmp(args[1],"flights") == 0){
        //GPtrArray* flights = get_user_array_by_id(get_pass_c(manager), user);
    }
    else return NULL;*/
    (void) manager;
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

typedef struct {
    char* user_id;
    char* user_name;
} UserInfo;

// Função de comparação para qsort
int compare_user_info(const void *a, const void *b) {
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
            if(strcoll(get_user_account_status(user),"active") == 0) {
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
    for (int i = 0; resultF[i] != NULL; i++) {
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
