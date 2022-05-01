/*
Given a binary tree, invert it and return the new value. You may invert it in-place.

To "invert" a binary tree, switch the left subtree and the right subtree, and invert them both. Inverting an empty tree does nothing.

Input
tree: a binary tree that needs to be inverted.
Output
The inverted binary tree.
*/
#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
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

Node<int>* invert_binary_tree_it(Node<int>* tree) {
    // WRITE YOUR BRILLIANT CODE HERE
    Node<int>* temp, * curr;
    std::queue<Node<int>*> tQueue;
    
    tQueue.push(tree);
    
    while (!tQueue.empty())
    {
        curr = tQueue.front();
        tQueue.pop();
        
        if ( curr != nullptr) {
            temp = curr->left;
            curr->left = curr->right;
            curr->right = temp;
            tQueue.push(curr->left);
            tQueue.push(curr->right);
        }
        
    }
    return tree;
}

Node<int>* invert_binary_tree(Node<int>* tree) {
    // WRITE YOUR BRILLIANT CODE HERE
    Node<int>* temp;
    
    if ( tree != nullptr) {
        temp = tree->left;
        tree->left = invert_binary_tree(tree->right);
        tree->right = invert_binary_tree(temp);
    }
    
    return tree;
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
    std::vector<std::string> tree_vec = get_words<std::string>();
    auto tree_it = tree_vec.begin();
    Node<int>* tree = build_tree<int>(tree_it, [](auto s) { return std::stoi(s); });
    //Node<int>* res = invert_binary_tree(tree);
    Node<int>* res = invert_binary_tree_it(tree);
    std::vector<std::string> res_vec;
    format_tree(res, [](auto v) { return std::to_string(v); }, res_vec);
    put_words(res_vec);
}
