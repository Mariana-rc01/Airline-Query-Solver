/**
 * @file flights.h
 * @brief
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

#ifndef FLIGHTS_H
#define FLIGHTS_H

typedef struct flight *FLIGHT;

#include "menuNdata/statistics.h"

FLIGHT create_flight(void);

void build_flight(char  **flight_fields, void *catalog, STATS stats);

void set_flight_id(FLIGHT flight, char* id);

void set_flight_airline(FLIGHT flight, char* airline);

void set_flight_plane_model(FLIGHT flight, char* plane_model);

void set_flight_total_seats(FLIGHT flight, char* total_seats);

void set_flight_origin(FLIGHT flight, char* origin);

void set_flight_destination(FLIGHT flight, char* destination);

void set_flight_schedule_departure_date(FLIGHT flight, char* schedule_departure_date);

void set_flight_schedule_arrival_date(FLIGHT flight, char* schedule_arrival_date);

void set_flight_real_departure_date(FLIGHT flight, char* real_departure_date);

void set_flight_real_arrival_date(FLIGHT flight, char* real_arrival_date);

void set_flight_pilot(FLIGHT flight, char* pilot);

void set_flight_copilot(FLIGHT flight, char* copilot);

void set_flight_notes(FLIGHT flight, char* notes);


int get_flight_id(FLIGHT flight);

char* get_flight_airline(FLIGHT flight);

char* get_flight_plane_model(FLIGHT flight);

int get_flight_total_seats(FLIGHT flight);

char* get_flight_origin(FLIGHT flight);

char* get_flight_destination(FLIGHT flight);

char* get_flight_schedule_departure_date(FLIGHT flight);

char* get_flight_schedule_arrival_date(FLIGHT flight);

char* get_flight_real_departure_date(FLIGHT flight);

char* get_flight_real_arrival_date(FLIGHT flight);

char* get_flight_pilot(FLIGHT flight);

char* get_flight_copilot(FLIGHT flight);

char* get_flight_notes(FLIGHT flight);


void free_flight(FLIGHT flight);

int verify_flight(char** fields);

#endif
