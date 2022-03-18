#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>

const int start_size = 10;

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

    while(a != EOF && a != '\n') {
    //while(a != '\n') {

        buf->text[buf->len] = a;
        buf->len++;
        buf->num_of_token++;

        a = getchar();

        if(isdigit(a) && isdigit(buf->text[buf->len - 1])) {
            buf->num_of_token--;
        }

        if(buf->len - 5 < buf->max_len) {
            change_size(buf, buf->max_len * 2);
        }
    }

    buf->text[buf->len] = '\0';
    change_size(buf, buf->len);

}

struct lex_array_t lex_init(int num_of_lex)
{
   struct lex_array_t new_arr;

   new_arr.lexems = calloc(num_of_lex, sizeof(struct lexem_t));
   new_arr.capacity = num_of_lex;
   new_arr.size = 0;

   return new_arr;
}

int main()
{
    struct buffer Buf;
    struct lex_array_t Lexems;


    read_in_buf(&Buf);
    for(int i = 0; i < Buf.len; i++) {
        printf("%c", Buf.text[i]);
    }

    Lexems = lex_init(Buf.num_of_token);

    free(Buf.text);

    return 0;
}
