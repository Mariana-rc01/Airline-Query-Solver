/**
 * @file utils.c
 * @brief Module that connects all the entities
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

int isDigit(char c){
    return(c >= '0' && c <= '9');
}

int isLetter(char c){
    return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ourAtoi(char* string){
    int i, r = 0;
    double n = pow(10.0,(double)(strlen(string)-2));
    for(i = 0; string[i] != '\0'; i++){
        r = (string[i] - '0') * (int) n;
        n /= 10;
    }

    return r;
}