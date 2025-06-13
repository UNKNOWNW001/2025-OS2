//queue.cpp
#include "queue.h"
#include <cstdlib>
#include <cstring>
#include <mutex>

struct Queue { Node* head; Node* tail; std::mutex mtx; };

extern "C" {

    Queue* init(void) {
        Queue* q = new Queue(); q->head = q->tail = nullptr; return q;
    }

    void release(Queue* queue) {
        std::lock_guard<std::mutex> lock(queue->mtx);
        Node* cur = queue->head;
        while (cur) { Node* nxt = cur->next; free(cur->item.value); delete cur; cur = nxt; }
        delete queue;
    }

    Node* nalloc(Item item) {
        Node* node = new Node;
        node->item.key = item.key;
        node->item.value_size = item.value_size;
        node->item.value = malloc(item.value_size);
        memcpy(node->item.value, item.value, item.value_size);
        node->next = nullptr;
        return node;
    }

    void nfree(Node* node) { if (!node) return; free(node->item.value); delete node; }
    Node* nclone(Node* src) { return src ? nalloc(src->item) : nullptr; }

    Reply enqueue(Queue* queue, Item item) {
        std::lock_guard<std::mutex> lock(queue->mtx);
        // 중복 key 업데이트 또는 정렬 삽입
    }

    Reply dequeue(Queue* queue) {
        std::lock_guard<std::mutex> lock(queue->mtx);
        // head 제거 후 반환
    }

}