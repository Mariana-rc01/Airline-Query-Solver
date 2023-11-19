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

    // Check if the entity ID is a digit, indicating it might be a flight ID
    while (isDigit(entity[i]) && entity[i] != '\0') i++;

    // If the ID is composed of digits and corresponds to a flight
    if ((i == (int)strlen(entity)) && get_flight_by_id(get_flights_c(manager), entity)) {
        FLIGHT flight = get_flight_by_id(get_flights_c(manager), entity);
        static flight_table_getters flight_functions[] = {
            get_flight_airline, get_flight_plane_model, get_flight_origin,
            get_flight_destination, get_flight_schedule_departure_date,
            get_flight_schedule_arrival_date
        };

        // Retrieve flight information using getter functions
        for (i = 0; i < 6; i++) {
            result[i] = flight_functions[i](flight);
        }

        // Get the number of flights in the array based on the flight ID
        int flight_array_number = get_flight_array_number_by_id(get_pass_c(manager), entity);
        result[6] = int_to_string(flight_array_number);

        // Get the delay of the flight
        int flight_delay = get_flight_delay(flight);
        result[7] = int_to_string(flight_delay);

        result[8] = "flight";
    }

    // If the ID starts with "Book" and corresponds to a reservation
    else if (strncmp(entity, "Book", 4) == 0 && get_reservations_by_id(get_reserv_c(manager), entity)) {
        RESERV reserv = get_reservations_by_id(get_reserv_c(manager), entity);
        static reservation_table_getters reservation_functions[] = {
            get_hotel_name, get_hotel_name, get_hotel_stars, get_begin_date, get_end_date,
            get_includes_breakfast
        };

        // Retrieve reservation information using getter functions
        for (i = 0; i < 6; i++) {
            result[i] = reservation_functions[i](reserv);
        }

        // Get the hotel ID from the reservation
        result[0] = get_hotel_id(reserv);

        // Get the number of nights in the reservation
        int nNight = get_number_of_nights(reserv);
        result[6] = int_to_string(nNight);

        // Get the cost of the reservation
        double cost = get_cost(reserv);
        result[7] = double_to_string(cost);

        result[8] = "reservation";
    }

    // If the entity is a user
    else if (get_user_by_id(get_users_c(manager), entity)) {
        USER user = get_user_by_id(get_users_c(manager), entity);

        // Check if the user is inactive, if so, return NULL
        if (strcmp(get_user_account_status(user), "INACTIVE") == 0) {
            free(result);
            return NULL;
        }

        static user_table_getters user_functions[] = {
            get_user_name, get_user_sex, get_user_sex,
            get_user_country_code, get_user_passport
        };

        // Retrieve user information using getter functions
        for (i = 0; i < 5; i++) {
            result[i] = user_functions[i](user);
        }

        // Get the age of the user
        int age = get_user_age(user);
        result[2] = int_to_string(age);

        // Get the number of flights associated with the user
        int array_flight = get_user_array_number_id(get_pass_c(manager), entity);
        result[5] = int_to_string(array_flight);

        // Get the number of reservations associated with the user
        int array_reserv = get_user_array_reserv_id(get_reserv_c(manager), entity);
        result[6] = int_to_string(array_reserv);

        // Get the total amount spent by the user
        double total_spent = get_user_total_spent(user);
        result[7] = double_to_string(total_spent);

        result[8] = "user";
    } else {
        // If the entity is not recognized, free the result array and return NULL
        free(result);
        return NULL;
    }
    
    (void) stats;
    return result;
}


/**
 * @file
 * @brief Structure representing a result entry.
 *
 * This structure holds information about a result entry, including an identifier (id),
 * a date, and a type. It is commonly used to store and organize data related to query results.
 * The members of this structure are typically filled with data retrieved from a database or
 * another data source and are used for sorting and processing the results.
 */
typedef struct {
    char* id;      ///< Identifier associated with the result entry.
    char* date;    ///< Date associated with the result entry.
    char* type;    ///< Type associated with the result entry.
} ResultEntry;

/**
 * @brief Compares two date strings in the format "yyyy/mm/dd hh:mm:ss".
 *
 * This function compares two date strings, first by years, then months, days, hours,
 * minutes, and seconds. The returning integer is positive if itemB is later than itemA,
 * negative if itemB is earlier than itemA, and zero if they are equal.
 *
 * @param itemA The first date string.
 * @param itemB The second date string.
 * @return The result of the comparison.
 */
