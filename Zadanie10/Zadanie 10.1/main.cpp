#include <iostream>
#include <cassert>

template <typename T>
class BSTNode {
public:
    T value;
    BSTNode *left, *right;
    
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {
        delete left;
        delete right;
    }
};

template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { delete root; }
    bool empty() const { return root == nullptr; }
    void insert(const T& item) { root = insert(root, item); }
    
    // Zadanie 10.1
    T* find_min() const;
    T* find_max() const;
    
private:
    BSTNode<T>* insert(BSTNode<T>* node, const T& item) {
        if (node == nullptr) return new BSTNode<T>(item);
        if (item < node->value)
            node->left = insert(node->left, item);
        else
            node->right = insert(node->right, item);
        return node;
    }
};

// Implementacja find_min()
template <typename T>
T* BinarySearchTree<T>::find_min() const {
    if (empty()) return nullptr;
    
    BSTNode<T>* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return &(current->value);
}

// Implementacja find_max()
template <typename T>
T* BinarySearchTree<T>::find_max() const {
    if (empty()) return nullptr;
    
    BSTNode<T>* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return &(current->value);
}

// Proste testy
int main() {
    // Test 1: Puste drzewo
    {
        BinarySearchTree<int> tree;
        assert(tree.find_min() == nullptr);
        assert(tree.find_max() == nullptr);
        std::cout << "Test 1 (puste drzewo) - OK\n";
    }
    
    // Test 2: Jedna wartość
    {
        BinarySearchTree<int> tree;
        tree.insert(5);
        assert(*tree.find_min() == 5);
        assert(*tree.find_max() == 5);
        std::cout << "Test 2 (jedna wartosc) - OK\n";
    }
    
    // Test 3: Wiele wartości
    {
        BinarySearchTree<int> tree;
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);
        
        assert(*tree.find_min() == 20);
        assert(*tree.find_max() == 80);
        std::cout << "Test 3 (wiele wartosci) - OK\n";
    }
    
    // Test 4: Wartości ujemne
    {
        BinarySearchTree<int> tree;
        tree.insert(0);
        tree.insert(-10);
        tree.insert(10);
        tree.insert(-20);
        tree.insert(-5);
        
        assert(*tree.find_min() == -20);
        assert(*tree.find_max() == 10);
        std::cout << "Test 4 (wartosci ujemne) - OK\n";
    }
    
    std::cout << "\nWszystkie testy zakończone sukcesem!\n";
    return 0;
}