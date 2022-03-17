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

} ;

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

    //while(a != EOF || a != '\n') {
    while(a != '\n') {

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


}

int main()
{
    struct buffer Buf;

    read_in_buf(&Buf);
    for(int i = 0; i < Buf.len; i++) {
        printf("%c", Buf.text[i]);
    }

    free(Buf.text);

    return 0;
}
