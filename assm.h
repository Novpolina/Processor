#include <stdio.h>        
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>



struct labels{
    int place_ip;
    char label[50];

};
enum{
    ERROR,
    NOERROR
};
int pass(FILE* file_with_code);
void asm_dump(FILE* dump_file);
void MakeFileWithCode(FILE* file);