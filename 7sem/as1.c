#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum reg_t { A = 0, B, C, D, RLAST };
enum opcode_t {
    MOVI = 0,
    ADD = 8,
    SUB = 9,
    MUL = 10,
    DIV = 11,
    IN = 48,
    OUT = 49,
    OPLAST
};
union operand_t {
    struct {
        int rd, rs;
    } ops;
    int rop;
    int imm;
};
struct instr_t {
    enum opcode_t opcode;
    union operand_t opnd;
};
struct reg_state_t {
    unsigned char data;
    unsigned char init;
};

int is_mov(char *str)
{
    return !(strcmp(str, "MOVI"));
}

enum opcode_t is_inout(char *str)
{
    if(!strcmp(str, "IN")) {
        return IN;
    }

    if(!strcmp(str, "OUT")) {
        return OUT;
    }

    return 0;
}

void check_arg(char a)
{
    if(a - 65 > 3){
        printf("ERROR\n");
        exit(0);
    }
}

unsigned get_num()
{
    int res;
    unsigned num;

    res = scanf("%u", &num);
    return num;
}

unsigned get_arg()
{
    char num;

    scanf(" %c", &num);
    check_arg(num);

    return num - 65;
}

enum opcode_t is_op(char *str)
{
    if(!strcmp(str, "ADD")) {
        return ADD;
    }
    if(!strcmp(str, "MUL")) {
        return MUL;
    }
    if(!strcmp(str, "SUB")) {
        return SUB;
    }
    if(!strcmp(str, "DIV")) {
        return DIV;
    }
    return 0;
}

unsigned get_arg_op()
{
    unsigned res;
    char arg1, arg2;

    scanf(" %c, %c", &arg1, &arg2);

    check_arg(arg1);
    check_arg(arg2);

    return ((arg1 - 65) * 4 + arg2 - 65);

}

unsigned to_hex(char *str)
{
    enum opcode_t Op;

    if(is_mov(str)) {

        return get_num();
    }

    if(Op = is_inout(str)) {

        return (get_arg() + Op * 4);
    }

    if(Op = is_op(str)) {

        return (get_arg_op() + Op * 16);

    }

    printf("ERROR\n");
    exit(0);
}

int main() {

    char *str;
    str = calloc(64, sizeof(char));
    for (; ; ) {
        int res;
        unsigned Data;
        res = scanf("%s", str);
        if (res != 1) {
            break;
        }

        Data = to_hex(str);

        printf("0x%x ", Data);
    }
}