int compare_datesF(char* itemA, char* itemB) {
    // Comparar anos
    int yearA, monthA, dayA, hourA, minA,segA;
    sscanf(itemA, "%d/%d/%d %d:%d:%d", &yearA, &monthA, &dayA, &hourA, &minA, &segA);

    int yearB, monthB, dayB, hourB, minB, segB;
    sscanf(itemB, "%d/%d/%d %d:%d:%d", &yearB, &monthB, &dayB, &hourB, &minB, &segB);

    if (yearA != yearB){
        return yearB - yearA;  // Sort by year in descending order
    }

    // Compare months
    if (monthA != monthB){
        return monthB - monthA;  // sort by month in descending order
    }

    // Compare days
    if (dayB != dayA){
        return dayB - dayA;  // Sort days by descending order
    }

    //Compare hours
    if (hourB != hourA){
        return hourB - hourA; //Sort hours in descending order
    }

    //Compare minutes
    if (minB != minA){
        return minB - minA; //Sort minutesin descending order
    }

    return segB - segA; //Sort seconds in descending order
}

/**
 * @brief Compares two ResultEntry structures based on date and ID.
 *
 * This function is designed to be used with the qsort function to sort an array
 * of ResultEntry structures. It first compares dates using the compare_datesF
 * function and then, in case of a tie, compares IDs using strcmp. The result is
 * suitable for sorting entries in chronological order and alphabetical order by ID.
 *
 * @param a Pointer to the first ResultEntry.
 * @param b Pointer to the second ResultEntry.
 * @return The result of the comparison.
 */
int compare_results(const void* a, const void* b) {
    ResultEntry* entryA = (ResultEntry*)a;
    ResultEntry* entryB = (ResultEntry*)b;

    // Compare dates
    int dateComparison = compare_datesF(entryA->date, entryB->date);
    if (dateComparison != 0) {
        return dateComparison;
    }

    // In case of a tie compare Ids
    return strcmp(entryA->id, entryB->id);
}

/**
 * @brief Sorts an array of results based on dates and IDs in case of a tie.
 *
 * This function takes arrays of IDs, dates, and types and sorts their content based on
 * chronological order (dates) and alphabetical order (IDs). The input arrays are then
 * modified to represent their sorted order.
 *
 * @param id An array of user IDs.
 * @param result_count The number of entries in the arrays.
 * @param date An array of date strings.
 * @param types An array of result types.
 */
