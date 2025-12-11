#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <cassert>
#include <iostream>

int rpn(const std::vector<std::string>& input) {
    std::stack<int> stack;
    
    for (const auto& token : input) {
        // Sprawdzenie czy to operator
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Sprawdzenie czy są wystarczająco argumentów na stosie
            if (stack.size() < 2) {
                throw std::invalid_argument("Niewystarczająca liczba argumentów dla operatora: " + token);
            }
            
            // Pobranie dwóch ostatnich wartości ze stosu (WAŻNA KOLEJNOŚĆ!)
            int right = stack.top();  // drugi operand (pobierany pierwszy)
            stack.pop();
            int left = stack.top();   // pierwszy operand (pobierany drugi)
            stack.pop();
            
            // Wykonanie operacji w poprawnej kolejności: left operator right
            if (token == "+") {
                stack.push(left + right);
            } else if (token == "-") {
                stack.push(left - right);
            } else if (token == "*") {
                stack.push(left * right);
            } else if (token == "/") {
                if (right == 0) {
                    throw std::invalid_argument("Dzielenie przez zero");
                }
                stack.push(left / right);
            }
        } else {
            // To jest liczba - konwersja string na int i dodanie na stos
            try {
                int number = std::stoi(token);
                stack.push(number);
            } catch (const std::exception& e) {
                throw std::invalid_argument("Nieprawidłowy token: " + token);
            }
        }
    }
    
    // Sprawdzenie czy na końcu jest dokładnie jedna wartość na stosie
    if (stack.size() != 1) {
        throw std::invalid_argument("Nieprawidłowe wyrażenie ONP");
    }
    
    return stack.top();
}

void test_rpn() {
    // Test 1: (2+3)*6 = 30
    std::vector<std::string> test1 = {"2", "3", "+", "6", "*"};
    assert(rpn(test1) == 30);
    std::cout << "Test 1 passed: (2+3)*6 = 30" << std::endl;
    
    // Test 2: 6/2 = 3
    std::vector<std::string> test2 = {"6", "2", "/"};
    assert(rpn(test2) == 3);
    std::cout << "Test 2 passed: 6/2 = 3" << std::endl;
    
    // Test 3: +4-(-2) = 6
    std::vector<std::string> test3 = {"4", "-2", "-"};
    assert(rpn(test3) == 6);
    std::cout << "Test 3 passed: 4-(-2) = 6" << std::endl;
    
    // Test 4: 5 + (1+2)*4 - 3 = 14
    std::vector<std::string> test4 = {"5", "1", "2", "+", "4", "*", "+", "3", "-"};
    assert(rpn(test4) == 14);
    std::cout << "Test 4 passed: 5 + (1+2)*4 - 3 = 14" << std::endl;
    
    // Test 5: Proste dodawanie
    std::vector<std::string> test5 = {"10", "5", "+"};
    assert(rpn(test5) == 15);
    std::cout << "Test 5 passed: 10 + 5 = 15" << std::endl;
    
    // Test 6: Odejmowanie
    std::vector<std::string> test6 = {"10", "5", "-"};
    assert(rpn(test6) == 5);
    std::cout << "Test 6 passed: 10 - 5 = 5" << std::endl;
    
    // Test 7: Mnożenie
    std::vector<std::string> test7 = {"10", "5", "*"};
    assert(rpn(test7) == 50);
    std::cout << "Test 7 passed: 10 * 5 = 50" << std::endl;
    
    std::cout << "Wszystkie testy przeszly pomyslnie!" << std::endl;
}


int main() {
    std::cout << "Uruchamianie testow ONP..." << std::endl;
    test_rpn();
    std::cout << std::endl;
    return 0;
}

