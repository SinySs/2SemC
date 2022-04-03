#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

const int start_size = 32;

struct buffer {

    char *text;

    int len;
    int max_len;
    int num_of_token;

};

enum lexem_kind_t{
    OP,
    BRACE,
    NUM
};

enum operation_t{
    ADD,
    SUB,
    MUL,
    DIV
};

enum braces_t{
    LBRAC,
    RBRAC
};


struct lexem_t {
    enum lexem_kind_t kind;
    union {
        enum operation_t op;
        enum braces_t b;
        int num;
    } lex;
};

struct lex_array_t {

    struct lexem_t *lexems;
    int size, capacity;

};

void change_size(struct buffer *buf, int new_size)
{

    char *new_text;
    new_text = realloc(buf->text, new_size);
    assert(new_text != NULL);

    buf->text = new_text;
    buf->max_len = new_size;
}

int read_in_buf(struct buffer *buf)
{
    char a;

    buf->len = 0;
    buf->num_of_token = 0;
    buf->max_len = start_size;
    buf->text = calloc(start_size, sizeof(char));


    a = getchar();

    while(a != EOF) {

        if(!isspace(a)) {

            buf->text[buf->len] = a;
            buf->len++;
            buf->num_of_token++;
        }

        a = getchar();


        if(isdigit(a) && isdigit(buf->text[buf->len - 1])) {
            buf->num_of_token--;
        }

        if(buf->len - 5 < buf->max_len) {
            change_size(buf, buf->max_len * 2);
        }
    }

    //buf->text[buf->len] = '\0';

}

struct lex_array_t lex_init(int num_of_lex)
{
   struct lex_array_t new_arr;

   new_arr.lexems = calloc(num_of_lex, sizeof(struct lexem_t));
   new_arr.capacity = num_of_lex;
   new_arr.size = 0;

   return new_arr;
}

int string_to_arr(struct lex_array_t *lex, const char *str, int len)
{
   int i, num_of_lex;

   int new_num;
   num_of_lex = 0;
   i = 0;

   while(i < len) {

        if(isdigit(str[i])) {

            lex->lexems[num_of_lex].kind = NUM;
            new_num = atoi(&str[i]);
            lex->lexems[num_of_lex].lex.num = new_num;
            num_of_lex++;

            while(isdigit(str[i])) {
                i++;
            }
        }

        switch(str[i]) {

        case('+'):
            lex->lexems[num_of_lex].kind = OP;
            lex->lexems[num_of_lex].lex.op = ADD;
            num_of_lex++;
            break;

        case('-'):
            lex->lexems[num_of_lex].kind = OP;
            lex->lexems[num_of_lex].lex.op = SUB;
            num_of_lex++;
            break;

        case('*'):
            lex->lexems[num_of_lex].kind = OP;
            lex->lexems[num_of_lex].lex.op = MUL;
            num_of_lex++;
            break;

        case('/'):
            lex->lexems[num_of_lex].kind = OP;
            lex->lexems[num_of_lex].lex.op = DIV;
            num_of_lex++;
            break;

        case('('):
            lex->lexems[num_of_lex].kind = BRACE;
            lex->lexems[num_of_lex].lex.op = LBRAC;
            num_of_lex++;
            break;

        case(')'):
            lex->lexems[num_of_lex].kind = BRACE;
            lex->lexems[num_of_lex].lex.op = RBRAC;
            num_of_lex++;
            break;

        default:

            return -1;
            break;

        }

        i++;
   }


   return 0;
}

void print_lex(struct lex_array_t lex)
{
    int i;

    for(i = 0; i < lex.capacity; i++) {

        switch(lex.lexems[i].kind) {

        case(NUM):
            printf("NUMBER:%d ", lex.lexems[i].lex.num);
            break;

        case(OP):
            switch(lex.lexems[i].lex.op) {

            case(ADD):
                printf("PLUS ");
                break;

            case(SUB):
                printf("MINUS ");
                break;

            case(MUL):
                printf("MUL ");
                break;

            case(DIV):
                printf("DIV ");
                break;

            }
            break;

        case(BRACE):
            switch(lex.lexems[i].lex.b) {

            case(LBRAC):
                printf("LBRAC ");
                break;

            case(RBRAC):
                printf("RBRAC ");
                break;
            break;
            }

        }
    }
}

int main()
{
    struct buffer Buf;
    struct lex_array_t Lexems;
    int status;


    read_in_buf(&Buf);

    /*for(int i = 0; i < Buf.len; i++) {
        printf("%c", Buf.text[i]);
    }*/

    Lexems = lex_init(Buf.num_of_token);
    status = string_to_arr(&Lexems, Buf.text, Buf.len);

    print_lex(Lexems);


    /*for(int i = 0; i < Lexems.capacity; i++) {
        if(Lexems.lexems[i].kind == NUM) {
            printf("%d ", Lexems.lexems[i].lex.num);
        } else if(Lexems.lexems[i].kind == OP) {
            printf("op ");
        } else if(Lexems.lexems[i].kind == BRACE) {
            printf("br ");
        }
    }*/

    free(Buf.text);

    return 0;
}
