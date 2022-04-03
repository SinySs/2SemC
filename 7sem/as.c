#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
enum reg_t { A = 0, B, C, D, RLAST };
enum opcode_t {
    MOVI = 0,
    ADD = 8,
    SUB = 9,
    MUL = 10,
    DIV = 11,
    IN,
    OUT,
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

int is_movi(unsigned Data) {
    return !((Data >> 7) & 0x1);
}

unsigned get_imm(unsigned Data) {
    return Data & ((1 << 8) - 1);
}

enum reg_t decode_arg0(unsigned Data) {
    return Data & 0x3;
}

enum reg_t decode_arg1(unsigned Data) {
    return decode_arg0(Data >> 2);
}

enum opcode_t arith_opcode(unsigned Data) {
    return Data >> 4;
}

unsigned is_inout(unsigned Data) {
    if (is_movi(Data))
        return 0;
    return (Data >> 6) & 0x1;
}

const char *get_reg_s(unsigned Reg) {
    switch (Reg) {
    case A:
        return "A";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    }
    fprintf(stderr, "Unknown reg: %x\n", Reg);
    exit(0);
}

const char *get_arith_s(enum opcode_t Opc) {
    switch (Opc) {
    case ADD:
        return "ADD";
    case SUB:
        return "SUB";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case IN:
        return "IN";
    case OUT:
        return "OUT";
    }
    fprintf(stderr, "ERROR\n");
    exit(0);
}

enum opcode_t get_inout(unsigned Data) {
    unsigned Opc = (Data >> 2) & 0xF;
    switch (Opc) {
    case (0):
        return IN;
    case (1):
        return OUT;
    }
    fprintf(stderr, "ERROR\n");
    exit(0);
}

int decode_inout(unsigned Data, char *Mnemonic) {
    enum opcode_t Opc = get_inout(Data);
    enum reg_t Arg0 = decode_arg0(Data);
    sprintf(Mnemonic, "%s %s", get_arith_s(Opc), get_reg_s(Arg0));
    return 0;
}

int decode_arith(unsigned Data, char *Mnemonic) {
    enum opcode_t Aop = arith_opcode(Data);
    enum reg_t Arg0 = decode_arg0(Data);
    enum reg_t Arg1 = decode_arg1(Data);
    sprintf(Mnemonic, "%s %s, %s", get_arith_s(Aop), get_reg_s(Arg1),
          get_reg_s(Arg0));
    return 0;
}

int decode(unsigned Data, char *Mnemonic) {
    if (is_movi(Data)) {
        sprintf(Mnemonic, "%s %d", "MOVI", get_imm(Data));
        return 0;
    }
    if (is_inout(Data)) {
        return decode_inout(Data, Mnemonic);
    }
    return decode_arith(Data, Mnemonic);
}

int main() {
    for (; ; ) {
        int res;
        unsigned Data;
        char Mnemonic[64] = {0};
        res = scanf("%x", &Data);
        if (res != 1) {
            break;
        }
        res = decode(Data, Mnemonic);
        printf("%s\n", Mnemonic);
    }
}
