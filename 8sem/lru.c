#include <stdio.h>
#include <malloc.h>
#include <assert.h>

struct hash_table_t
{
    struct node_t* data;
    int size;
    int capacity;
};

struct node_t {

    struct node_t* next;
    int data;

};

struct node_t *create_node(int data)
{
    struct node_t* new_node;
    new_node = (struct node_t*)calloc(1, sizeof(struct node_t));
    new_node->data = data;
    return new_node;
}

struct hash_table_t initialize_table(int capacity)
{
    struct hash_table_t new_table;
    new_table.capacity = capacity;
    new_table.data = calloc(capacity, sizeof(struct node_t));
    new_table.size = 0;

    return new_table;
}

int get_hash(int data, int M)
{
    return data % M;
}

int check_in_hash(int data, int M, struct hash_table_t table)
{
    int hash;
    hash = get_hash(data, M);

    if(table.data[hash].data != 0)
        return 1;

    return 0;
}

int is_optimize(int data, int M, struct hash_table_t *table)
{
    int flag;

    flag = check_in_hash(data, M, *table);

    if(flag)
        return 1;


    //fill_hash_table();

    return 0;
}

int main()
{
    int cells_num, calls_num, res;
    int i, data;
    int result;
    struct hash_table_t table;
    struct node_t head, tail;

    res = scanf("%d %d", &cells_num, &calls_num);
    assert(res == 2);

    table = initialize_table(cells_num);

    for(i = 0; i < calls_num; i++) {
        res = scanf("%d", &data);
        assert(res == 1);

        result += is_optimize(data, cells_num, &table);

    }

}
