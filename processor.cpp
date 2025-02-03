#include "assm.h"
#include "commands.h"
#include "stack.h"

struct SPU{
    int ip;
    stack stack_code;
    int* code;
    int* reg;
    int* rm;
    
};

SPU SPU_Init(){
    SPU SPU = {};

    int code[200] = {-1};
    int reg[5] = {-1};
    int rm[100] = {-1};


    SPU.code = code;
    SPU.ip = 0;
    SPU.reg = reg;
    SPU.rm = rm;
    

}


void read_numbers_from_file(FILE* code, int *numbers, int *count) {

    *count = 0; // Инициализируем счетчик чисел
    while (*count < MAX_NUMBERS && fscanf(code, "%i", &numbers[*count]) == 1) {
        (*count)++; // Увеличиваем счетчик после успешного считывания числа
    }

}

int processor(FILE* file_code) {
    stack stack_code = {};
    StackInit(&stack_code, 200);
    
    int code[MAX_NUMBERS] = {}; 
    for(int i = 0; i < 200; i++){
        code[i] = -1;
    }
    int count = 0; 
    read_numbers_from_file(file_code, code, &count);
    // char cmd[50] = {};
    // for (int i = 0; i < 200 && fscanf(file_code, "%49s", cmd) == 1; i++){
    //     code[i] = strtol(cmd, NULL, 10);


    // }
    // for(int i = 0; i < 200; i++){
    //     printf("%i ", code[i]);

    // }
    // printf("sdfghjk");

    for(int ip = 0; ip < 200 && code[ip] != -1; ip++){
        printf("%i", code[ip]);
        switch (code[ip]){
            case SPUSH:
                ip++;
                printf("fghjk");
                StackPush(&stack_code, code[ip]);
            default:
                break;


        }


    }
    STACK_DUMP(&stack_code, VSE_ZAYEBIS);
    StackDestroy(&stack_code);

    return 0;
}

