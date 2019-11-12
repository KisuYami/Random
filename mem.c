#include <stdio.h>
#include <string.h>

#define get_offset(x) ((void *)x + sizeof(block_t) - (void *)memory.buf)

#define MEMORY_BUFF 116

struct memory
{
    char buf[MEMORY_BUFF];

    size_t size;
    size_t offset;

} memory;

struct block_metadata
{
    char free;
    short int size;

    struct block_metadata *next;
};

typedef struct block_metadata block_t;

void *v_print(char *name, char *data)
{
    block_t *f = (void *)data - sizeof(block_t);

    printf("%s: %s, \tsize: %d, \toffset: %d\n",
           name, data, f->size,
           data - memory.buf);
}

char *
print_bin(int n, char buf[8])
{
    if(n < 0) return "0000000";

    int i = 0;

    while (n) {
        if(i > 8)  break;
        if (n & 1) buf[i++] = '1';
        else       buf[i++] = '0';

        n >>= 1;
    }
    buf[i] = '\0';

    return buf;
}

void v_dump()
{
    char buf[8];

    printf("--------------------Memory-Dump-----------------\n");
    printf("|   Address    |    Bin     |   Int  |   Char  |\n");
    printf("------------------------------------------------\n");

    for(int i = 0; i <= MEMORY_BUFF; i++)
        printf("|  0x%08x  |  %08s  |  %4d  |    %01c    |\n", i,
               print_bin(memory.buf[i], buf),
               memory.buf[i], (memory.buf[i] > 'A') ? memory.buf[i] : ' ');

    printf("------------------------End---------------------\n");
}

void *v_free(void *ptr)
{
    block_t *first_meta = ptr - sizeof(block_t);
    first_meta->free = 0; // Freed
}

void *v_malloc(size_t size)
{
    if(memory.offset + size + sizeof(block_t) > memory.size)
    {
        block_t *p = (void *)memory.buf;
        block_t *avalable[10];

        int i = 0;
        size_t total_free = 0;

        for(;p != NULL; p = p->next)
        {
            block_t *old_p;

            if(p->free == 0 && p->size >= size)
            {
                block_t *ptr_p = p;
                int can_free = 1;

                for (; p != NULL; p = p->next)
                {
                    if(p->free != 0)
                        can_free == 0;
                }

                if(can_free == 1)
                {
                    memory.offset = get_offset(ptr_p);

                    block_t new_meta = {
                        .free = 1,
                        .size = size,
                        .next = NULL,
                    };

                    old_p->next = NULL;
                    break;
                }

                ptr_p->free = 1;
                return &memory.buf[get_offset(ptr_p)];
            }

            if(p->free == 0)
            {
                avalable[i++] = p;
                total_free += p->size + sizeof(block_t);

                if(total_free >= size)
                {
                    if(p->next == NULL)
						memory.offset = get_offset(p) + p->size;

                    avalable[0]->size = size;
                    avalable[0]->free = 1;

                    return &memory.buf[get_offset(avalable[0])];
                }
            }

            old_p = p;
        }
    }

    block_t new_meta = {
        .free = 1,
        .size = size,
        .next = NULL,
    };

    block_t *p = (void *)memory.buf;

    if(memory.offset > 0)
    {
        for(;p->next != NULL; p = p->next);

        p->next = (void *)memory.buf + memory.offset;
    }

    memcpy(memory.buf + memory.offset, &new_meta, sizeof(block_t));
    memory.offset += size + sizeof(block_t);


    return &memory.buf[memory.offset - size];
}

/*
  DONE:
  - offset changing
  - memory allocating
  - free blocks finder

  TODO:
  - 

*/

int main(void)
{
    memory = (struct memory) {
        .size = MEMORY_BUFF,
        .offset = 0,
    };

    char *test_a = v_malloc(11);
    char *test_b = v_malloc(12);
    char *test_c = v_malloc(11);

    strncpy(test_a, "first test", 11);
    strncpy(test_b, "second test", 12);
    strncpy(test_c, "third test", 11);

    block_t *f = (void *)test_a - sizeof(block_t);

    v_print("test_a", test_a);
    v_print("test_b", test_b);
    v_print("test_c", test_c);

    v_free(test_a);
    v_free(test_b);
    v_free(test_c);

    char *test_d = v_malloc(25);
    char *test_e = v_malloc(9);
    char *test_f = v_malloc(10);

    strncpy(test_d, "New memory, bigger stuff", 25);
    strncpy(test_e, "not smol", 9);
    strncpy(test_f, "big stuff", 10);

    v_print("test_d", test_d);
    v_print("test_e", test_e);
    v_print("test_e", test_f);

    v_dump();

    return 0;
}
