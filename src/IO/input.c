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

/**
 * @brief Verifies if a character is a digit 
 * 
 * @param c Character to be verified
 * @return Bool
 */
int isDigit(char c){
    return(c >= '0' && c <= '9');
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





