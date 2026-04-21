#include <iostream>
#include <fstream>
#include <string>

struct Node {
    char data;
    Node* next;
};

struct Queue {
    Node* head = nullptr;
    Node* tail = nullptr;
};

void enqueue(Queue& q, char value) {
    Node* newNode = new Node{value, nullptr};
    if (q.tail == nullptr) {
        q.head = q.tail = newNode;
    } else {
        q.tail->next = newNode;
        q.tail = newNode;
    }
}

char dequeue(Queue& q) {
    if (q.head == nullptr) return '\0';
    Node* temp = q.head;
    char val = temp->data;
    q.head = q.head->next;
    if (q.head == nullptr) q.tail = nullptr;
    delete temp;
    return val;
}

bool isEmpty(const Queue& q) {
    return q.head == nullptr;
}

void printQueue(Queue q, const std::string& message) {
    std::cout << message << ": ";
    Node* current = q.head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void createQueueFromFile(Queue& q, const std::string& filename) {
    std::ifstream file(filename);
    char ch;
    if (file.is_open()) {
        while (file.get(ch)) {
            if (ch != '\n' && ch != '\r') {
                enqueue(q, ch);
            }
        }
        file.close();
    } else {
        std::cerr << "Pomylka vidkryttya fajlu!" << std::endl;
    }
}

bool isEnglishLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void processAndSplitQueues(Queue& source, Queue& englishQ, Queue& othersQ) {
    while (!isEmpty(source)) {
        char val = dequeue(source);
        if (isEnglishLetter(val)) {
            enqueue(englishQ, val);
        } else {
            enqueue(othersQ, val);
        }
    }
}

void clearQueue(Queue& q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}

int main() {
    Queue mainQueue, englishQueue, othersQueue;

    createQueueFromFile(mainQueue, "input.txt");

    if (isEmpty(mainQueue)) {
        std::cout << "Pochatkova cherga porozhnya." << std::endl;
        return 0;
    }

    printQueue(mainQueue, "Pochatkova cherga");

    processAndSplitQueues(mainQueue, englishQueue, othersQueue);

    printQueue(englishQueue, "Cherga z anglijskymy literamy");
    printQueue(othersQueue, "Cherga z inshymy symvolamy");

    clearQueue(englishQueue);
    clearQueue(othersQueue);

    return 0;
}
