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

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void* query1(MANAGER manager,char** args){
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
        int flight_array_number = get_flight_nPassengers(flight);
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
            get_hotel_id, get_hotel_name, get_hotel_stars, get_begin_date, get_end_date,
            get_includes_breakfast
        };

        // Retrieve reservation information using getter functions
        for(i = 0; i < 6; i++){
            result[i] = reservation_functions[i](reserv);
        }

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
        char* status = get_user_account_status(user);

        // Check if the user is inactive, if so, return NULL
        if (strcmp(status, "INACTIVE") == 0) {
            free(result);
            free(status);
            return NULL;
        }

        static user_table_getters user_functions[] = {
            get_user_name, get_user_sex, get_user_sex,
            get_user_country_code, get_user_passport
        };

        // Retrieve user information using getter functions
        for(i = 0; i < 5; i++){
            if(i != 2){
            result[i] = user_functions[i](user);
            }
            else result[i] = int_to_string(get_user_age(user));
        }

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
        free(status);
    } else {
        // If the entity is not recognized, free the result array and return NULL
        free(result);
        return NULL;
    }

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
    char* id;      /**< Identifier associated with the result entry. */
    char* date;    /**< Date associated with the result entry. */
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
        return minB - minA; //Sort minutes in descending order
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

void* query2(MANAGER manager,char** args){
    char* user = args[0];
    int length_args = 0;
    while (args[length_args] != NULL) length_args++;
    USER userE = get_user_by_id(get_users_c(manager),user);
    FLIGHTS_C flightsC = get_flights_c(manager);
    RESERV_C reservC = get_reserv_c(manager);

    //Check if user_id exists
    if (!userE){
        return NULL;
    }

    ResultEntry* result_array = malloc(sizeof(ResultEntry) * 256);
    int count = 0;

    char* status = get_user_account_status(userE);
    if (strcmp(status, "INACTIVE") == 0){
        free(result_array);
        free(status);
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
            result_array[count].id = id_flight;
            result_array[count].date = date;
            count++;
        }

        // Iterate over reservations
        for (int i = 0; i < (int)reservations->len; i++) {
            char* reservationI = g_ptr_array_index(reservations, i);
            RESERV reservation = get_reservations_by_id(reservC,reservationI);
            char* date = get_begin_date(reservation);

            char* id_reserv = strdup(reservationI);
            result_array[count].id = id_reserv;
            result_array[count].date = concat(date," 00:00:00");
            count++;
            free(date);
        }
    }
    else if (strcmp(args[1],"reservations") == 0){
        GPtrArray* reservations = get_user_reserv_array_by_id(reservC,user);

        // Iterate over reservations
        for (int i = 0; i < (int)reservations->len; i++) {
            char* reservationI = g_ptr_array_index(reservations, i);
            RESERV reservation = get_reservations_by_id(reservC,reservationI);
            char* date = get_begin_date(reservation);

            char* id_reserv = strdup(reservationI);
            result_array[count].id = id_reserv;
            result_array[count].date = concat(date," 00:00:00");
            count++;
            free(date);
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
            result_array[count].id = id_flight;
            result_array[count].date = date;
            count++;
        }
    }
    else {
        free(result_array);
        return NULL;
    }

    // Sort ressults
    char** finalResult = malloc(sizeof(char*)*256);
    finalResult[0] = int_to_string(count);
    qsort(result_array, count, sizeof(ResultEntry), compare_results);

    if (length_args == 1) finalResult[1] = NULL;
    else finalResult[1] = strdup(args[1]);
    for (int j = 2; j < count+2; j++) {
        char* date = strndup(result_array[j-2].date, 10);
        char* id = result_array[j-2].id;
        int total_size = snprintf(NULL, 0,"%s;%s", id, date) + 1;

        // Alocatte memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create formatted string
        snprintf(formatted_string, total_size, "%s;%s", id, date);

        finalResult[j] = strdup(formatted_string);
        free(formatted_string);
        free(date);
        free(result_array[j-2].id);
        free(result_array[j-2].date);
    }

    free(status);
    free(result_array);
    return finalResult;
}

