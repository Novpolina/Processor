#include <stdio.h>        
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "assm.h"

int arr_with_code[200] ={};
int ip = 0;
int ERROR = 123432;

struct labels jumps[20] = {};
int ip_labels = 0;


bool is_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    while (isspace((unsigned char)*str)) {
        str++;
    }
    if (*str == '-') {
        str++;
    }
    bool has_digits = false;
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        has_digits = true;
        str++;
    }
    return has_digits;
}


int first_pass(FILE* file_with_code) {
    char cmd[50] = "";

    while(fscanf(file_with_code, "%99s", cmd) == 1){
        if(strcmp(cmd, "PUSH") == 0){

            fscanf(file_with_code, "%s", cmd);
            if (is_integer(cmd)){
                arr_with_code[ip] = 11;
                ip++;
                arr_with_code[ip] = strtol(cmd, NULL, 10);
                ip++;
            }
            else if(strcmp(cmd, "AX") == 0){
                arr_with_code[ip] = 12;
                ip++;
                arr_with_code[ip] = 1;
                ip++;
            }
            else if(strcmp(cmd, "BX") == 0){
                arr_with_code[ip] = 12;
                ip++;
                arr_with_code[ip] = 2;
                ip++;
            }
            else if(strcmp(cmd, "CX") == 0){
                arr_with_code[ip] = 12;
                ip++;
                arr_with_code[ip] = 3;
                ip++;
            }
            else if(strcmp(cmd, "DX") == 0){
                arr_with_code[ip] = 12;
                ip++;
                arr_with_code[ip] = 4;
                ip++;
            }
            else if(strcmp(cmd, "[") == 0){
                arr_with_code[ip] = 13;
                ip++;
                fscanf(file_with_code, "%s", cmd);
                arr_with_code[ip] = strtol(cmd, NULL, 10);
                ip++;
                fscanf(file_with_code, "%s", cmd);

                if(strcmp(cmd, "]") == 0){
                    return ERROR;
                }
            }
            else{
                return ERROR;
            }
            
        }
        else if(strcmp(cmd, "POP")){
            fscanf(file_with_code, "%s", cmd);
            if(strcmp(cmd, "AX") == 0){
                arr_with_code[ip] = 21;
                ip++;
                arr_with_code[ip] = 1;
                ip++;
            }
            else if(strcmp(cmd, "BX") == 0){
                arr_with_code[ip] = 21;
                ip++;
                arr_with_code[ip] = 2;
                ip++;
            }
            else if(strcmp(cmd, "CX") == 0){
                arr_with_code[ip] = 21;
                ip++;
                arr_with_code[ip] = 3;
                ip++;
            }
            else if(strcmp(cmd, "DX") == 0){
                arr_with_code[ip] = 21;
                ip++;
                arr_with_code[ip] = 4;
                ip++;
            }
            else if(strcmp(cmd, "[") == 0){
                arr_with_code[ip] = 22;
                ip++;
                fscanf(file_with_code, "%s", cmd);
                arr_with_code[ip] = strtol(cmd, NULL, 10);
                ip++;
                fscanf(file_with_code, "%s", cmd);

                if(strcmp(cmd, "]") == 0){
                    return ERROR;
                }
            }
            else{
                return ERROR;
            }
            
        }
        else if(strcmp(cmd, "ADD")){
            arr_with_code[ip] = 31;
            ip++;

        }
        //////////////////добавить хуйни
        else if(strcmp(cmd, "JA")){
            arr_with_code[ip] = 41;
            ip++;
            fscanf(file_with_code, "%s", cmd);
            strcpy(jumps[ip_labels].label, cmd);
            jumps[ip_labels].place_ip = ip;

        }
        else{
            

        }



    }





}