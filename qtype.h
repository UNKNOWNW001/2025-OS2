//qtype.h
#ifndef QTYPE_H
#define QTYPE_H

typedef int   Key;
typedef void* Value;
typedef struct { Key key; Value value; } Item;
typedef struct { bool success; Item item; } Reply;

typedef struct node_t {
    Item        item;
    struct node_t* next;
} Node;// ���� ���� ����Ʈ�� Node ���� �߰�
typedef struct Queue Queue;

#endif // QTYPE_H
