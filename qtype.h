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
} Node;// 내부 연결 리스트용 Node 선언 추가
typedef struct Queue Queue;

#endif // QTYPE_H
