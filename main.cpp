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
#include "processor.h"

int main(){
    FILE* code = fopen("code.txt", "r");
    FILE* dump = fopen("dump.txt", "w");
    FILE* asm_code = fopen("asm.txt", "w+");
    pass(code);
    asm_dump(dump);
    MakeFileWithCode(asm_code);
    fclose(asm_code);
    fclose(code);
    fclose(dump);
    FILE* cod = fopen("asm.txt", "r");
    processor(cod);
    

}