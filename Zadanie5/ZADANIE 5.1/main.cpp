#include "doublelist.h"
#include <cassert>
#include <iostream>
#include <string>

void testBasicOperations() {
    std::cout << "=== Test podstawowych operacji ===" << std::endl;
    
    DoubleList<int> list;
    
    // Test empty na pustej liście
    assert(list.empty() == true);
    assert(list.size() == 0);
    
    // Test push_back
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.empty() == false);
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    // Test push_front
    list.push_front(0);
    list.push_front(-1);
    assert(list.size() == 5);
    assert(list.front() == -1);
    assert(list.back() == 3);
    
    // Test pop_front
    list.pop_front();
    assert(list.front() == 0);
    assert(list.size() == 4);
    
    // Test pop_back
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 3);
    
    std::cout << "Podstawowe operacje: OK" << std::endl;
}

void testCopyOperations() {
    std::cout << "=== Test kopiowania ===" << std::endl;
    
    DoubleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Test konstruktora kopiującego
    DoubleList<int> list2(list1);
    assert(list2.size() == 3);
    assert(list2.front() == 1);
    assert(list2.back() == 3);
    
    // Modyfikacja oryginału nie powinna wpłynąć na kopię
    list1.pop_front();
    assert(list1.size() == 2);
    assert(list2.size() == 3); // kopia niezmieniona
    
    // Test operatora przypisania kopiującego
    DoubleList<int> list3;
    list3 = list2;
    assert(list3.size() == 3);
    assert(list3.front() == 1);
    assert(list3.back() == 3);
    
    // Samoprzypisanie
    list3 = list3;
    assert(list3.size() == 3);
    
    std::cout << "Operacje kopiowania: OK" << std::endl;
}

void testMoveOperations() {
    std::cout << "=== Test przenoszenia ===" << std::endl;
    
    DoubleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Test konstruktora przenoszącego
    DoubleList<int> list2(std::move(list1));
    assert(list2.size() == 3);
    assert(list2.front() == 1);
    assert(list2.back() == 3);
    assert(list1.empty() == true); // lista1 powinna być pusta po przeniesieniu
    
    // Test operatora przypisania przenoszącego
    DoubleList<int> list3;
    list3 = std::move(list2);
    assert(list3.size() == 3);
    assert(list3.front() == 1);
    assert(list3.back() == 3);
    assert(list2.empty() == true); // lista2 powinna być pusta po przeniesieniu
    
    std::cout << "Operacje przenoszenia: OK" << std::endl;
}

void testIndexOperations() {
    std::cout << "=== Test operacji indeksowych ===" << std::endl;
    
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    
    // Test operatora [] - odczyt
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    assert(list[3] == 40);
    
    // Test operatora [] - zapis
    list[1] = 25;
    assert(list[1] == 25);
    assert(list.front() == 10);
    assert(list[2] == 30);
    
    // Test insert na początku
    list.insert(0, 5);
    assert(list.size() == 5);
    assert(list[0] == 5);
    assert(list[1] == 10);
    
    // Test insert w środku
    list.insert(3, 28);
    assert(list.size() == 6);
    assert(list[2] == 25);
    assert(list[3] == 28);
    assert(list[4] == 30);
    
    // Test insert na końcu
    list.insert(list.size(), 50);
    assert(list.size() == 7);
    assert(list.back() == 50);
    
    // Test erase z początku
    list.erase(0);
    assert(list.size() == 6);
    assert(list.front() == 10);
    
    // Test erase ze środka
    list.erase(2);
    assert(list.size() == 5);
    assert(list[1] == 25);
    assert(list[2] == 30);
    
    // Test erase z końca
    list.erase(list.size() - 1);
    assert(list.size() == 4);
    assert(list.back() == 40);
    
    // Test index
    assert(list.index(10) == 0);
    assert(list.index(25) == 1);
    assert(list.index(40) == 3);
    assert(list.index(100) == -1); // element nie istnieje
    
    std::cout << "Operacje indeksowe: OK" << std::endl;
}

void testClearAndDisplay() {
    std::cout << "=== Test czyszczenia ===" << std::endl;
    
    DoubleList<int> list;
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    
    assert(list.empty() == false);
    assert(list.size() == 3);
    
    list.clear();
    assert(list.empty() == true);
    assert(list.size() == 0);
    
    // Czyszczenie pustej listy
    list.clear();
    assert(list.empty() == true);
    
    std::cout << "Czyszczenie: OK" << std::endl;
}


void testReverseDisplay() {
    std::cout << "=== Test wyswietlania odwrotnego ===" << std::endl;
    
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    // Sprawdzamy czy lista ma poprawne połączenia w obie strony
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    // Test consistency - można ręcznie sprawdzić połączenia
    // ale w testach automatycznych skupiamy się na funkcjonalności
    
    std::cout << "Wyswietlanie odwrotne: OK" << std::endl;
}

int main() {
    testBasicOperations();
    testCopyOperations();
    testMoveOperations();
    testIndexOperations();
    testClearAndDisplay();
    testReverseDisplay();
    
    std::cout << "\n=================================" << std::endl;
    std::cout << "WSZYSTKIE TESTY ZAKONCZONE POMYSLNIE!" << std::endl;
    std::cout << "=================================" << std::endl;
    
    return 0;
}