#include "arraylist.h"
#include <iostream>
#include <cassert>
#include <algorithm>

void test_constructor_and_basic_operations() {
    std::cout << "=== Test 1: Konstruktor i podstawowe operacje ===" << std::endl;
    ArrayList<int> list(5);
    
    assert(list.empty());
    assert(list.size() == 0);
    assert(list.max_size() == 5);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    assert(!list.empty());
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Lista: " << list << std::endl;
    std::cout << "Test 1: PASSED\n" << std::endl;
}

void test_push_front_and_pop() {
    std::cout << "=== Test 2: Push front i operacje pop ===" << std::endl;
    ArrayList<int> list(5);
    
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Po push_front: " << list << std::endl;
    
    list.pop_front();
    assert(list.front() == 2);
    assert(list.size() == 2);
    
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 1);
    
    std::cout << "Po pop_front i pop_back: " << list << std::endl;
    std::cout << "Test 2: PASSED\n" << std::endl;
}

void test_copy_constructor_and_assignment() {
    std::cout << "=== Test 3: Konstruktor kopiujący i przypisanie ===" << std::endl;
    ArrayList<int> list1(5);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Konstruktor kopiujący
    ArrayList<int> list2(list1);
    assert(list2.size() == 3);
    assert(list2[0] == 1);
    assert(list2[1] == 2);
    assert(list2[2] == 3);
    
    // Operator przypisania
    ArrayList<int> list3(3);
    list3 = list1;
    assert(list3.size() == 3);
    assert(list3[0] == 1);
    
    std::cout << "List1: " << list1 << std::endl;
    std::cout << "List2 (copy): " << list2 << std::endl;
    std::cout << "List3 (assignment): " << list3 << std::endl;
    std::cout << "Test 3: PASSED\n" << std::endl;
}

void test_move_operations() {
    std::cout << "=== Test 4: Operacje move ===" << std::endl;
    ArrayList<int> list1(5);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    // Move constructor
    ArrayList<int> list2(std::move(list1));
    assert(list2.size() == 3);
    assert(list1.empty());
    
    // Move assignment
    ArrayList<int> list3(3);
    list3 = std::move(list2);
    assert(list3.size() == 3);
    assert(list2.empty());
    
    std::cout << "List3 (after move): " << list3 << std::endl;
    std::cout << "Test 4: PASSED\n" << std::endl;
}

void test_index_operations() {
    std::cout << "=== Test 5: Operacje indeksowe ===" << std::endl;
    ArrayList<int> list(5);
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
    
    std::cout << "Lista po operacjach indeksowych: " << list << std::endl;
    std::cout << "Test 5: PASSED\n" << std::endl;
}

void test_sort_and_reverse() {
    std::cout << "=== Test 6: Sortowanie i odwracanie ===" << std::endl;
    ArrayList<int> list(6);
    list.push_back(5);
    list.push_back(2);
    list.push_back(8);
    list.push_back(1);
    list.push_back(9);
    
    std::cout << "Przed sortowaniem: " << list << std::endl;
    list.sort();
    std::cout << "Po sortowaniu: " << list << std::endl;
    
    for (std::size_t i = 1; i < list.size(); ++i) {
        assert(list[i-1] <= list[i]);
    }
    
    list.reverse();
    std::cout << "Po odwróceniu: " << list << std::endl;
    
    for (std::size_t i = 1; i < list.size(); ++i) {
        assert(list[i-1] >= list[i]);
    }
    
    std::cout << "Test 6: PASSED\n" << std::endl;
}

void test_merge() {
    std::cout << "=== Test 7: Scalanie list ===" << std::endl;
    
    // Upewnij się, że lista ma wystarczająco miejsca
    ArrayList<int> list1(10);  // Zwiększony rozmiar
    list1.push_back(1);
    list1.push_back(3);
    list1.push_back(5);
    
    ArrayList<int> list2(10);  // Zwiększony rozmiar  
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(6);
    
    std::cout << "List1: " << list1 << std::endl;
    std::cout << "List2: " << list2 << std::endl;
    std::cout << "List1 size: " << list1.size() << ", max_size: " << list1.max_size() << std::endl;
    std::cout << "List2 size: " << list2.size() << ", max_size: " << list2.max_size() << std::endl;
    
    list1.merge(list2);
    std::cout << "Po scaleniu: " << list1 << std::endl;
    std::cout << "List2 po scaleniu: " << list2 << " (rozmiar: " << list2.size() << ")" << std::endl;
    
    assert(list1.size() == 6);
    for (std::size_t i = 1; i < list1.size(); ++i) {
        assert(list1[i-1] <= list1[i]);
    }
    assert(list2.empty()); // List2 powinna być pusta po merge
    
    std::cout << "Test 7: PASSED\n" << std::endl;
}

void test_clear_and_full() {
    std::cout << "=== Test 8: Czyszczenie i pełna lista ===" << std::endl;
    ArrayList<int> list(3);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    assert(list.full());
    assert(!list.empty());
    
    list.clear();
    assert(list.empty());
    assert(!list.full());
    
    std::cout << "Po wyczyszczeniu: " << list << std::endl;
    std::cout << "Test 8: PASSED\n" << std::endl;
}

void test_string_list() {
    std::cout << "=== Test 9: Lista stringów ===" << std::endl;
    ArrayList<std::string> list(4);
    
    list.push_back("Hello");
    list.push_back("World");
    list.push_front("C++");
    
    std::cout << "Lista stringów: " << list << std::endl;
    
    assert(list.size() == 3);
    assert(list[0] == "C++");
    assert(list[1] == "Hello");
    assert(list[2] == "World");
    
    std::cout << "Test 9: PASSED\n" << std::endl;
}

int main() {
    std::cout << "Rozpoczynanie testów ArrayList...\n" << std::endl;
    
    try {
        test_constructor_and_basic_operations();
        test_push_front_and_pop();
        test_copy_constructor_and_assignment();
        test_move_operations();
        test_index_operations();
        test_sort_and_reverse();
        test_merge();
        test_clear_and_full();
        test_string_list();
        
        std::cout << "====================================" << std::endl;
        std::cout << "WSZYSTKIE TESTY ZOSTAŁY POMYŚLNIE PRZEPROWADZONE!" << std::endl;
        std::cout << "====================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test nie powiódł się: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}