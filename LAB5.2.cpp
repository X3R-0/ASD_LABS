#include <iostream>
#include <cassert>

struct Node {
    int value;
    Node* next = nullptr;
};

struct Queue {
    Node* front = nullptr;
    Node* rear = nullptr;
    size_t size = 0;
};

bool isEmpty(const Queue* queue) {
    return queue->front == nullptr;
}

void enqueue(Queue* queue, int value) {
    Node* newNode = new Node{ value };
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

int* front(Queue* queue) {
    if (isEmpty(queue)) return nullptr;
    return &queue->front->value;
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) return;

    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    delete temp;
    queue->size--;
}

int main() {
    Queue queue;

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    std::cout << "Front of queue: " << *front(&queue) << "\n";

    dequeue(&queue);
    std::cout << "Front of queue after dequeue: " << *front(&queue) << "\n";

    dequeue(&queue);
    dequeue(&queue);
    std::cout << "Is the queue empty? " << (isEmpty(&queue) ? "Yes" : "No") << "\n";

    return 0;
}