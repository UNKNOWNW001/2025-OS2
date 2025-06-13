#include "queue.h"
#include <cstdlib>
#include <cstring>
#include <mutex>

struct Queue {
    Node* head;
    Node* tail;
    std::mutex mtx;
};

extern "C" {

    Queue* init(void) {
        Queue* q = new Queue();
        q->head = nullptr;
        q->tail = nullptr;
        return q;
    }

    void release(Queue* queue) {
        if (!queue) return;

        {
            std::lock_guard<std::mutex> lock(queue->mtx);
            Node* cur = queue->head;
            while (cur) {
                Node* next = cur->next;
                free(cur->item.value);
                delete cur;
                cur = next;
            }
        }

        delete queue;
    }

    Node* nalloc(Item item) {
        Node* node = new Node;
        node->item.key = item.key;
        node->item.value = malloc(item.value_size);
        node->item.value_size = item.value_size;
        memcpy(node->item.value, item.value, item.value_size);
        node->next = nullptr;
        return node;
    }

    void nfree(Node* node) {
        if (!node) return;
        free(node->item.value);
        delete node;
    }

    Node* nclone(Node* src) {
        if (!src) return nullptr;
        return nalloc(src->item);
    }

    Reply enqueue(Queue* queue, Item item) {
        Reply r = { false, {0, nullptr, 0} };
        if (!queue) return r;
        std::lock_guard<std::mutex> lock(queue->mtx);
        Node* prev = nullptr;
        Node* cur = queue->head;
        while (cur) {
            if (cur->item.key == item.key) {
                free(cur->item.value);
                cur->item.value = malloc(item.value_size);
                cur->item.value_size = item.value_size;
                memcpy(cur->item.value, item.value, item.value_size);
                r.success = true;
                return r;
            }
            if (cur->item.key > item.key) break;
            prev = cur;
            cur = cur->next;
        }
        Node* node = new Node;
        node->item.key = item.key;
        node->item.value = malloc(item.value_size);
        node->item.value_size = item.value_size;
        memcpy(node->item.value, item.value, item.value_size);
        node->next = cur;
        if (prev) prev->next = node;
        else queue->head = node;
        if (!cur) queue->tail = node;
        r.success = true;
        return r;
    }

    Reply dequeue(Queue* queue) {
        Reply r = { false, {0, nullptr, 0} };
        if (!queue) return r;
        std::lock_guard<std::mutex> lock(queue->mtx);
        if (!queue->head) return r;
        Node* node = queue->head;
        queue->head = node->next;
        if (!queue->head) queue->tail = nullptr;
        r.success = true;
        r.item.key = node->item.key;
        r.item.value = node->item.value;
        r.item.value_size = node->item.value_size;
        delete node;
        return r;
    }

    Queue* range(Queue* queue, Key start, Key end) {
        if (!queue) return nullptr;
        Queue* result = init();
        std::lock_guard<std::mutex> lock(queue->mtx);
        Node* cur = queue->head;
        while (cur) {
            if (cur->item.key >= start && cur->item.key <= end) {
                Node* node = new Node;
                node->item.key = cur->item.key;
                node->item.value_size = cur->item.value_size;
                node->item.value = malloc(cur->item.value_size);
                memcpy(node->item.value, cur->item.value, cur->item.value_size);
                node->next = nullptr;
                if (!result->head) result->head = result->tail = node;
                else { result->tail->next = node; result->tail = node; }
            }
            cur = cur->next;
        }
        return result;
    }

}