void* query3(MANAGER manager,char** args){
    char* hotel_id = args[0];
    RESERV_C catalog = get_reserv_c(manager);

    double rating = 0;
    int i = 0;

    GPtrArray* hotel_array = get_hotel_reserv_array_by_id(catalog, hotel_id);

    if (hotel_array != NULL){
        for (guint j = 0; j < hotel_array->len; j++) {
            char* reserv_id = g_ptr_array_index(hotel_array, j);
            RESERV reservation = get_reservations_by_id(catalog, reserv_id);
            char* ratingH = get_rating(reservation);
            double add;
            sscanf(ratingH, "%lf", &add);
            rating += add;
            i++;
            free(ratingH);
        }
        rating = rating/(double)i;
    }
    else rating = 0;

    char* finalResult = double_to_string(rating);

    return finalResult;
}

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
    ResultEntry* res_a = (ResultEntry*)a;
    ResultEntry* res_b = (ResultEntry*)b;

    // Compare begin dates
    int date_compare = compare_dates(res_a->date, res_b->date);
    if (date_compare != 0) {
        return date_compare;
    }

    //If begin dates are equal use the reservation Id as a tiebreaker
    int compare = strcmp(res_a->id, res_b->id);
    return compare;
}

void* query4(MANAGER manager,char** args){
    char* hotel_id = args[0];
    RESERV_C catalog = get_reserv_c(manager);

    // Create an array to store pointers to the reservations
    int initialCapacity = 500;
    ResultEntry* reserv_array = malloc(sizeof(ResultEntry) * initialCapacity);
    int i = 0;

    GPtrArray* hotel_array = get_hotel_reserv_array_by_id(catalog, hotel_id);

    if (hotel_array != NULL){
        for (guint j = 0; j < hotel_array->len; j++) {
            if (i >= initialCapacity) {
                initialCapacity *= 2;
                reserv_array = realloc(reserv_array, sizeof(ResultEntry) * initialCapacity);
            }
            char* reserv_id = g_ptr_array_index(hotel_array, j);
            RESERV reservation = get_reservations_by_id(catalog, reserv_id);
            reserv_array[i].id = get_reservation_id(reservation);
            reserv_array[i].date = get_begin_date(reservation);
            i++;
        }
    }
    else {
        free(reserv_array);
        return NULL;
    }

    // Sort reservations using sort function
    qsort(reserv_array, i, sizeof(ResultEntry), compare_reservations);

    char** finalResult = malloc(sizeof(char*)*(i+1));
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1; j++) {
        RESERV reservation = get_reservations_by_id(catalog,reserv_array[j-1].id);
        char* begin = get_begin_date(reservation);
        char* end = get_end_date(reservation);
        char* user = get_user_id_R(reservation);
        char* rating = get_rating(reservation);

        int total_size = snprintf(NULL, 0,"%s;%s;%s;%s;%s;%f", reserv_array[j-1].id,
        begin, end, user, rating, get_cost(reservation)) + 1;

        // Allocate memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%s;%s;%s;%s;%.3f",reserv_array[j-1].id,
        begin, end, user, rating, get_cost(reservation));

        finalResult[j] = formatted_string;
        free(begin);
        free(user);
        free(end);
        free(rating);
        free(reserv_array[j-1].id);
        free(reserv_array[j-1].date);
    }

    free(reserv_array);

    return finalResult;
}