void sort_results2(char** id, int result_count, char** date, char** types) {
    ResultEntry* result_array = malloc(sizeof(ResultEntry) * result_count);

    // Fill UserInfo array with user data
    for (int i = 0; i < result_count; i++) {
        result_array[i].id = id[i];
        result_array[i].date = date[i];
        result_array[i].type = types[i];
    }

    // Sort User array
    qsort(result_array, result_count, sizeof(ResultEntry), compare_results);

    // Reorganize the arrays based of the sorted UserInfo array
    for (int i = 0; i < result_count; i++) {
        id[i] = result_array[i].id;
        date[i] = result_array[i].date;
        types[i] = result_array[i].type;
    }

    // Free alocated memory
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

    //Check if user_id exists
    if (!userE){
        return NULL;
    }
    else if (strcmp(get_user_account_status(userE), "INACTIVE") == 0){
        return NULL;
    }
    else if (length_args == 1){ //list all types
        GPtrArray* flights = get_user_array_by_id(get_pass_c(manager),user);
        GPtrArray* reservations = get_user_reserv_array_by_id(reservC,user);

        // Iterate over flights
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

        // Iterate over reservations
        for (int i = 0; i < (int)reservations->len; i++) {
            gpointer reservationI = g_ptr_array_index(reservations, i);
            RESERV reservation = get_reservations_by_gpointer(reservC,reservationI);
            char* reservs = get_reserv_from_key(reservC, reservationI);
            char* date = get_begin_date(reservation);

            char* id_reserv = strdup(reservs);
            ids[count] = id_reserv;
            dates[count] = concat(date," 00:00:00");
            types[count] = "reservation";
            count++;
        }
    }
    else if (strcmp(args[1],"reservations") == 0){
        GPtrArray* reservations = get_user_reserv_array_by_id(reservC,user);

        // Iterate over reservations
        for (int i = 0; i < (int)reservations->len; i++) {
            gpointer reservationI = g_ptr_array_index(reservations, i);
            RESERV reservation = get_reservations_by_gpointer(reservC,reservationI);
            char* reservs = get_reserv_from_key(reservC, reservationI);
            char* date = get_begin_date(reservation);

            char* id_reserv = strdup(reservs);
            ids[count] = id_reserv;
            dates[count] = concat(date," 00:00:00");
            types[count] = "reservation";
            count++;
        }
    }
    else if (strcmp(args[1],"flights") == 0){
        GPtrArray* flights = get_user_array_by_id(get_pass_c(manager), user);

        // Iterate over flights
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

    // Sort ressults
    char** finalResult = malloc(sizeof(char*)*256);
    finalResult[0] = int_to_string(count);
    sort_results2(ids, count, dates, types);

    if (length_args == 1) finalResult[1] = "all";
    else finalResult[1] = strdup(args[1]);
    for (int j = 2; j < count+2; j++) {
        char *date = strndup(dates[j-2], 10);
        int total_size = snprintf(NULL, 0,"%s;%s;%s", ids[j-2], date, types[j-2]) + 1;

        // Alocatte memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create formatted string
        snprintf(formatted_string, total_size, "%s;%s;%s", ids[j-2], date, types[j-2]);

        finalResult[j] = formatted_string;
        free(ids[j-2]);
        free(dates[j-2]);
        //free(types[j-1]);
    }

    free(ids);
    free(dates);
    free(types);
    (void) stats;
    return finalResult;
}

void* query3(MANAGER manager, STATS stats, char** args){
    char* hotel_id = args[0];
    RESERV_C catalog = get_reserv_c(manager);

    // Create array that contains pointers to reservation
    double rating = 0;
    int i = 0;

    GHashTable* reserv = get_hash_table_reserv(catalog);

    // Iterate over reservations in the catalog
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reserv);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERV reservation = (RESERV)value;

        // Verify if a reservation belongs to the desired hotel
        if (strcmp(get_hotel_id(reservation), hotel_id) == 0) {
            char* ratingH = get_rating(reservation);
            double add;
            sscanf(ratingH, "%lf", &add);
            rating += add;
            i++;
            free(ratingH);
        }
    }

    rating = rating/(double)i;

    char* finalResult = malloc(sizeof(char*)*128);
    finalResult = double_to_string(rating);

    (void) stats;
    return finalResult;
}

/**
 * @typedef RESERVInfo
 * @brief Structure representing reservation information.
 *
 * This structure holds information about a reservation, including the reservation ID
 * and the date of the reservation. It is used for sorting and organizing reservation data.
 */
typedef struct {
    char* id;
    char* date;
} RESERVInfo;

/**
 * @brief Compares two date strings in the format "yyyy/mm/dd".
 *
 * This function compares two date strings, first by years, then months, then days.
 * The returning integer is positive if itemB is later than itemA, negative if itemB
 * is earlier than itemA, and zero if they are equal.
 *
 * @param a Pointer to the first date string.
 * @param b Pointer to the second date string.
 * @return The result of the comparison.
 */
int compare_dates(const void* a, const void* b) {
    char* itemA = (char*)a;
    char* itemB = (char*)b;

    // Compare years
    int yearA, monthA, dayA;
    sscanf(itemA, "%d/%d/%d", &yearA, &monthA, &dayA);

    int yearB, monthB, dayB;
    sscanf(itemB, "%d/%d/%d", &yearB, &monthB, &dayB);

    if (yearA != yearB){
        return yearB - yearA;  // Sort by year in descending order
    }

    // Compare months
    if (monthA != monthB){
        return monthB - monthA;  // Sort by month in descending order
    }

    // Compare days
    return dayB - dayA;  // Sort by day in descending order
}

