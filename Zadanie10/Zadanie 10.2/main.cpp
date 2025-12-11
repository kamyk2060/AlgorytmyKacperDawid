#include <iostream>
#include <cassert>

// Szablon wezla drzewa BST z laczem do rodzica
template <typename T>
class BSTNode {
public:
    T value;
    BSTNode *left, *right, *parent;
    
    BSTNode(const T& item, BSTNode* p = nullptr) 
        : value(item), left(nullptr), right(nullptr), parent(p) {}
    
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
    
    // Wstawianie z ustawianiem parent
    void insert(const T& item) { 
        root = insert(root, item, nullptr); 
    }
    
    // Zadanie 10.2 - Successor
    T* find_successor(const T& item) const;
    
    BSTNode<T>* find_node(const T& item) const {
        BSTNode<T>* current = root;
        while (current != nullptr && current->value != item) {
            if (item < current->value)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    }
    
private:
    BSTNode<T>* insert(BSTNode<T>* node, const T& item, BSTNode<T>* parent) {
        if (node == nullptr) return new BSTNode<T>(item, parent);
        
        if (item < node->value) {
            node->left = insert(node->left, item, node);
        } else {
            node->right = insert(node->right, item, node);
        }
        return node;
    }
};

// Implementacja find_successor()
template <typename T>
T* BinarySearchTree<T>::find_successor(const T& item) const {
    // Znajdz wezel z dana wartoscia
    BSTNode<T>* node = find_node(item);
    if (node == nullptr) return nullptr; // Wezel nie istnieje
    
    // Przypadek 1: Jesli wezel ma prawe dziecko
    if (node->right != nullptr) {
        // Successor to najmniejszy element w prawym poddrzewie
        BSTNode<T>* current = node->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return &(current->value);
    }
    
    // Przypadek 2: Jesli wezel nie ma prawego dziecka
    // Successor to pierwszy przodek, dla ktorego node jest w lewym poddrzewie
    BSTNode<T>* current = node;
    BSTNode<T>* parent = node->parent;
    
    while (parent != nullptr && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }
    
    if (parent != nullptr) {
        return &(parent->value);
    }
    
    // Nie ma nastepnika (node to maksymalny element w drzewie)
    return nullptr;
}

// Testy dla find_successor()
int main() {
    std::cout << "=== Test funkcji find_successor() ===\n";
    
    // Test 1: Puste drzewo
    {
        BinarySearchTree<int> tree;
        assert(tree.find_successor(5) == nullptr);
        std::cout << "Test 1 (puste drzewo) - OK\n";
    }
    
    // Test 2: Drzewo z jednym elementem
    {
        BinarySearchTree<int> tree;
        tree.insert(10);
        assert(tree.find_successor(10) == nullptr); // Brak nastepnika
        assert(tree.find_successor(5) == nullptr); // Nieistniejacy element
        std::cout << "Test 2 (jeden element) - OK\n";
    }
    
    // Test 3: Proste drzewo - nastepnik w prawym poddrzewie
    {
        BinarySearchTree<int> tree;
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        
        int* succ1 = tree.find_successor(30);
        assert(succ1 != nullptr && *succ1 == 50);
        
        int* succ2 = tree.find_successor(50);
        assert(succ2 != nullptr && *succ2 == 70);
        
        int* succ3 = tree.find_successor(70);
        assert(succ3 == nullptr); // Brak nastepnika
        
        std::cout << "Test 3 (proste drzewo) - OK\n";
    }
    
    // Test 4: Zlozone drzewo - nastepnik u przodka
    {
        BinarySearchTree<int> tree;
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);
        
        /* Drzewo:
               50
             /    \
            30     70
           /  \   /  \
          20  40 60  80
        */
        
        // Successor 20 -> 30 (prawe dziecko istnieje)
        int* succ1 = tree.find_successor(20);
        assert(succ1 != nullptr && *succ1 == 30);
        
        // Successor 30 -> 40 (najmniejszy w prawym poddrzewie)
        int* succ2 = tree.find_successor(30);
        assert(succ2 != nullptr && *succ2 == 40);
        
        // Successor 40 -> 50 (u przodka)
        int* succ3 = tree.find_successor(40);
        assert(succ3 != nullptr && *succ3 == 50);
        
        // Successor 60 -> 70
        int* succ4 = tree.find_successor(60);
        assert(succ4 != nullptr && *succ4 == 70);
        
        // Successor 80 -> nullptr (brak nastepnika)
        int* succ5 = tree.find_successor(80);
        assert(succ5 == nullptr);
        
        std::cout << "Test 4 (zlozone drzewo) - OK\n";
    }
    
    // Test 6: Przypadek szczegolny - nastepnik u korzenia
    {
        BinarySearchTree<int> tree;
        tree.insert(100);
        tree.insert(50);
        tree.insert(150);
        tree.insert(25);
        tree.insert(75);
        tree.insert(125);
        tree.insert(175);
        tree.insert(60);
        tree.insert(90);
        
        /* Drzewo:
                  100
                /     \
              50       150
             /  \     /   \
            25   75  125  175
                /  \
               60   90
        */
        
        // Successor 90 -> 100 (u przodka)
        int* succ = tree.find_successor(90);
        assert(succ != nullptr && *succ == 100);
        
        std::cout << "Test 6 (nastepnik u korzenia) - OK\n";
    }
    
    // Test 7: Wszystkie elementy inorder i ich nastepniki
    {
        BinarySearchTree<int> tree;
        tree.insert(8);
        tree.insert(3);
        tree.insert(10);
        tree.insert(1);
        tree.insert(6);
        tree.insert(14);
        tree.insert(4);
        tree.insert(7);
        tree.insert(13);
        
        /* Inorder: 1, 3, 4, 6, 7, 8, 10, 13, 14
           Successory:
           1 -> 3
           3 -> 4
           4 -> 6
           6 -> 7
           7 -> 8
           8 -> 10
           10 -> 13
           13 -> 14
           14 -> nullptr
        */
        
        assert(*tree.find_successor(1) == 3);
        assert(*tree.find_successor(3) == 4);
        assert(*tree.find_successor(4) == 6);
        assert(*tree.find_successor(6) == 7);
        assert(*tree.find_successor(7) == 8);
        assert(*tree.find_successor(8) == 10);
        assert(*tree.find_successor(10) == 13);
        assert(*tree.find_successor(13) == 14);
        assert(tree.find_successor(14) == nullptr);
        
        std::cout << "Test 7 (pelna sekwencja) - OK\n";
    }
    
    std::cout << "\n=== Wszystkie testy zakonczone sukcesem! ===\n";
    
    // Dodatkowa demonstracja
    std::cout << "\n=== Demonstracja ===" << std::endl;
    BinarySearchTree<int> demo;
    int values[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    
    for (int val : values) {
        demo.insert(val);
    }
    
    std::cout << "Drzewo z wartosciami: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Testujemy kilka nastepnikow
    int test_val = 13;
    int* succ = demo.find_successor(test_val);
    if (succ) {
        std::cout << "Nastepnik " << test_val << " to: " << *succ << std::endl;
    } else {
        std::cout << test_val << " nie ma nastepnika" << std::endl;
    }
    
    test_val = 20;
    succ = demo.find_successor(test_val);
    if (succ) {
        std::cout << "Nastepnik " << test_val << " to: " << *succ << std::endl;
    } else {
        std::cout << test_val << " nie ma nastepnika" << std::endl;
    }
    
    return 0;
}