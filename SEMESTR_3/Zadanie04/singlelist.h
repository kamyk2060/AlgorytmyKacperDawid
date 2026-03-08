// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
public:
    SingleList() : head(nullptr), tail(nullptr) {}
    ~SingleList(); // tu trzeba wyczyscic wezly

    SingleList(const SingleList& other); // copy constructor
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));

    SingleList& operator=(const SingleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    SingleList& operator=(SingleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    std::size_t size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1), L.push_front(item)
    void push_front(T&& item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1), L.push_back(item)
    void push_back(T&& item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void reverse(); // O(n) NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T>
SingleList<T>::SingleList(const SingleList& other) : head(nullptr), tail(nullptr) {
    SingleNode<T> *current = other.head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <typename T>
SingleList<T>::SingleList(SingleList&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList& other) {
    if (this != &other) {
        clear();
        SingleNode<T> *current = other.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
SingleList<T>& SingleList<T>::operator=(SingleList&& other) {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template <typename T>
std::size_t SingleList<T>::size() const {
    std::size_t count = 0;
    SingleNode<T> *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new SingleNode<T>(std::move(item), head);
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(std::move(item));
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

template <typename T>
void SingleList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void SingleList<T>::reverse() {
    if (empty() || head == tail) return;
    
    SingleNode<T> *prev = nullptr;
    SingleNode<T> *current = head;
    SingleNode<T> *next = nullptr;
    tail = head;
    
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
T& SingleList<T>::operator[](std::size_t pos) {
    assert(pos < size());
    SingleNode<T> *current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
const T& SingleList<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    SingleNode<T> *current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void SingleList<T>::erase(std::size_t pos) {
    assert(pos < size());
    if (pos == 0) {
        pop_front();
    } else {
        SingleNode<T> *current = head;
        for (std::size_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        SingleNode<T> *nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        if (nodeToDelete == tail) {
            tail = current;
        }
        delete nodeToDelete;
    }
}

template <typename T>
int SingleList<T>::index(const T& item) {
    SingleNode<T> *current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->value == item) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
void SingleList<T>::insert(std::size_t pos, const T& item) {
    assert(pos <= size());
    if (pos == 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        SingleNode<T> *current = head;
        for (std::size_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        current->next = new SingleNode<T>(item, current->next);
    }
}

template <typename T>
void SingleList<T>::insert(std::size_t pos, T&& item) {
    assert(pos <= size());
    if (pos == 0) {
        push_front(std::move(item));
    } else if (pos == size()) {
        push_back(std::move(item));
    } else {
        SingleNode<T> *current = head;
        for (std::size_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        current->next = new SingleNode<T>(std::move(item), current->next);
    }
}

#endif