#include <iostream>
#include <vector>
#include <cassert>

struct StackArray {
    std::vector<int> data;

    bool isEmpty() const {
        return data.empty();
    }

    void push(int value) {
        data.push_back(value);
    }

    int* getLastElement() {
        if (isEmpty()) return nullptr;
        return &data.back();
    }

    void pop() {
        if (!isEmpty()) {
            data.pop_back();
        }
    }
};

struct Node {
    int value;
    Node* next = nullptr;
};

struct StackLinkedList {
    Node* top = nullptr;

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node{ value, top };
        top = newNode;
    }

    int* getLastElement() {
        if (isEmpty()) return nullptr;
        return &top->value;
    }

    void pop() {
        if (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {

    StackArray stackArray;
    stackArray.push(10);
    stackArray.push(20);
    stackArray.push(30);

    std::cout << "StackArray top element: " << *stackArray.getLastElement() << "\n";
    stackArray.pop();
    std::cout << "StackArray top after pop: " << *stackArray.getLastElement() << "\n";


    StackLinkedList stackLinkedList;
    stackLinkedList.push(100);
    stackLinkedList.push(200);
    stackLinkedList.push(300);

    std::cout << "StackLinkedList top element: " << *stackLinkedList.getLastElement() << "\n";
    stackLinkedList.pop();
    std::cout << "StackLinkedList top after pop: " << *stackLinkedList.getLastElement() << "\n";

    return 0;
}