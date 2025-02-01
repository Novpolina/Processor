enum commands{
    PUSH,
    POP,
    ADD,
    SUB,
    DIV,
    JMP,
    JA
};

struct labels{
    int place_ip;
    char label[50];

};