void* query5(MANAGER manager,char** args){
    char* origin = args[0];
    char* begin_date = args[1];
    char* end_date = args[2];
    FLIGHTS_C catalog = get_flights_c(manager);

    // Create an array to store pointers to reservations
    int initialCapacity = 500;
    ResultEntry* flight_array = malloc(sizeof(ResultEntry) * initialCapacity);

    int i = 0;

    GHashTable* flights = get_hash_table_flight(catalog);

    // Iterate over catalog reservations
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flights);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        FLIGHT flight = (FLIGHT)value;
        char* date = get_flight_schedule_departure_date(flight);
        char* originC = get_flight_origin(flight);

        // Verify if a reservation belongs to the desire hotel
        if (strcmp(originC, origin) == 0 &&
        (compare_datesF(begin_date,date) >= 0 && compare_datesF(date,end_date) >= 0)) {
            if (i >= initialCapacity) {
                initialCapacity *= 2;
                flight_array = realloc(flight_array, sizeof(ResultEntry) * initialCapacity);
            }
            flight_array[i].id = get_flight_id(flight);
            flight_array[i].date = get_flight_schedule_departure_date(flight);
            i++;
        }
        free(date);
        free(originC);
    }

    // Sort flights using compare function
    qsort(flight_array, i, sizeof(ResultEntry), compare_results);

    char** finalResult = malloc(sizeof(char*)*(i+1));
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1; j++) {
        //id;schedule_departure_date;destination;airline;plane_model
        FLIGHT flight = get_flight_by_id(catalog, flight_array[j-1].id);

        char* schedule_departure_date = get_flight_schedule_departure_date(flight);
        char* destination = get_flight_destination(flight);
        char* airline = get_flight_airline(flight);
        char* plane_model = get_flight_plane_model(flight);

        int total_size = snprintf(NULL, 0,"%s;%s;%s;%s;%s\n", flight_array[j-1].id,
        schedule_departure_date, destination, airline,plane_model) + 1;

        // Alocatte memory to formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create formatted string
        snprintf(formatted_string, total_size, "%s;%s;%s;%s;%s", flight_array[j-1].id,
        schedule_departure_date, destination, airline,plane_model);

        finalResult[j] = formatted_string;
        free(flight_array[j-1].id);
        free(flight_array[j-1].date);
        free(schedule_departure_date);
        free(destination);
        free(airline);
        free(plane_model);
    }

    free(flight_array);
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
// return airport name and number of passengers
void* query6(MANAGER manager,char** args){
    char* Year = args[0];
    int N = ourAtoi(args[1]);
    FLIGHTS_C catalog = get_flights_c(manager);

    int initialCapacity = 500;
    AirportInfo* array = malloc(sizeof(AirportInfo) * initialCapacity);

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

        char* id_flight = get_flight_id(flight);
        int pass = get_flight_nPassengers(flight);

        // Verify if a airport belongs to the desired year
        if (strcmp(Year,truncatedString) == 0){
        // Verify if an airport name, has been registered, if it was increment nº of passengers
            int airportPosition = findAirportPosition(array, i, origin);
            if (airportPosition != -1){ // é para incrementar no array[i] que tem aquele aeroporto
                array[airportPosition].nPassengers += pass;
            }
            else {
                if (i >= initialCapacity) {
                    initialCapacity *= 2;
                    array = realloc(array, sizeof(AirportInfo) * initialCapacity);
                }
                array[i].name = strdup(origin);
                array[i].nPassengers = pass;
                i++;
            }

            int airportPositionD = findAirportPosition(array, i, destination);
            if (airportPositionD != -1){ // Increments in the array[i] with the airport
                array[airportPositionD].nPassengers += pass;
            }
            else {
                if (i >= initialCapacity) {
                    // Se atingir a capacidade máxima, dobre o tamanho
                    initialCapacity *= 2;
                    array = realloc(array, sizeof(AirportInfo) * initialCapacity);
                }
                array[i].name = strdup(destination);
                array[i].nPassengers = pass;
                i++;
            }
        }
        free(date);
        free(truncatedString);
        free(origin);
        free(destination);
        free(id_flight);
    }

    // Sort flights using compare function
    qsort(array, i, sizeof(AirportInfo), sort_airports);

    char** finalResult = malloc(sizeof(char*)*(N+1));
    finalResult[0] = (i < N ? int_to_string(i) : int_to_string(N));
    for (int j = 1; j < i+1 && j<N+1; j++) {
        int total_size = snprintf(NULL, 0,"%s;%d", array[j-1].name,
        array[j-1].nPassengers) + 1;

        // Alocatte memory to a formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%d", array[j-1].name, array[j-1].nPassengers);

        finalResult[j] = formatted_string;
    }

    for(int j = 0; j < i; j++){
        free(array[j].name);
    }

    free(array);

    return finalResult;
}


typedef struct {
    char* name;
    GArray* delays;
    int n_delays;
    int median;
} AirportInfo2;

int sort_airports2(const void* a, const void* b) {
    AirportInfo2* f_a = (AirportInfo2*)a;
    AirportInfo2* f_b = (AirportInfo2*)b;

    // Compare delays
    int delay_compare = f_b->median - f_a->median;
    if (delay_compare != 0) {
        return delay_compare;
    }

    // If the number of passengers is the same, use airport name as a tiebreaker
    int compare = strcmp(f_a->name, f_b->name);
    return compare;
}

int findAirportPosition2(AirportInfo2* array, int size, const char* airport) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].name, airport) == 0) {
            // The airport name was found in the array
            return i;
        }
    }
    // Airport name was not found in the array
    return -1;
}


int compare_ints(gconstpointer a, gconstpointer b) {
    return *(const int*)a - *(const int*)b;
}