/**
 * @brief Compares two reservations based on their dates and IDs.
 *
 * This function is designed to be used with the qsort function to compare two RESERVInfo 
 * structures. It first compares dates using the compare_dates function and then,
 * in case of a tie, compares reservation IDs using strcmp.
 *
 * @param a Pointer to the first RESERVInfo structure.
 * @param b Pointer to the second RESERVInfo structure.
 * @return The result of the comparison.
 */
int compare_reservations(const void* a, const void* b) {
    RESERVInfo* res_a = (RESERVInfo*)a;
    RESERVInfo* res_b = (RESERVInfo*)b;

    // Compare begin dates
    int date_compare = compare_dates(res_a->date, res_b->date);
    if (date_compare != 0) {
        return date_compare;
    }

    //If begin dates are equal use the reservation Id as a tiebreaker
    int compare = strcmp(res_a->id, res_b->id);
    return compare;
}

/**
 * @brief Sorts an array of reservation results based on dates and reservation IDs.
 *
 * This function takes arrays of reservation IDs and dates and organizes them based on
 * chronological order (dates) and alphabetical order (IDs). It uses the compare_reservations
 * function for the sorting process. The input arrays are thenmodified to represent their 
 * sorted order.
 *
 * @param id An array of reservation IDs.
 * @param result_count The number of entries in the arrays.
 * @param date An array of reservation dates.
 */
void sort_resultsR(char** id, int result_count, char** date) {
    RESERVInfo* reserv_array = malloc(sizeof(RESERVInfo) * result_count);

    // Fill UserInfo array with user data
    for (int i = 0; i < result_count; i++) {
        reserv_array[i].id = id[i];
        reserv_array[i].date = date[i];
    }

    // Sort user array
    qsort(reserv_array, result_count, sizeof(RESERVInfo), compare_reservations);

    // Reorganize the arrays based in the sorted UserInfo array
    for (int i = 0; i < result_count; i++) {
        id[i] = reserv_array[i].id;
        date[i] = reserv_array[i].date;
    }

    free(reserv_array);
}

void* query4(MANAGER manager, STATS stats, char** args){
    char* hotel_id = args[0];
    RESERV_C catalog = get_reserv_c(manager);

    // Create an array to store pointers to the reservations
    char** reservations_array = malloc(get_number_reserv_id(catalog) * sizeof(char*));
    char** dates_array = malloc(get_number_reserv_id(catalog) * sizeof(char*));
    int i = 0;

    GHashTable* reserv = get_hash_table_reserv(catalog);

    // Iterate over catalog reservations
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reserv);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERV reservation = (RESERV)value;

        // Verify if a reservation belongs to a given hotel
        if (strcmp(get_hotel_id(reservation), hotel_id) == 0) {
            reservations_array[i] = strdup(get_reserv_from_key(catalog,GINT_TO_POINTER(get_reservation_id(reservation))));
            dates_array[i] = get_begin_date(reservation);
            i++;
        }
    }

    // Sort reservations using sort function
    sort_resultsR(reservations_array,i,dates_array);

    char** finalResult = malloc(sizeof(char*)*600);
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1; j++) {
        RESERV reservation = get_reservations_by_id(catalog,reservations_array[j-1]);
        int total_size = snprintf(NULL, 0,"%s;%s;%s;%s;%s;%f", reservations_array[j-1],
        get_begin_date(reservation), get_end_date(reservation),
        get_user_from_key(catalog, GINT_TO_POINTER(get_user_id_R(reservation))),
        get_rating(reservation), get_cost(reservation)) + 1;

        // Allocate memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%s;%s;%s;%s;%.3f",reservations_array[j-1],
        get_begin_date(reservation), get_end_date(reservation),
        get_user_from_key(catalog, GINT_TO_POINTER(get_user_id_R(reservation))),
        get_rating(reservation), get_cost(reservation));

        finalResult[j] = formatted_string;
    }
    
    //Free Allocated memory
    free(reservations_array);
    free(dates_array);

    (void) stats;
    return finalResult;
}

/**
 * @typedef FlightInfo
 * @brief Structure representing flight information.
 *
 * This structure holds information about a flight, including the flight ID
 * and the date of the flight. It is used for sorting and organizing flight data.
 */
typedef struct {
    char* id;
    char* date;
} FlightInfo;

