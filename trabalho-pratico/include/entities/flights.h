/**
 * @file flights.h
 * @brief This file contains the definition of the flight struct and related functions.
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

/**
 * @typedef FLIGHT
 * @brief Typedef for struct flight pointer.
 */
typedef struct flight *FLIGHT;

#include "IO/input.h"
#include "utils/utils.h"
#include <glib.h>

/**
 * @brief Creates a new flight struct with default values.
 * @return A pointer to the new created flight.
 */
FLIGHT create_flight(void);

/**
 * @brief Sets the flight ID.
 * @param flight A pointer to the flight struct.
 * @param id The flight ID.
 */
void set_flight_id(FLIGHT flight, char* id);

/**
 * @brief Sets the airline for the flight.
 * @param flight A pointer to the flight struct.
 * @param airline The airline name.
 */
void set_flight_airline(FLIGHT flight, char* airline);

/**
 * @brief Sets the plane model for the flight.
 * @param flight A pointer to the flight struct.
 * @param plane_model The plane model.
 */
void set_flight_plane_model(FLIGHT flight, char* plane_model);

/**
 * @brief Sets the total number of seats for the flight.
 * @param flight A pointer to the flight struct.
 * @param total_seats The total number of seats.
 */
void set_flight_total_seats(FLIGHT flight, char* total_seats);

/**
 * @brief Sets the origin airport for the flight.
 * @param flight A pointer to the flight struct.
 * @param origin The flight origin airport.
 */
void set_flight_origin(FLIGHT flight, char* origin);

/**
 * @brief Sets the destination airport for the flight.
 * @param flight A pointer to the flight struct.
 * @param destination The flight destination airport.
 */
void set_flight_destination(FLIGHT flight, char* destination);

/**
 * @brief Sets the scheduled departure date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @param schedule_departure_date The scheduled departure date and time.
 */
void set_flight_schedule_departure_date(FLIGHT flight, char* schedule_departure_date);

/**
 * @brief Sets the scheduled arrival date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @param schedule_arrival_date The scheduled arrival date and time.
 */
void set_flight_schedule_arrival_date(FLIGHT flight, char* schedule_arrival_date);

/**
 * @brief Sets the real departure date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @param real_departure_date The real departure date and time.
 */
void set_flight_real_departure_date(FLIGHT flight, char* real_departure_date);

/**
 * @brief Sets the real arrival date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @param real_arrival_date The real arrival date and time.
 */
void set_flight_real_arrival_date(FLIGHT flight, char* real_arrival_date);

/**
 * @brief Sets the number of passengers of the flight.
 * @param flight A pointer to the flight struct.
 * @param n Number of passengers.
 */
void set_flight_nPassengers(FLIGHT flight, int n);

/**
 * @brief Gets the flight ID.
 * @param flight A pointer to the flight struct.
 * @return The flight ID.
 */
char* get_flight_id(FLIGHT flight);

/**
 * @brief Gets the airline for the flight.
 * @param flight A pointer to the flight struct.
 * @return The airline name.
 */
char* get_flight_airline(FLIGHT flight);

/**
 * @brief Gets the plane model for the flight.
 * @param flight A pointer to the flight struct.
 * @return The plane model.
 */
char* get_flight_plane_model(FLIGHT flight);

/**
 * @brief Gets the total number of seats for the flight.
 * @param flight A pointer to the flight struct.
 * @return The total number of seats.
 */
int get_flight_total_seats(FLIGHT flight);

/**
 * @brief Gets the flight origin airport.
 * @param flight A pointer to the flight struct.
 * @return The flight origin airport.
 */
char* get_flight_origin(FLIGHT flight);

/**
 * @brief Gets the flight destination airport.
 * @param flight A pointer to the flight struct.
 * @return The flight destination airport.
 */
char* get_flight_destination(FLIGHT flight);

/**
 * @brief Gets the scheduled departure date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @return The scheduled departure date and time.
 */
char* get_flight_schedule_departure_date(FLIGHT flight);

/**
 * @brief Gets the scheduled arrival date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @return The scheduled arrival date and time.
 */
char* get_flight_schedule_arrival_date(FLIGHT flight);

/**
 * @brief Gets the real departure date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @return The real departure date and time.
 */
char* get_flight_real_departure_date(FLIGHT flight);

/**
 * @brief Gets the real arrival date and time for the flight.
 * @param flight A pointer to the flight struct.
 * @return The real arrival date and time.
 */
char* get_flight_real_arrival_date(FLIGHT flight);

/**
 * @brief Gets the number of passengers of the flight.
 * @param flight A pointer to the flight struct.
 * @param n Number of passengers.
 */
int get_flight_nPassengers(FLIGHT flight);

/**
 * @brief Frees memory associated with a flight struct.
 * @param flight A pointer to the flight struct.
 */
void free_flight(FLIGHT flight);

/**
 * @brief Verifies the validity of flight data.
 * @param fields An array of flight data fields.
 * @return 1 if the flight data is valid, 0 otherwise.
 */
int verify_flight(char** fields);

/**
 * @brief Builds a flight struct from flight data fields.
 * @param flight_fields An array of flight data fields.
 * @param catalog A pointer to the flight catalog.
 * @param stats A pointer to the statistics.
 *
 * @return 1 if the flight is added to the catalog 0 if not
 */
int build_flight(char **flight_fields, void *catalog);

#endif
