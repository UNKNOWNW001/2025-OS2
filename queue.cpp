//queue.cpp
#include "queue.h"
#include <cstdlib>
#include <cstring>

struct Queue { Node* head; Node* tail; };

extern "C" {

    Queue* init(void) {
        Queue* q = new Queue();
        q->head = q->tail = nullptr;
        return q;
    }

    void release(Queue* queue) {
        delete queue;
    }

    Reply enqueue(Queue* queue, Item item) {
        Node* prev = nullptr;
        Node* cur = queue->head;
        while (cur && cur->item.key < item.key) {
            prev = cur;
            cur = cur->next;
        }
        Node* node = new Node{ item, cur };
        if (prev) prev->next = node;
        else queue->head = node;
        if (!cur) queue->tail = node;
        return { true, item };
    }

    Reply dequeue(Queue* queue) {
        if (!queue->head) return { false, {0, nullptr, 0} };
        Node* node = queue->head;
        queue->head = node->next;
        if (!queue->head) queue->tail = nullptr;
        Reply r = { true, node->item };
        delete node;
        return r;
    }

}