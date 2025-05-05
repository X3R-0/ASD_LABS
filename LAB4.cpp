#include <iostream>
using namespace std;

class StackArray {
private:
    int* data;
    int index;
    int size;

public:
    StackArray(int size) {
        this->size = size;
        data = new int[size];
        index = -1;
    }

    ~StackArray() {
        delete[] data;
    }

    bool Empty() {
        return index < 0;
    }

    void Add(int val) {
        if (index >= size - 1) {
            cout << "Stack overflow" << endl;
            return;
        }
        data[++index] = val;
    }

    int Peek() {
        return Empty() ? -1 : data[index];
    }

    void Remove() {
        if (Empty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        index--;
    }

    void Show() {
        for (int i = index; i >= 0; i--)
            cout << data[i] << " ";
        cout << endl;
    }
};

struct NodeStack {
    int data;
    NodeStack* next;

    NodeStack(int data) : data(data), next(nullptr) {}
};

class StackLinked {
private:
    NodeStack* head = nullptr;

public:
    ~StackLinked() {
        while (!Empty()) Remove();
    }

    bool Empty() {
        return head == nullptr;
    }

    void Add(int val) {
        NodeStack* node = new NodeStack(val);
        node->next = head;
        head = node;
    }

    int Peek() {
        return head ? head->data : -1;
    }

    void Remove() {
        if (Empty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        NodeStack* temp = head;
        head = head->next;
        delete temp;
    }

    void Show() {
        NodeStack* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

struct NodeQueue {
    int data;
    NodeQueue* next;

    NodeQueue(int data) : data(data), next(nullptr) {}
};

class QueueLinked {
private:
    NodeQueue* start = nullptr;
    NodeQueue* end = nullptr;

public:
    ~QueueLinked() {
        while (!Empty()) Extract();
    }

    bool Empty() {
        return start == nullptr;
    }

    void Insert(int val) {
        NodeQueue* node = new NodeQueue(val);
        if (Empty()) {
            start = end = node;
        } else {
            end->next = node;
            end = node;
        }
    }

    int First() {
        return start ? start->data : -1;
    }

    void Extract() {
        if (Empty()) {
            cout << "Queue underflow" << endl;
            return;
        }
        NodeQueue* temp = start;
        start = start->next;
        if (!start)
            end = nullptr;
        delete temp;
    }

    void Display() {
        NodeQueue* current = start;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    cout << "StackArray" << endl;
    StackArray stackA(5);
    stackA.Add(11);
    stackA.Add(22);
    stackA.Add(33);
    cout << "Top " << stackA.Peek() << endl;
    stackA.Show();
    stackA.Remove();
    cout << "After pop" << endl;
    stackA.Show();

    cout << "StackLinked" << endl;
    StackLinked stackL;
    stackL.Add(111);
    stackL.Add(222);
    stackL.Add(333);
    cout << "Top " << stackL.Peek() << endl;
    stackL.Show();
    stackL.Remove();
    cout << "After pop" << endl;
    stackL.Show();

    cout << "QueueLinked" << endl;
    QueueLinked queueL;
    queueL.Insert(1);
    queueL.Insert(2);
    queueL.Insert(3);
    cout << "Front " << queueL.First() << endl;
    queueL.Display();
    queueL.Extract();
    cout << "After de-queue" << endl;
    queueL.Display();

    return 0;
}