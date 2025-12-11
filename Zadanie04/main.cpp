#include "singlelist.h"
#include <iostream>
#include <cassert>
#include <algorithm>

void test_constructor_and_basic_operations() {
    std::cout << "=== Test 1: Konstruktor i podstawowe operacje ===" << std::endl;
    SingleList<int> list;
    
    assert(list.empty());
    assert(list.size() == 0);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    assert(!list.empty());
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Lista: ";
    list.display();
    std::cout << "Test 1: PASSED\n" << std::endl;
}

void test_push_front_and_pop() {
    std::cout << "=== Test 2: Push front i operacje pop ===" << std::endl;
    SingleList<int> list;
    
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Po push_front: ";
    list.display();
    
    list.pop_front();
    assert(list.front() == 2);
    assert(list.size() == 2);
    
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 1);
    
    std::cout << "Po pop_front i pop_back: ";
    list.display();
    std::cout << "Test 2: PASSED\n" << std::endl;
}

void test_copy_constructor_and_assignment() {
    std::cout << "=== Test 3: Konstruktor kopiujący i przypisanie ===" << std::endl;
    SingleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Konstruktor kopiujący
    SingleList<int> list2(list1);
    assert(list2.size() == 3);
    assert(list2.front() == 1);
    assert(list2.back() == 3);
    
    // Operator przypisania
    SingleList<int> list3;
    list3 = list1;
    assert(list3.size() == 3);
    assert(list3.front() == 1);
    
    std::cout << "List1: ";
    list1.display();
    std::cout << "List2 (copy): ";
    list2.display();
    std::cout << "List3 (assignment): ";
    list3.display();
    std::cout << "Test 3: PASSED\n" << std::endl;
}

void test_move_operations() {
    std::cout << "=== Test 4: Operacje move ===" << std::endl;
    SingleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Move constructor
    SingleList<int> list2(std::move(list1));
    assert(list2.size() == 3);
    assert(list1.empty());
    
    // Move assignment
    SingleList<int> list3;
    list3 = std::move(list2);
    assert(list3.size() == 3);
    assert(list2.empty());
    
    std::cout << "List3 (after move): ";
    list3.display();
    std::cout << "Test 4: PASSED\n" << std::endl;
}

void test_index_operations() {
    std::cout << "=== Test 5: Operacje indeksowe ===" << std::endl;
    SingleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    // Operator []
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    
    list[1] = 25;
    assert(list[1] == 25);
    
    // Insert
    list.insert(1, 15);
    assert(list.size() == 4);
    assert(list[1] == 15);
    assert(list[2] == 25);
    
    // Erase
    list.erase(2);
    assert(list.size() == 3);
    assert(list[2] == 30);
    
    // Index search
    assert(list.index(10) == 0);
    assert(list.index(15) == 1);
    assert(list.index(30) == 2);
    assert(list.index(999) == -1); // nie ma
    
    std::cout << "Lista po operacjach indeksowych: ";
    list.display();
    std::cout << "Test 5: PASSED\n" << std::endl;
}

void test_reverse() {
    std::cout << "=== Test 6: Odwracanie listy ===" << std::endl;
    SingleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    
    std::cout << "Przed odwróceniem: ";
    list.display();
    
    list.reverse();
    std::cout << "Po odwróceniu: ";
    list.display();
    
    // Sprawdź czy lista jest odwrócona
    assert(list.front() == 5);
    assert(list[1] == 4);
    assert(list[2] == 3);
    assert(list[3] == 2);
    assert(list.back() == 1);
    
    std::cout << "Test 6: PASSED\n" << std::endl;
}

void test_clear() {
    std::cout << "=== Test 7: Czyszczenie listy ===" << std::endl;
    SingleList<int> list;
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    assert(!list.empty());
    assert(list.size() == 3);
    
    list.clear();
    assert(list.empty());
    assert(list.size() == 0);
    
    // Test czy można dodać elementy po wyczyszczeniu
    list.push_back(10);
    list.push_front(5);
    assert(list.size() == 2);
    assert(list.front() == 5);
    assert(list.back() == 10);
    
    std::cout << "Po wyczyszczeniu i dodaniu nowych elementów: ";
    list.display();
    std::cout << "Test 7: PASSED\n" << std::endl;
}

void test_string_list() {
    std::cout << "=== Test 8: Lista stringów ===" << std::endl;
    SingleList<std::string> list;
    
    list.push_back("Hello");
    list.push_back("World");
    list.push_front("C++");
    
    std::cout << "Lista stringów: ";
    list.display();
    
    assert(list.size() == 3);
    assert(list[0] == "C++");
    assert(list[1] == "Hello");
    assert(list[2] == "World");
    
    std::cout << "Test 8: PASSED\n" << std::endl;
}


void test_edge_cases() {
    std::cout << "=== Test 10: Przypadki brzegowe ===" << std::endl;
    
    // Pusta lista
    SingleList<int> empty_list;
    assert(empty_list.empty());
    assert(empty_list.size() == 0);
    
    // Lista z jednym elementem
    SingleList<int> single_list;
    single_list.push_back(42);
    assert(single_list.size() == 1);
    assert(single_list.front() == 42);
    assert(single_list.back() == 42);
    
    single_list.pop_front();
    assert(single_list.empty());
    
    // Test pop_back z jednym elementem
    single_list.push_back(100);
    single_list.pop_back();
    assert(single_list.empty());
    
    // Test reverse z jednym elementem
    single_list.push_back(50);
    single_list.reverse();
    assert(single_list.front() == 50);
    assert(single_list.size() == 1);
    
    std::cout << "Wszystkie przypadki brzegowe przetestowane pomyślnie" << std::endl;
    std::cout << "Test 10: PASSED\n" << std::endl;
}


int main() {
    std::cout << "Rozpoczynanie testów SingleList...\n" << std::endl;
    
    try {
        test_constructor_and_basic_operations();
        test_push_front_and_pop();
        test_copy_constructor_and_assignment();
        test_move_operations();
        test_index_operations();
        test_reverse();
        test_clear();
        test_string_list();
        test_edge_cases();
        
        std::cout << "====================================" << std::endl;
        std::cout << "WSZYSTKIE TESTY ZOSTAŁY POMYŚLNIE PRZEPROWADZONE!" << std::endl;
        std::cout << "====================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test nie powiódł się: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Nieznany błąd podczas testów" << std::endl;
        return 1;
    }
    
    return 0;
}