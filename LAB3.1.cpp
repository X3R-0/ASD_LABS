#include <iostream>
#include <functional>
#include <cassert>

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
};

template <typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;
};

template <typename T>
struct FindNodeResult {
    Node<T>* prev;
    Node<T>* current;
};

template <typename T>
Node<T>* insertAfter(LinkedList<T>* list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>{ value };

    if (node == nullptr) {
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == nullptr) {
            list->tail = newNode;
        }
    } else {
        newNode->next = node->next;
        node->next = newNode;
        if (list->tail == node) {
            list->tail = newNode;
        }
    }

    ++list->size;
    return newNode;
}

template <typename T, typename Comparator = std::equal_to<T>>
FindNodeResult<T> find(LinkedList<T>* list, const T& value, Comparator comp = Comparator{}) {
    Node<T>* prev = nullptr;
    Node<T>* curr = list->head;

    while (curr != nullptr) {
        if (comp(curr->value, value)) {
            return { prev, curr };
        }
        prev = curr;
        curr = curr->next;
    }

    return { nullptr, nullptr };
}

template <typename T>
void removeAfter(LinkedList<T>* list, Node<T>* node) {
    Node<T>* toDelete = nullptr;

    if (node == nullptr) {
        toDelete = list->head;
        if (toDelete != nullptr) {
            list->head = toDelete->next;
            if (list->tail == toDelete) {
                list->tail = nullptr;
            }
        }
    } else {
        toDelete = node->next;
        if (toDelete != nullptr) {
            node->next = toDelete->next;
            if (list->tail == toDelete) {
                list->tail = node;
            }
        }
    }

    if (toDelete) {
        delete toDelete;
        --list->size;
    }
}

template <typename T>
void assertNoCycles(LinkedList<T>* list) {
    Node<T>* current = list->head;
    size_t steps = 0;

    while (current != nullptr && steps <= list->size) {
        current = current->next;
        ++steps;
    }

    assert(steps <= list->size && "Cycle detected in linked list!");
}

int main() {
    LinkedList<int> list;

    Node<int>* a = insertAfter<int>(&list, nullptr, 10);
    Node<int>* b = insertAfter(&list, a, 20);
    insertAfter(&list, b, 30);

    assertNoCycles(&list);

    auto result = find(&list, 20);
    if (result.current) {
        std::cout << "Found: " << result.current->value << "\n";
    }

    removeAfter<int>(&list, nullptr);
    assertNoCycles(&list);

    for (Node<int>* curr = list.head; curr != nullptr; curr = curr->next) {
        std::cout << curr->value << " ";
    }
    std::cout << "\n";

    while (list.head) {
        removeAfter<int>(&list, nullptr);
    }

    return 0;
}