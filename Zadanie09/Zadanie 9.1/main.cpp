#include <iostream>
#include <cassert>
#include <stack>

// Szablon dla wezla drzewa binarnego
template <typename T>
class BSTNode {
public:
    T value;
    BSTNode *left, *right;
    
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; }
};

// WERSJA REKURENCYJNA - zlicza liscie drzewa
template <typename T>
int calc_leaves_recursive(BSTNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    
    return calc_leaves_recursive(node->left) + calc_leaves_recursive(node->right);
}

// WERSJA ITERACYJNA - zlicza liscie drzewa (z uzyciem stosu)
template <typename T>
int calc_leaves_iterative(BSTNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    
    int leaf_count = 0;
    std::stack<BSTNode<T>*> S;
    S.push(node);
    
    while (!S.empty()) {
        BSTNode<T>* current = S.top();
        S.pop();
        
        if (current->left == nullptr && current->right == nullptr) {
            leaf_count++;
        } else {
            if (current->right != nullptr) {
                S.push(current->right);
            }
            if (current->left != nullptr) {
                S.push(current->left);
            }
        }
    }
    
    return leaf_count;
}

// Funkcja pomocnicza do tworzenia wezla
template <typename T>
BSTNode<T>* create_node(const T& value) {
    return new BSTNode<T>(value);
}

int main() {
    std::cout << "=== TESTY FUNKCJI calc_leaves() ===\n\n";
    
    // TEST 1: Puste drzewo
    {
        BSTNode<int>* tree1 = nullptr;
        assert(calc_leaves_recursive(tree1) == 0);
        assert(calc_leaves_iterative(tree1) == 0);
        std::cout << "Test 1 (puste drzewo): PASSED\n";
    }
    
    // TEST 2: Drzewo z jednym wezlem (korzen jest lisciem)
    {
        BSTNode<int>* tree2 = create_node(1);
        assert(calc_leaves_recursive(tree2) == 1);
        assert(calc_leaves_iterative(tree2) == 1);
        std::cout << "Test 2 (jeden wezel): PASSED\n";
        delete tree2;
    }
    
    // TEST 3: Drzewo z trzema wezlami (dwa liscie)
    //     1
    //    / \
    //   2   3
    {
        BSTNode<int>* tree3 = create_node(1);
        tree3->left = create_node(2);
        tree3->right = create_node(3);
        assert(calc_leaves_recursive(tree3) == 2);
        assert(calc_leaves_iterative(tree3) == 2);
        std::cout << "Test 3 (trzy wezly, dwa liscie): PASSED\n";
        delete tree3;
    }
    
    // TEST 4: Drzewo niesymetryczne
    //       1
    //      / \
    //     2   3
    //    /
    //   4
    {
        BSTNode<int>* tree4 = create_node(1);
        tree4->left = create_node(2);
        tree4->right = create_node(3);
        tree4->left->left = create_node(4);
        assert(calc_leaves_recursive(tree4) == 2);
        assert(calc_leaves_iterative(tree4) == 2);
        std::cout << "Test 4 (drzewo niesymetryczne): PASSED\n";
        delete tree4;
    }
    
    // TEST 5: Wieksze drzewo
    //         1
    //        / \
    //       2   3
    //      / \   \
    //     4   5   6
    //    /
    //   7
    {
        BSTNode<int>* tree5 = create_node(1);
        tree5->left = create_node(2);
        tree5->right = create_node(3);
        tree5->left->left = create_node(4);
        tree5->left->right = create_node(5);
        tree5->right->right = create_node(6);
        tree5->left->left->left = create_node(7);
        assert(calc_leaves_recursive(tree5) == 3);
        assert(calc_leaves_iterative(tree5) == 3);
        std::cout << "Test 5 (wieksze drzewo): PASSED\n";
        delete tree5;
    }
    
    // TEST 6: Drzewo zdegenerowane (liniowe) - tylko prawe dzieci
    //   1
    //    \
    //     2
    //      \
    //       3
    //        \
    //         4
    {
        BSTNode<int>* tree6 = create_node(1);
        tree6->right = create_node(2);
        tree6->right->right = create_node(3);
        tree6->right->right->right = create_node(4);
        assert(calc_leaves_recursive(tree6) == 1);
        assert(calc_leaves_iterative(tree6) == 1);
        std::cout << "Test 6 (drzewo liniowe - prawe): PASSED\n";
        delete tree6;
    }
    
    // TEST 7: Drzewo zdegenerowane (liniowe) - tylko lewe dzieci
    //       1
    //      /
    //     2
    //    /
    //   3
    //  /
    // 4
    {
        BSTNode<int>* tree7 = create_node(1);
        tree7->left = create_node(2);
        tree7->left->left = create_node(3);
        tree7->left->left->left = create_node(4);
        assert(calc_leaves_recursive(tree7) == 1);
        assert(calc_leaves_iterative(tree7) == 1);
        std::cout << "Test 7 (drzewo liniowe - lewe): PASSED\n";
        delete tree7;
    }
    
    // TEST 8: Drzewo pelne
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    {
        BSTNode<int>* tree8 = create_node(1);
        tree8->left = create_node(2);
        tree8->right = create_node(3);
        tree8->left->left = create_node(4);
        tree8->left->right = create_node(5);
        tree8->right->left = create_node(6);
        tree8->right->right = create_node(7);
        assert(calc_leaves_recursive(tree8) == 4);
        assert(calc_leaves_iterative(tree8) == 4);
        std::cout << "Test 8 (drzewo pelne): PASSED\n";
        delete tree8;
    }
    
    std::cout << "\n=== Wszystkie testy zakonczone sukcesem! ===\n";
    
    return 0;
}