//Listar o top N aeroportos com a maior mediana de atrasos.
void* query7(MANAGER manager,char** args){
    //guardar todas os atrasos num array para cada aeroporto e obter a mediana
    int N = ourAtoi(args[0]);
    FLIGHTS_C catalog = get_flights_c(manager); 
    GHashTable* flights = get_hash_table_flight(catalog); 
    int i = 0;
    int initialCapacity = 500; 
    AirportInfo2* array = malloc(sizeof(AirportInfo2) * initialCapacity); 
    int delay;
    char** finalResult = malloc(sizeof(char*)*(N+1));
    
    // Iterate over catalog reservations
    GHashTableIter iter; 
    gpointer key, value; 
    g_hash_table_iter_init(&iter, flights);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        FLIGHT flight = (FLIGHT) value;

        char* airport = get_flight_origin(flight);
        char* scheduled_date = get_flight_schedule_departure_date(flight);
        char* real_date = get_flight_real_departure_date(flight);

        delay = calculate_flight_delay(scheduled_date, real_date);
        int airportPosition = findAirportPosition2(array, i, airport);
        
        if (airportPosition != -1){ 
            g_array_append_val(array[airportPosition].delays, delay);
            array[airportPosition].n_delays++;
            
        
            }
        else {
            if (i >= initialCapacity) {
                initialCapacity *= 2;
                array = realloc(array, sizeof(AirportInfo2) * initialCapacity);
                }
            array[i].delays = g_array_new(FALSE, FALSE, sizeof(int));;
            array[i].name = strdup(airport);
            g_array_append_val(array[i].delays, delay);
            i++;
            }
        
        free(airport);
        free(scheduled_date);
        free(real_date);
    } 
    
    for(int k = 0; k < i; k++) {
        g_array_sort(array[k].delays, compare_ints);
        guint length = array[k].delays->len;
        array[k].median = g_array_index(array[k].delays, int , (length/2));
    }

    qsort(array, i, sizeof(AirportInfo2), sort_airports2); 


    finalResult[0] = (i < N ? int_to_string(i) : int_to_string(N));
    for (int j = 1; j < i+1 && j<N+1; j++) {
        int total_size = snprintf(NULL, 0,"%s;%d", array[j-1].name,
        array[j-1].median) + 1;

        // Alocatte memory to a formatted string
        char* formatted_string = malloc(total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%d", array[j-1].name, array[j-1].median);

        finalResult[j] = formatted_string;
    } 

    for(int j = 0; j < i; j++){
        free(array[j].name);
        g_array_free(array[j].delays, TRUE);
    }

    free(array);

    return finalResult;
    
}

int compare_dates_timeless(char* itemA, char* itemB) {
    // Comparar anos
    int yearA, monthA, dayA;
    sscanf(itemA, "%d/%d/%d", &yearA, &monthA, &dayA);

    int yearB, monthB, dayB;
    sscanf(itemB, "%d/%d/%d", &yearB, &monthB, &dayB);

    if (yearA != yearB){
        return yearB - yearA;  // Sort by year in descending order
    }

    // Compare months
    if (monthA != monthB){
        return monthB - monthA;  // sort by month in descending order
    }

    // Compare days
    return dayB - dayA;  // Sort days by descending order

}


/*Apresentar a receita total de um hotel entre duas datas (inclusive), a partir do seu identificador.
As receitas de um hotel devem considerar apenas o preço por noite (price_per_night) de todas as
reservas com noites entre as duas datas. E.g., caso um hotel tenha apenas uma reserva de 100€/noite
de 2023/10/01 a 2023/10/10, e quisermos saber as receitas entre 2023/10/01 a 2023/10/02, deverá ser
retornado 200€ (duas noites). Por outro lado, caso a reserva seja entre 2023/10/01 a 2023/10/02,
deverá ser retornado 100€ (uma noite).*/

void* query8(MANAGER manager, char** args){
    char* hotel_id = strdup(args[0]);
    RESERV_C catalog = get_reserv_c(manager);
    int price, n_nights, result = 0;
    char* begin = strdup(args[1]);
    char* end = strdup(args[2]);
    
    GPtrArray* hotel_array = get_hotel_reserv_array_by_id(catalog, hotel_id);

    if (hotel_array != NULL){
        for (guint j = 0; j < hotel_array->len; j++) {
            n_nights = 0;
            char* reserv_id = g_ptr_array_index(hotel_array, j);
            RESERV reservation = get_reservations_by_id(catalog, reserv_id);
            char* begin_date = get_begin_date(reservation);
            char* end_date = get_end_date(reservation);
            price = get_price_per_night(reservation);
            
            if(compare_dates_timeless(end_date,begin) <= 0 && compare_dates_timeless(begin_date,end) >= 0) {
                n_nights = 0;
                char* test_begin = strdup((compare_dates_timeless(begin, begin_date) > 0) ? begin_date : begin);
                char* test_end = strdup((compare_dates_timeless(end, end_date) > 0) ? end : end_date);                
                if(strcmp(test_end, end)==0) {n_nights++;}
                n_nights += dates_timespan(test_begin, test_end);
                result+= (price * n_nights) ;
            }
            free(begin_date);
            free(end_date);
        }
        
    }
    free(begin);
    free(end);
    free(hotel_id);
    char* finalResult = int_to_string(result);

    return finalResult;
}


