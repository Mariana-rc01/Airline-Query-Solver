/**
 * @file flights.c
 * @brief This file contains the implementation of the flight struct and related functions.
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

#include "entities/flights.h"
#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @struct flight
 * @brief Represents flight information.
 */
struct flight {
    char* id; /**< Unique flight ID. */
    char* airline; /**< Airline name. */
    char* plane_model; /**< Model of the plane. */
    int total_seats; /**< Total number of seats in the plane. */
    char* origin; /**< Flight origin airport. */
    char* destination; /**< Flight destination airport. */
    char* schedule_departure_date; /**< Scheduled departure date and time. */
    char* schedule_arrival_date; /**< Scheduled arrival date and time. */
    char* real_departure_date; /**< Real departure date and time. */
    char* real_arrival_date; /**< Real arrival date and time. */
    int nPassengers; /**< Number of passengers. */
};

FLIGHT create_flight(void){
    FLIGHT new = malloc(sizeof(struct flight));
    new->id = NULL;
    new->airline = NULL;
    new->plane_model = NULL;
    new->total_seats = 0;
    new->origin = NULL;
    new->destination = NULL;
    new->schedule_departure_date = NULL;
    new->schedule_arrival_date = NULL;
    new->real_departure_date = NULL;
    new->real_arrival_date = NULL;
    new->nPassengers = 0;

    return new;
}

void set_flight_id(FLIGHT flight, char* id){
    flight->id = strdup(id);
}

void set_flight_airline(FLIGHT flight, char* airline){
    flight->airline = strdup(airline);
}

void set_flight_plane_model(FLIGHT flight, char* plane_model){
    flight->plane_model = strdup(plane_model);
}

void set_flight_total_seats(FLIGHT flight, char* total_seats){
    flight->total_seats = ourAtoi(total_seats);
}

void set_flight_origin(FLIGHT flight, char* origin){
    flight->origin = strdup(origin);
}

void set_flight_destination(FLIGHT flight, char* destination){
    flight->destination = strdup(destination);
}

void set_flight_schedule_departure_date(FLIGHT flight, char* schedule_departure_date){
    flight->schedule_departure_date = strdup(schedule_departure_date);
}

void set_flight_schedule_arrival_date(FLIGHT flight, char* schedule_arrival_date){
    flight->schedule_arrival_date = strdup(schedule_arrival_date);
}

void set_flight_real_departure_date(FLIGHT flight, char* real_departure_date){
    flight->real_departure_date = strdup(real_departure_date);
}

void set_flight_real_arrival_date(FLIGHT flight, char* real_arrival_date){
    flight->real_arrival_date = strdup(real_arrival_date);
}

void set_flight_nPassengers(FLIGHT flight, int n){
    flight->nPassengers = n;
}

char* get_flight_id(FLIGHT flight){
    return strdup(flight->id);
}

char* get_flight_airline(FLIGHT flight){
    return strdup(flight->airline);
}

char* get_flight_plane_model(FLIGHT flight){
    return strdup(flight->plane_model);
}

int get_flight_total_seats(FLIGHT flight){
    return (flight->total_seats);
}

char* get_flight_origin(FLIGHT flight){
    return strdup(flight->origin);
}

char* get_flight_destination(FLIGHT flight){
    return strdup(flight->destination);
}

char* get_flight_schedule_departure_date(FLIGHT flight){
    return strdup(flight->schedule_departure_date);
}

char* get_flight_schedule_arrival_date(FLIGHT flight){
    return strdup(flight->schedule_arrival_date);
}

char* get_flight_real_departure_date(FLIGHT flight){
    return strdup(flight->real_departure_date);
}

char* get_flight_real_arrival_date(FLIGHT flight){
    return strdup(flight->real_arrival_date);
}

int get_flight_nPassengers(FLIGHT flight){
    return flight->nPassengers;
}

void free_flight(FLIGHT flight){
    free(flight->airline);
    free(flight->plane_model);
    free(flight->origin);
    free(flight->destination);
    free(flight->schedule_departure_date);
    free(flight->schedule_arrival_date);
    free(flight->real_departure_date);
    free(flight->real_arrival_date);

    free(flight);
}

int verify_flight(char** fields){
    if (!(fields[0]) || !(fields[1]) || !(fields[2]) ||
        !(fields[10]) || !(fields[11]) || !(fields[6]) || !(fields[7]) ||
        !(fields[8] || !(fields[9]))) return 0;

    if (!(validate_date_time(fields[6]))) return 0;
    if (!(validate_date_time(fields[7]))) return 0;
    if (!(validate_date_time(fields[8]))) return 0;
    if (!(validate_date_time(fields[9]))) return 0;

    if (!(compare_date_time(fields[6],fields[7]))) return 0;
    if (!(compare_date_time(fields[8],fields[9]))) return 0;

    if (!(validate_seats(fields[3]))) return 0;

    if (!(validate_airports(fields[4]))) return 0;
    if (!(validate_airports(fields[5]))) return 0;

    return 1;
}

int build_flight(char** flight_fields, void* catalog){

    FLIGHTS_C flightsC = (FLIGHTS_C) catalog;

    if (!verify_flight(flight_fields)) return 0;

    FLIGHT flight = create_flight();

    char* origin = case_insensitive(flight_fields[4]);
    char* destination = case_insensitive(flight_fields[5]);

    set_flight_id(flight,flight_fields[0]);
    set_flight_airline(flight,flight_fields[1]);
    set_flight_plane_model(flight,flight_fields[2]);
    set_flight_total_seats(flight,flight_fields[3]);
    set_flight_origin(flight,origin);
    set_flight_destination(flight,destination);
    set_flight_schedule_departure_date(flight,flight_fields[6]);
    set_flight_schedule_arrival_date(flight,flight_fields[7]);
    set_flight_real_departure_date(flight,flight_fields[8]);
    set_flight_real_arrival_date(flight,flight_fields[9]);

    insert_flight_c(flight,flightsC,flight->id);

    char year[6];
    char month[3];
    char day[3];
    sscanf(flight_fields[6], "%4[^/]/%2[^/]/%2[^/]", year, month, day);

    char* concatenated = concat(year, month);

    insert_flightNumber_c(flightsC, concatenated, day);

    return 1;
}

