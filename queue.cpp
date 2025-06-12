//queue.cpp
#include "queue.h"
#include <cstdlib>

struct Queue { Node* head; Node* tail; /* mutex 나중에 추가 */ };

extern "C" {

    Queue* init(void) {
        Queue* q = new Queue();
        q->head = q->tail = nullptr;
        return q;
    }

    void release(Queue* queue) {
        delete queue;
    }

}