/**
 * @brief Compares two flight entries based on their dates and IDs.
 *
 * This function is compares two FlightInfo structures. It first compares dates 
 * using the compare_datesF function, and then, in case of a tie, compares flight IDs using strcmp.
 *
 * @param a Pointer to the first FlightInfo structure.
 * @param b Pointer to the second FlightInfo structure.
 * @return The result of the comparison.
 */
int compare_flights(const void* a, const void* b) {
    FlightInfo* f_a = (FlightInfo*)a;
    FlightInfo* f_b = (FlightInfo*)b;

    // Compare begin dates
    int date_compare = compare_datesF(f_a->date, f_b->date);
    if (date_compare != 0) {
        return date_compare;
    }

    // If the begin dates are the same use flight Id as a tiebreaker
    int compare = strcmp(f_a->id, f_b->id);
    return compare;
}

/**
 * @brief Sorts an array of flight results based on dates and flight IDs.
 *
 * This function takes arrays of flight IDs and dates and organizes them based on
 * chronological order (dates) and alphabetical order (IDs). It uses the compare_flights
 * function for the sorting process. The input arrays are then modified to represent their
 * the sorted order.
 *
 * @param id An array of flight IDs.
 * @param result_count The number of entries in the arrays.
 * @param date An array of flight dates.
 */
void sort_resultsF(char** id, int result_count, char** date) {
    FlightInfo* flight_array = malloc(sizeof(FlightInfo) * result_count);

    // Fill FlightInfo array with user data
    for (int i = 0; i < result_count; i++) {
        flight_array[i].id = id[i];
        flight_array[i].date = date[i];
    }

    // Sort flights array
    qsort(flight_array, result_count, sizeof(FlightInfo), compare_flights);

    // Reorganize the resulting arrays based off sorted FlightInfo array
    for (int i = 0; i < result_count; i++) {
        id[i] = flight_array[i].id;
        date[i] = flight_array[i].date;
    }

    free(flight_array);
}

void* query5(MANAGER manager, STATS stats, char** args){
    char* origin = args[0];
    char* begin_date = args[1];
    char* end_date = args[2];
    FLIGHTS_C catalog = get_flights_c(manager);

    // Create an array to store pointers to reservations
    char** flights_array = malloc(512 * sizeof(char*));
    char** dates_array = malloc(512 * sizeof(char*));
    int i = 0;

    GHashTable* flights = get_hash_table_flight(catalog);

    // Iterate over catalog reservations
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flights);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        FLIGHT flight = (FLIGHT)value;
        char* date = get_flight_schedule_arrival_date(flight);

        // Verify if a reservation belongs to the desire hotel
        if (strcmp(get_flight_origin(flight), origin) == 0 &&
        (compare_datesF(begin_date,date) >= 0 && compare_datesF(date,end_date) >= 0)) {
            flights_array[i] = get_flight_from_key(catalog,GINT_TO_POINTER(get_flight_id(flight)));
            dates_array[i] = get_flight_schedule_arrival_date(flight);
            i++;
        }
    }

    // Sort flights using compare function
    sort_resultsF(flights_array,i,dates_array);

    char** finalResult = malloc(sizeof(char*)*600);
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1; j++) {
        //id;schedule_departure_date;destination;airline;plane_model
        FLIGHT flight = get_flight_by_id(catalog, flights_array[j-1]);

        int total_size = snprintf(NULL, 0,"%s;%s;%s;%s;%s\n", flights_array[j-1],
        get_flight_schedule_departure_date(flight), get_flight_destination(flight),
        get_flight_airline(flight),get_flight_plane_model(flight)) + 1;

        // Alocatte memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create formatted string
        snprintf(formatted_string, total_size, "%s;%s;%s;%s;%s", flights_array[j-1],
        get_flight_schedule_departure_date(flight), get_flight_destination(flight),
        get_flight_airline(flight),get_flight_plane_model(flight));

        finalResult[j] = formatted_string;
    }

    free(flights_array);
    free(dates_array);
    (void) stats;
    return finalResult;
}

/**
 * @typedef FlightInfo
 * @brief Structure representing flight information.
 *
 * This structure holds information about a flight, including the flight ID
 * and the date of the flight. It is used for sorting and organizing flight data.
 */
typedef struct {
    char* name;
    int nPassengers;
} AirportInfo;

