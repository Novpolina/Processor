
#include "assm.h"
#include "commands.h"


int ip = 0;
const int LABLS = 5;

struct labels jumps[LABLS] = {};
int ip_jumps = 0;


struct labels label[LABLS] = {};
int ip_label = 0;
int arr_with_code[200] ={};

void dump_jumps(FILE* dump_file);
void dump_labels(FILE* dump_file);


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


int pass(FILE* file_with_code) {
    char cmd[50] = "";
    for(int i = 0; i < LABLS; i++){
        jumps[i].place_ip = -1;
    }
    for(int i = 0; i < LABLS; i++){
        label[i].place_ip = -1;
    }
    for(int i = 0; i < 200; i++){
        arr_with_code[i] = -1;
    }

    while(fscanf(file_with_code, "%49s", cmd) == 1){
        if(strcmp(cmd, "PUSH") == 0){

            fscanf(file_with_code, "%s", cmd);
            if (is_integer(cmd)){
                arr_with_code[ip] = SPUSH;
                ip++;
                arr_with_code[ip] = strtol(cmd, NULL, 10);
                ip++;
            }
            else if(strcmp(cmd, "AX") == 0){
                arr_with_code[ip] = SPUSHR;
                ip++;
                arr_with_code[ip] = 1;
                ip++;
            }
            else if(strcmp(cmd, "BX") == 0){
                arr_with_code[ip] = SPUSHR;
                ip++;
                arr_with_code[ip] = 2;
                ip++;
            }
            else if(strcmp(cmd, "CX") == 0){
                arr_with_code[ip] = SPUSHR;
                ip++;
                arr_with_code[ip] = 3;
                ip++;
            }
            else if(strcmp(cmd, "DX") == 0){
                arr_with_code[ip] = SPUSHR;
                ip++;
                arr_with_code[ip] = 4;
                ip++;
            }
            else if(strcmp(cmd, "[") == 0){
                arr_with_code[ip] = SPUSHR;
                ip++;
                fscanf(file_with_code, "%s", cmd);
                arr_with_code[ip] = strtol(cmd, NULL, 10);
                ip++;
                fscanf(file_with_code, "%s", cmd);

                if(strcmp(cmd, "]")){
                    return ERROR;
                }
            }
            else{
                return ERROR;
            }
            
        }
        else if(strcmp(cmd, "POP") == 0){
            fscanf(file_with_code, "%s", cmd);
            if(strcmp(cmd, "AX") == 0){
                arr_with_code[ip] = SPOP;
                ip++;
                arr_with_code[ip] = 1;
                ip++;
            }
            else if(strcmp(cmd, "BX") == 0){
                arr_with_code[ip] = SPOP;
                ip++;
                arr_with_code[ip] = 2;
                ip++;
            }
            else if(strcmp(cmd, "CX") == 0){
                arr_with_code[ip] = SPOP;
                ip++;
                arr_with_code[ip] = 3;
                ip++;
            }
            else if(strcmp(cmd, "DX") == 0){
                arr_with_code[ip] = SPOP;
                ip++;
                arr_with_code[ip] = 4;
                ip++;
            }
            else if(strcmp(cmd, "[") == 0){
                arr_with_code[ip] = SPOPOP;
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
        else if(strcmp(cmd, "ADD") == 0){
            arr_with_code[ip] = SADD;
            ip++;

        }
        //////////////////добавить хуйни
        else if(strcmp(cmd, "JA") == 0){
            arr_with_code[ip] = SJA;
            ip++;
            fscanf(file_with_code, "%s", cmd);
            //printf ("\n %s \n", cmd);
            strcpy(jumps[ip_jumps].label, cmd);
            jumps[ip_jumps].place_ip = ip;
            ip_jumps++;
            ip++;

        }
        else{
            strcpy(label[ip_label].label, cmd);
            label[ip_label].place_ip = ip;
            ip_label++;
        }

    }

    ip_jumps--;

    for(;ip_jumps >= 0; ip_jumps -- ){

        for(int i = 0; i < ip_label; i++){
            if(strcmp(jumps[ip_jumps].label, label[i].label) == 0){
                arr_with_code[jumps[ip_jumps].place_ip] = label[i].place_ip;
            }
        }
        if(jumps[ip_jumps].place_ip == -1){
            return ERROR;
        }
    }
    return NOERROR;

}
void MakeFileWithCode(FILE* file){
    for(int i = 0; i < 200 && arr_with_code[i] != -1; i++){
        fprintf(file, "%i ", arr_with_code[i]);
    }

}

void dump(FILE* dump_file){
    fprintf(dump_file, "\n------------------Массив кода-----------------------\n");
    for(int i = 0; i < 200 /*&& arr_with_code[i] != -1*/; i++){
        fprintf(dump_file, "%i ", arr_with_code[i]);
    }
    fprintf(dump_file, "\n");

}
void dump_labels(FILE* dump_file){
    fprintf(dump_file, "\n------------------------Метки-----------------------\n");
    for( int i = 0; i < LABLS; i++){
        fprintf(dump_file, "Метка %s  на месте %i.\n",  label[i].label, label[i].place_ip);
    }
    fprintf(dump_file, "\n");
}
void dump_jumps(FILE* dump_file){
    fprintf(dump_file, "\n--------------------------JUMP------------------------\n");
    for( int i = 0; i < LABLS ; i++){
        fprintf(dump_file, "JUMP на метку %s  на месте %i. \n",  jumps[i].label, jumps[i].place_ip);
    }
    fprintf(dump_file, "\n");
}

void asm_dump(FILE* dump_file){
    dump_jumps(dump_file);
    dump_labels(dump_file);
    dump(dump_file);
}
