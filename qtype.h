// qtype.h (v1)
#ifndef QTYPE_H
#define QTYPE_H

typedef int   Key;
typedef void* Value;
typedef struct { Key key; Value value; } Item;
typedef struct { bool success; Item item; } Reply;
typedef struct Node node_t;  // stub
typedef struct Queue Queue;  // stub

#endif // QTYPE_H
