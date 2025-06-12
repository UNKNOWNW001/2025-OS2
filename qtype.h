//qtype.h
#ifndef QTYPE_H
#define QTYPE_H

#include <stdbool.h>
#include <stddef.h>

typedef int   Key;
typedef void* Value;

typedef struct {
    Key       key;
    Value     value;
    size_t    value_size;
} Item;

typedef struct {
    bool    success;
    Item    item;
} Reply;

typedef struct node_t {
    Item            item;
    struct node_t* next;
} Node;

typedef struct Queue Queue;

#endif // QTYPE_H