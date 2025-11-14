// main.cpp
#include <iostream>
#include <string>
#include "mydeque.h"

void testBasicOperations() {
    std::cout << "=== TEST 1: Podstawowe operacje ===" << std::endl;
    MyDeque<int> deque(3); // Tablica 4-elementowa, max 3 elementy
    
    std::cout << "Pusta: " << deque.empty() << ", Pelna: " << deque.full() << std::endl;
    std::cout << "Rozmiar: " << deque.size() << "/" << deque.max_size() << std::endl;
    
    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(0);
    
    std::cout << "Po dodaniu 0(front), 1(back), 2(back): ";
    deque.display();
    std::cout << "Pusta: " << deque.empty() << ", Pelna: " << deque.full() << std::endl;
    std::cout << "Rozmiar: " << deque.size() << "/" << deque.max_size() << std::endl;
    std::cout << "Front: " << deque.front() << ", Back: " << deque.back() << std::endl;
    
    std::cout << std::endl;
}

void testPushPopOperations() {
    std::cout << "=== TEST 2: Operacje push/pop ===" << std::endl;
    MyDeque<int> deque(4); // max 4 elementy
    
    // Test push_back
    for(int i = 1; i <= 3; i++) {
        deque.push_back(i * 10);
    }
    std::cout << "Po push_back 10,20,30: ";
    deque.display();
    
    // Test push_front - tylko 1 element bo już mamy 3
    deque.push_front(5);
    std::cout << "Po push_front 5: ";
    deque.display();
    
    // Test pop_front
    deque.pop_front();
    std::cout << "Po pop_front: ";
    deque.display();
    
    // Test pop_back
    deque.pop_back();
    std::cout << "Po pop_back: ";
    deque.display();
    
    // Teraz możemy dodać kolejny element
    deque.push_front(1);
    std::cout << "Po push_front 1: ";
    deque.display();
    
    std::cout << std::endl;
}

void testCyclicBehavior() {
    std::cout << "=== TEST 3: Zachowanie cykliczne ===" << std::endl;
    MyDeque<int> deque(3); // max 3 elementy
    
    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(0); // [0,1,2] - pełna
    
    std::cout << "Poczatkowa: ";
    deque.display();
    
    deque.pop_front(); // [1,2]
    deque.push_back(3); // [1,2,3]
    
    std::cout << "Po pop_front i push_back(3): ";
    deque.display();
    
    deque.pop_front(); // [2,3]
    deque.push_back(4); // [2,3,4]
    
    std::cout << "Po pop_front i push_back(4): ";
    deque.display();
    
    std::cout << std::endl;
}

void testIndexOperations() {
    std::cout << "=== TEST 4: Operacje indeksowania ===" << std::endl;
    MyDeque<int> deque(5); // max 5 elementów
    
    for(int i = 0; i < 5; i++) {
        deque.push_back(i * 10);
    }
    std::cout << "Poczatkowa: ";
    deque.display();
    
    // Test operator[]
    std::cout << "deque[0]: " << deque[0] << std::endl;
    std::cout << "deque[2]: " << deque[2] << std::endl;
    std::cout << "deque[4]: " << deque[4] << std::endl;
    
    // Modyfikacja przez indeks
    deque[1] = 999;
    deque[3] = 777;
    std::cout << "Po modyfikacji deque[1]=999, deque[3]=777: ";
    deque.display();
    
    // Test index()
    std::cout << "Index 999: " << deque.index(999) << std::endl;
    std::cout << "Index 30: " << deque.index(30) << std::endl;
    std::cout << "Index 1000: " << deque.index(1000) << std::endl;
    
    std::cout << std::endl;
}

void testInsertErase() {
    std::cout << "=== TEST 5: Insert i erase ===" << std::endl;
    MyDeque<int> deque(6); // max 6 elementów
    
    // Dodajemy tylko 4 elementy, żeby mieć miejsce na insert
    deque.push_back(10);
    deque.push_back(20);
    deque.push_back(30);
    deque.push_back(40);
    std::cout << "Poczatkowa: ";
    deque.display();
    
    // Insert na początek
    deque.insert(0, 5);
    std::cout << "Po insert(0, 5): ";
    deque.display();
    
    // Insert na koniec
    deque.insert(deque.size(), 50);
    std::cout << "Po insert(size, 50): ";
    deque.display();
    
    // Insert w środku - już nie możemy bo pełna
    std::cout << "Proba insert w srodku (pelna kolejka): ";
    if (!deque.full()) {
        deque.insert(2, 15);
        deque.display();
    } else {
        std::cout << "Kolejka pelna, nie mozna wstawic" << std::endl;
    }
    
    // Erase z początku
    deque.erase(0);
    std::cout << "Po erase(0): ";
    deque.display();
    
    // Erase z końca
    deque.erase(deque.size()-1);
    std::cout << "Po erase(size-1): ";
    deque.display();
    
    // Erase ze środka
    deque.erase(2);
    std::cout << "Po erase(2): ";
    deque.display();
    
    std::cout << std::endl;
}

void testCopyMoveSemantics() {
    std::cout << "=== TEST 6: Semantyka kopiowania i przenoszenia ===" << std::endl;
    
    // Test konstruktora kopiującego
    MyDeque<int> original(3);
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    
    MyDeque<int> copy = original;
    std::cout << "Original: ";
    original.display();
    std::cout << "Kopia: ";
    copy.display();
    
    // Modyfikacja kopii nie wpływa na original
    copy[0] = 999;
    std::cout << "Po modyfikacji kopii: " << std::endl;
    std::cout << "Original: ";
    original.display();
    std::cout << "Kopia: ";
    copy.display();
    
    // Test operatora przypisania
    MyDeque<int> assigned(2);
    assigned = original;
    std::cout << "Po przypisaniu: ";
    assigned.display();
    
    std::cout << std::endl;
}

void testClearAndDisplay() {
    std::cout << "=== TEST 7: Clear i display_reversed ===" << std::endl;
    MyDeque<int> deque(4); // max 4 elementy
    
    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(0);
    deque.push_back(3);
    
    std::cout << "Przed clear: ";
    deque.display();
    std::cout << "Odwrocone: ";
    deque.display_reversed();
    
    deque.clear();
    std::cout << "Po clear - pusta: " << deque.empty() << std::endl;
    
    // Ponowne dodanie
    deque.push_back(100);
    deque.push_back(200);
    std::cout << "Po ponownym dodaniu: ";
    deque.display();
    
    std::cout << std::endl;
}


int main() {
    std::cout << "=== TESTS FOR MYDEQUE IMPLEMENTATION ===" << std::endl << std::endl;
    
    testBasicOperations();
    testPushPopOperations();
    testCyclicBehavior();
    testIndexOperations();
    testInsertErase();
    testCopyMoveSemantics();
    testClearAndDisplay();
    
    std::cout << "=== ALL TESTS COMPLETED ===" << std::endl;
    
    return 0;
}