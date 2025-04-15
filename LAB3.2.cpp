#include <iostream>
#include <cassert>
#include <functional>

template<typename T>
struct Node {
    T value;
    Node* prev = nullptr;
    Node* next = nullptr;
};

template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;
};

template<typename T>
Node<T>* insertAfter(LinkedList<T>* list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>{ value };

    if (node == nullptr) {
        newNode->next = list->head;
        if (list->head) list->head->prev = newNode;
        list->head = newNode;
        if (list->tail == nullptr) list->tail = newNode;
    } else {
        newNode->next = node->next;
        newNode->prev = node;
        if (node->next) node->next->prev = newNode;
        node->next = newNode;
        if (list->tail == node) list->tail = newNode;
    }

    ++list->size;
    return newNode;
}

template<typename T>
Node<T>* insertBefore(LinkedList<T>* list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>{ value };

    if (node == nullptr) {
        newNode->prev = list->tail;
        if (list->tail) list->tail->next = newNode;
        list->tail = newNode;
        if (list->head == nullptr) list->head = newNode;
    } else {
        newNode->prev = node->prev;
        newNode->next = node;
        if (node->prev) node->prev->next = newNode;
        node->prev = newNode;
        if (list->head == node) list->head = newNode;
    }

    ++list->size;
    return newNode;
}

template<typename T, typename Comparator = std::equal_to<T>>
Node<T>* find(LinkedList<T>* list, const T& value, Comparator comp = Comparator{}) {
    Node<T>* curr = list->head;
    while (curr) {
        if (comp(curr->value, value)) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
void remove(LinkedList<T>* list, Node<T>* node) {
    if (!node) return;

    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;

    delete node;
    --list->size;
}

template<typename T>
void assertNoCycles(LinkedList<T>* list) {
    Node<T>* forward = list->head;
    Node<T>* backward = list->tail;

    size_t fCount = 0, bCount = 0;

    while (forward && fCount <= list->size) {
        forward = forward->next;
        ++fCount;
    }
    while (backward && bCount <= list->size) {
        backward = backward->prev;
        ++bCount;
    }

    assert(fCount <= list->size && "Cycle detected in next links");
    assert(bCount <= list->size && "Cycle detected in prev links");
}

int main() {
    LinkedList<int> list;

    Node<int>* a = insertAfter<int>(&list, nullptr, 10); 
    Node<int>* b = insertAfter(&list, a, 20);           
    insertBefore(&list, b, 15);                          

    assertNoCycles(&list);

    std::cout << "Forward: ";
    for (Node<int>* n = list.head; n != nullptr; n = n->next) {
        std::cout << n->value << " ";
    }
    std::cout << "\n";

    std::cout << "Backward: ";
    for (Node<int>* n = list.tail; n != nullptr; n = n->prev) {
        std::cout << n->value << " ";
    }
    std::cout << "\n";

    Node<int>* found = find(&list, 15);
    if (found) std::cout << "Found: " << found->value << "\n";

    remove(&list, found);

    assertNoCycles(&list);

    std::cout << "After deletion: ";
    for (Node<int>* n = list.head; n != nullptr; n = n->next) {
        std::cout << n->value << " ";
    }
    std::cout << "\n";

    while (list.head) {
        remove(&list, list.head);
    }

    return 0;
}