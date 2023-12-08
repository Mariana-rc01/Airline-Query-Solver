/**
 * @file passengers.c
 * @brief This file contains the implementation of the passengers struct and related functions.
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

#include "entities/passengers.h"

#include "catalogs/manager_c.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

int verify_passengers(char** passengers_fields, USERS_C users, FLIGHTS_C flights){
    if (!(passengers_fields[0])) return 0;
    if (!(passengers_fields[1])) return 0;
    if (!(get_flight_by_id(flights, passengers_fields[0]))) return 0;
    if (!(get_user_by_id(users, passengers_fields[1]))) return 0;
    return 1;
}

int build_passengers(char** passengers_fields, void* catalog){

    MANAGER managerC = (MANAGER) catalog;
    USERS_C usersC = get_users_c(managerC);
    FLIGHTS_C flightsC = get_flights_c(managerC);
    PASS_C passengersC = get_pass_c(managerC);

    if (!verify_passengers(passengers_fields, usersC, flightsC)) return 0;

    char* copy_flight = strdup(passengers_fields[0]);
    char* copy_user = strdup(passengers_fields[1]);

    /*FLIGHT flight = get_flight_by_id(flightsC, copy_flight);

    // Check if the number of passengers exceeds the total number of seats
    GPtrArray* passengersArray = get_flight_array_by_id(passengersC, copy_flight);
    if (passengersArray && (int)passengersArray->len > get_flight_total_seats(flight)) {
        FILE* errorP = fopen("Resultados/passengers_errors.csv", "a");
        if (errorP != NULL) {
            for (int i = 0; i < (int)passengersArray->len; i++) {
                fprintf(errorP, "%s;%p\n", copy_flight, g_ptr_array_index(passengersArray, i));
            }
            fclose(errorP);
        }

        FILE* errorF = fopen("Resultados/flights_errors.csv", "a");
        if (errorF != NULL) {
            char* id = copy_flight;
            char* airline = get_flight_airline(flight);
            char* plane_model = get_flight_plane_model(flight);
            int total_seats = get_flight_total_seats(flight);
            char* origin = get_flight_origin(flight);
            char* destination = get_flight_destination(flight);
            char* schedule_d_d = get_flight_schedule_departure_date(flight);
            char* schedule_a_d = get_flight_schedule_arrival_date(flight);
            char* real_d_d = get_flight_real_departure_date(flight);
            char* real_a_d = get_flight_real_arrival_date(flight);
            char* pilot = get_flight_pilot(flight);
            char* copilot = get_flight_copilot(flight);
            char* notes = get_flight_notes(flight);

            fprintf(errorF, "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", id, airline,plane_model,total_seats,
            origin,destination,schedule_d_d, schedule_a_d, real_d_d, real_a_d, pilot, copilot, notes);
            fclose(errorF);
        }

        // Remove the flight from the hash table
        remove_flight_from_hash_table(flightsC, copy_flight);
        remove_flight_array_from_hash_table(passengersC, copy_flight);

        return 0;
    }*/

    //insert_pass_flight_c(copy_user, passengersC, strdup(passengers_fields[0]));
    insert_pass_user_c(copy_flight,passengersC, copy_user);

    return 1;
}