typedef struct {
    char* user;
    char* user_id;
} User_list;

int sort_users(const void* a, const void* b) {
    User_list* f_a = (User_list*)a;
    User_list* f_b = (User_list*)b;

    int result;

    result = strcmp(f_a->user, f_b->user);
    if(result == 0) {result = strcmp(f_a->user_id, f_b->user_id);}
    return result;
}



void* query9(MANAGER manager,char** args) {
    /*USERS_C catalog = get_users_c(manager);
    GHashTable* users= get_hash_table_users(catalog);
    GHashTableIter iter;
    gpointer key, value;
    char* prefix = args[0];
    int i = 0; 
    int initialCapacity = 500;
    
    User_list* user_list = malloc(sizeof(User_list) * initialCapacity);
    g_hash_table_iter_init(&iter, users);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        USER entity = (USER) value;
        char* user = get_user_name(entity);
        char* user_status = get_user_account_status(entity);
        if (strncmp(prefix, user, strlen(prefix)) == 0 && strcmp(user_status, "INACTIVE") != 0){
            char* user_id = get_user_id(entity);
            if (i >= initialCapacity) {
                    initialCapacity *= 2;
                    user_list = realloc(user_list, sizeof(User_list) * initialCapacity);
                }
            user_list[i].user = user;
            user_list[i].user_id = user_id;
            i++;
            free(user_id);            
        }
        free(user);
        free(user_status);
    }

    qsort(user_list, i, sizeof(User_list), sort_users);

    char** finalResult = malloc(sizeof(char*)*(i+1));
    finalResult[0] = int_to_string(i);
    for (int j = 1; j < i+1 && j<i+1; j++) {
        int total_size = snprintf(NULL, 0,"%s;%s", user_list[j-1].user_id,
        user_list[j-1].user) + 1;

        // Alocatte memory to a formatted string
        char* formatted_string = malloc(sizeof(char*)*total_size);

        // Create fromatted string
        snprintf(formatted_string, total_size, "%s;%s", user_list[j-1].user_id, user_list[j-1].user);

        finalResult[j] = formatted_string;
    }

    for(int j = 0; j < i; j++){
        free(user_list[j].user_id);
        free(user_list[j].user);
    }

    free(user_list);

    return finalResult;*/
    (void) manager;
    (void) args;
    return args;
}


void* query10(MANAGER catalog,char** args){
    (void) catalog;
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
    for (int i = 0; i < 8; i++) {
        if(resultF[i] != NULL) free(resultF[i]);
    }
    free(resultF);
}

void free_query2(void* result){
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    free(resultF[0]);
    for (int i = 2; i < n+2; i++) {
        free(resultF[i]);
    }
    free(resultF);
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
    for (int i = 0; i < n+1; i++) {
        free(resultF[i]);
    }
    free(resultF);
}

void free_query5(void* result){
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    for (int i = 0; i < n+1; i++) {
        free(resultF[i]);
    }
    free(resultF);
}

void free_query6(void* result){
    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    for (int i = 0; i < n+1; i++) {
        free(resultF[i]);
    }
    free(resultF);
}

void free_query7(void* result){
        if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    for (int i = 0; i < n+1; i++) {
        free(resultF[i]);
    }
    free(resultF);
}

void free_query8(void* result){
    if (result == NULL) {
    return;
    }
    char** resultF = (char**) result;
    free(resultF);
}

void free_query9(void* result) {
    /*    if (result == NULL) {
        return;
    }
    char** resultF = (char**) result;
    int n = ourAtoi(resultF[0]);
    for (int i = 0; i < n+1; i++) {
        free(resultF[i]);
    }
    free(resultF);*/
    (void) result;
}

void free_query10(void* result){
    (void) result;
}
