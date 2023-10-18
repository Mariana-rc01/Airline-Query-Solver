/**
 * @file input.c
 * @brief Module that reads the input file and contains the file validations 
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

#include "IO/input.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/**
 * @brief Verifies if a character is a digit 
 * 
 * @param c Character to be verified
 * @return Bool
 */
int isDigit(char c){
    return(c >= '0' && c <= '9');
}

int isLetter(char c){
    return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * @brief This function casts any String to Int.
 * 
 * We can't just cast a String to number, we have to pay attention to units
 * E.g. Thousands, Hundreds, Tens, Ones...
 * For this, we need to raise 10 to the power of the length of the string minus 2
 * This is the Invanriant of this function
 * 
 * 
 * @param string Accepts any type of string
 * @return Cast from string to int
 */
int ourAtoi(char* string){
    int i, r;
    double n = pow(10.0,(double)(strlen(string)-2));
    for(i = 0; string[i] != '\0'; i++){
        r = (string[i] - '0') * (int) n;
        n /= 10;
    }

    return r;
}

// YYYY/MM/DD
int validate_date_timeless(char* date_string){

    // validate years
    if(!isDigit(date_string[0]) &&
       !isDigit(date_string[1]) &&
       !isDigit(date_string[2]) &&
       !isDigit(date_string[3])) return 0;

    // validate months
    int aux;
    if(isDigit(date_string[5]) && isDigit(date_string[6]))
        aux = (date_string[5] - '0') * 10 + (date_string[6] - '0');
    else return 0;

    if (aux > 12 || aux < 1) return 0;

    // validate days
    if(isDigit(date_string[8]) && isDigit(date_string[9]))
        aux = (date_string[8] - '0') * 10 + (date_string[9] - '0');
    else return 0;

    if (aux > 31 || aux < 1) return 0;
    
    return 1;
}

// YYYY/MM/DD hh:mm:ss
int validate_date_time(char* date_string){

    if(validate_date_timeless(date_string) == 0) return 0;
 
    // Validate hours
    int aux;
    if(isDigit(date_string[11]) && isDigit(date_string[12]))
        aux = (date_string[11] - '0') * 10 + (date_string[12] - '0');
    else return 0;

    if (aux > 23 || aux < 0) return 0;

    // Validate minutes
    if(isDigit(date_string[14]) && isDigit(date_string[15]))
        aux = (date_string[14] - '0') * 10 + (date_string[15] - '0');
    else return 0;

    if (aux > 59 || aux < 0) return 0;

    // Validate seconds
    if(isDigit(date_string[17]) && isDigit(date_string[18]))
        aux = (date_string[17] - '0') * 10 + (date_string[18] - '0');
    else return 0;

    if (aux > 59 || aux < 0) return 0;

    return 1;
}

int compare_date_timeless(char* date_string_start , char* date_string_end){
    
    int i;
    char* start = NULL; 
    char* end = NULL;
    for(i = 0; i < 4; i++){
        start[i] = date_string_start[i];
    }
    start[i] = '\0';

    for(i = 0; i < 4; i++){
        end[i] = date_string_end[i];
    }
    end[i] = '\0';

    int yearS = ourAtoi(start);
    int yearE = ourAtoi(end);

    if((yearS - yearE) > 0) return 0;
    else if(yearS - yearE == 0){

        for(i = 0; i < 2; i++){
            start[i] = date_string_start[i+5];
        }
        start[i] = '\0';
        
        for(i = 0; i < 2; i++){
            end[i] = date_string_end[i+5];
        }
        end[i] = '\0';

        int monthS = ourAtoi(start);
        int monthE = ourAtoi(end);

        if((monthS - monthE) > 0) return 0;
        else if((monthS - monthE) == 0){
            for(i = 0; i < 2; i++){
                start[i] = date_string_start[i+8];
            }
            start[i] = '\0';
            
            for(i = 0; i < 2; i++){
                end[i] = date_string_end[i+8];
            }
            end[i] = '\0';

            int dayS = ourAtoi(start);
            int dayE = ourAtoi(end);

            if((dayS - dayE) >= 0) return 0;
        }
    }
    return 1;
}

int compare_date_time(char* date_string_start, char* date_string_end){

    if (compare_date_timeless(date_string_start, date_string_end) == 0) return 0;

    int i;
    char* start = NULL; 
    char* end = NULL;
    for(i = 0; i < 2; i++){
        start[i] = date_string_start[i+11];
    }
    start[i] = '\0';

    for(i = 0; i < 2; i++){
        end[i] = date_string_end[i+11];
    }
    end[i] = '\0';

    int hourS = ourAtoi(start);
    int hourE = ourAtoi(end);

    if((hourS - hourE) > 0) return 0;
    else if(hourS - hourE == 0){

        for(i = 0; i < 2; i++){
            start[i] = date_string_start[i+14];
        }
        start[i] = '\0';
        
        for(i = 0; i < 2; i++){
            end[i] = date_string_end[i+14];
        }
        end[i] = '\0';

        int minuteS = ourAtoi(start);
        int minuteE = ourAtoi(end);

        if((minuteS - minuteE) > 0) return 0;
        else if((minuteS - minuteE) == 0){
            for(i = 0; i < 2; i++){
                start[i] = date_string_start[i+17];
            }
            start[i] = '\0';
            
            for(i = 0; i < 2; i++){
                end[i] = date_string_end[i+17];
            }
            end[i] = '\0';

            int secondS = ourAtoi(start);
            int secondE = ourAtoi(end);

            if((secondS - secondE) >= 0) return 0;
        }
    }
    return 1;
}

// “<username>@<domain>.<TLD>” 
int validate_email(char* email){    
    int i = 0;
    int email_length = strlen(email);

    // validates username (at least 1 char)
    while(email[i] != '@' || email[i] == '\0') i++;
    if(i < 1 || i == email_length) return 0;

    // validates domain (at least 1 char)
    int j = i;
    i++;
    while(email[i] != '.' || email[i] == '\0') i++;
    if((i - j) <= 1 || i == email_length) return 0;

    // validates TLD (at least 2 chars)
    // the position i marks the position of the '.'
    if(email_length - i <= 2) return 0;

    return 1;
}

int validate_country_code(char* code){
    if(strlen(code) != 3  ||
       !isLetter(code[0]) || 
       !isLetter(code[1])) return 0;

    return 1;
}

int validate_account_status(char* status){
    int i = 0;
    while(status[i] != '\0' && isLetter(status[i])){
        status[i] = toupper(status[i]);
        i++;
    }
    if(status[i] != '\0') return 0;
    if(strcmp(status,"ACTIVE") != 0 || strcmp(status,"INACTIVE") != 0) return 0;
    
    return 1;
}

int validate_total_seats(char* seats, char* passengers){
    return(ourAtoi(passengers) <= ourAtoi(seats));
}

int validate_airports(char* airport){
    if(strlen(airport) != 3) return 0;
    int i = 0;
    while(airport[i] != '\0' && isLetter(airport[i])){
        airport[i] = toupper(airport[i]);
        i++;
    } 

    if(airport[i] != '\0') return 0;

    return 1;
}

int validate_hotel_stars(char* stars){
    int i = 0;
    while(stars[i] != '.'  || stars[i] != '-' ||
          stars[i] != '\0' || !isDigit(stars[i])) i++;

    if (stars[i] != '\0' && (ourAtoi(stars) < 1 || ourAtoi(stars) > 5)) return 0;
    return 1;
}

int validate_city_tax(char* tax){
    int i = 0;
    while(tax[i] != '.'  || tax[i] != '-' ||
          tax[i] != '\0' || !isDigit(tax[i])) i++;

    if (tax[i] != '\0' && ourAtoi(tax) < 0) return 0;
    return 1;
}

int validate_price_per_night(char* price){
    int i = 0;
    while(price[i] != '.'  || price[i] != '-' ||
          price[i] != '\0' || !isDigit(price[i])) i++;

    if (price[i] != '\0' && ourAtoi(price) <= 0) return 0;
    return 1;
}

int validate_includes_breakfast(char* boolean){
    
    if(strlen(boolean) == 0) return 1;

    if(strlen(boolean) == 1 && 
       (boolean[0] == '1' || boolean[0] == '0' ||
        boolean[0] == 't' || boolean[0] == 'f')) return 1;


    int i = 0;
    while(boolean[i] != '\0' && isLetter(boolean[i])){
        boolean[i] = toupper(boolean[i]);
        i++;
    }
    if(boolean[i] != '\0') return 0;
    if(strcmp(boolean,"TRUE") != 0 || strcmp(boolean,"FALSE") != 0) return 0;
    
    return 1;
}

int validate_rating(char* rating){

    if(strlen(rating) == 0) return 1;

    return(validate_hotel_stars(rating));
}

int validate_existence(char* string){
    return(strlen(string));
}


