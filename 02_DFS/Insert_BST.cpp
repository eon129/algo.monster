/*
Given the root node of a valid BST and a value to insert into the tree, return a new root node representing the valid BST with the addition of the new item. If the new item already exists in the binary search tree, do not insert anything.

You must expand on the original BST by adding a leaf node. Do not change the structure of the original BST.

Input
bst: a binary tree representing the existing BST.
val: an integer representing the value to be inserted.
Output
A valid BST with the inserted number, or the same BST if the number already exists.

Examples
Example 1:
Input:

tree = <See explanation>
val = 7
Output: <See explanation>

Explanation:

Before insertion:
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, stoi, string, to_string
#include <vector> // vector
#include <queue>

template <typename T>
struct Node {
    T val;
    Node<T>* left;
    Node<T>* right;

    explicit Node(T val, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : val{val}, left{left}, right{right} {}

    ~Node() {
        delete left;
        delete right;
    }
};

Node<int>* insert_bst(Node<int>* bst, int val) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if (bst == nullptr) {
        return new Node<int>(val, nullptr, nullptr);
    }
    
    if (bst->val < val) {
        
        bst->right = insert_bst(bst->right, val);
    }
    
    if (bst->val > val) {
        
        bst->left = insert_bst(bst->left, val);
    }
    
    return bst;
}

Node<int>* insert_bst_it(Node<int>* bst, int val) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if (bst == nullptr) {
        return new Node<int>(val, nullptr, nullptr);
    }
    
    std::queue<Node<int>*> q;
    
    q.push(bst);
    
    while (!q.empty()) {
        
        Node<int> * current;
        
        current = q.front();
        q.pop();
            
        if (current->val < val ) {
            
            if (current->left == nullptr) {
                current->left = new Node<int>(val, nullptr, nullptr);
                break;
            }
            
            q.push(current->left);
        }
        
        if (current->val > val ) {
            
            if (current->right == nullptr) {
                current->right = new Node<int>(val, nullptr, nullptr);
                break;
            }
            
            q.push(current->right);
        }
    }
    
    return bst;
}

template<typename T, typename Iter, typename F>
Node<T>* build_tree(Iter& it, F f) {
    std::string val = *it;
    ++it;
    if (val == "x") return nullptr;
    Node<T>* left = build_tree<T>(it, f);
    Node<T>* right = build_tree<T>(it, f);
    return new Node<T>{f(val), left, right};
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T, typename F>
void format_tree(Node<T>* node, F f, std::vector<std::string>& out) {
    if (node == nullptr) {
        out.emplace_back("x");
        return;
    }
    out.emplace_back(f(node->val));
    format_tree(node->left, f, out);
    format_tree(node->right, f, out);
}

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<std::string> bst_vec = get_words<std::string>();
    auto bst_it = bst_vec.begin();
    Node<int>* bst = build_tree<int>(bst_it, [](auto s) { return std::stoi(s); });
    int val;
    std::cin >> val;
    ignore_line();
    //recursive
    //Node<int>* res = insert_bst(bst, val);
    
    //iteretive
    Node<int>* res = insert_bst_it(bst, val);
    std::vector<std::string> res_vec;
    format_tree(res, [](auto v) { return std::to_string(v); }, res_vec);
    put_words(res_vec);
}