/**
 * @brief Compares two airport entries based on the number of passengers and airport names.
 *
 * This function is designed to be used with the qsort function to sort an array of
 * AirportInfo structures. It first compares the number of passengers in descending
 * order and, in case of a tie, compares airport names using strcmp. The result is suitable
 * for sorting entries based on passenger count and alphabetical order of airport names.
 *
 * @param a Pointer to the first AirportInfo structure.
 * @param b Pointer to the second AirportInfo structure.
 * @return The result of the comparison.
 */
int sort_airports(const void* a, const void* b) {
    AirportInfo* f_a = (AirportInfo*)a;
    AirportInfo* f_b = (AirportInfo*)b;

    // Compare number of passengers
    int date_compare = f_b->nPassengers - f_a->nPassengers;
    if (date_compare != 0) {
        return date_compare;
    }

    // If the number of passengers is the same, use airport name as a tiebreaker
    int compare = strcmp(f_a->name, f_b->name);
    return compare;
}

/**
 * @brief Finds the position of an airport in an array or returns -1 if not present.
 *
 * This function searches for the specified airport name in an array of AirportInfo
 * structures. If the airport name is found, the function returns the position in the
 * array; otherwise, it returns -1 to indicate that the airport is not present.
 *
 * @param array The array of AirportInfo structures.
 * @param size The number of entries in the array.
 * @param airport The name of the airport to search for.
 * @return The position of the airport in the array or -1 if not found.
 */
int findAirportPosition(AirportInfo* array, int size, const char* airport) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].name, airport) == 0) {
            // The airport name was found in the array
            return i;
        }
    }
    // Airport name was not found in the array
    return -1;
}

// receives <Year> and N
// retorn airport name and number of passengers
void* query6(MANAGER manager, STATS stats, char** args){
    char* Year = args[0];
    int N = ourAtoi(args[1]);
    FLIGHTS_C catalog = get_flights_c(manager);
    PASS_C passengers = get_pass_c(manager);

    AirportInfo* array = malloc(sizeof(AirportInfo) * 512);

    int i = 0;

    GHashTable* flights = get_hash_table_flight(catalog);

    // Iterate over catalog reservations
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flights);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        FLIGHT flight = (FLIGHT) value;

        char* date = get_flight_schedule_arrival_date(flight);
        char *truncatedString = strndup(date, 4);
        char* origin = get_flight_origin(flight);
        char* destination = get_flight_destination(flight);

        char* id_flight = get_flight_from_key(catalog, GINT_TO_POINTER(get_flight_id(flight)));
        int pass = get_flight_array_number_by_id(passengers, id_flight);

        // Verify if a airport belongs to the desired year
        if (strcmp(Year,truncatedString) == 0){
        // Verify if an airport name, has been registered, if it was increment nº of passengers
            int airportPosition = findAirportPosition(array, i, origin);
            if (airportPosition != -1){ // é para incrementar no array[i] que tem aquele aeroporto
                array[airportPosition].nPassengers += pass;
            }
            else {
                array[i].name = origin;
                array[i].nPassengers = pass;
                i++;
            }

            int airportPositionD = findAirportPosition(array, i, destination);
            if (airportPositionD != -1){ // Increments in the array[i] with the airport
                array[airportPositionD].nPassengers += pass;
            }
            else {
                array[i].name = destination;
                array[i].nPassengers = pass;
                i++;
            }
        }
    }

    // Sort flights using compare function
    qsort(array, i, sizeof(AirportInfo), sort_airports);


    char** finalResult = malloc(sizeof(char*)*600);
    finalResult[0] = int_to_string(N);
    for (int j = 1; j < i+1 && j<N+1; j++) {
        int total_size = snprintf(NULL, 0,"%s;%d", array[j-1].name,
        array[j-1].nPassengers) + 1;

        // Alocatte memory to a formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%d", array[j-1].name, array[j-1].nPassengers);

        finalResult[j] = formatted_string;
    }

    (void) stats;
    return finalResult;
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

void* query9(MANAGER catalog, STATS stats, char** args) {
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
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    free(resultF);
}

void free_query4(void* result){
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    for (int i = 0; i < n; i++) {
        free(resultF[i]);
    }
    free(resultF);
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
    (void) result;
}

void free_query10(void* result){
    (void) result;
}
