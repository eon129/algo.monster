/*
A balanced binary tree is defined as a tree such that either it is an empty tree, or both its subtree are balanced and has a height difference of at most 1.

In that case, given a binary tree, determine if it's balanced.
*/
#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <vector> // vector
#include <cstdlib>

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

struct balanceResult {
    bool r;
    int  count;
};

struct balanceResult _is_balanced(Node<int>* tree) {
    // WRITE YOUR BRILLIANT CODE HERE
    struct balanceResult res, resL, resR;
    
    int max, min;
    
    if (tree == nullptr) {
        res.r = true;
        res.count = 0;
        return res;
    }
    
    resL = _is_balanced(tree->left);
    resR = _is_balanced(tree->right);
    
    //Are both children balanced
    res.r = resL.r && resR.r;
    
    max = std::max(resL.count, resR.count);
    min = std::min(resL.count, resR.count);
    
    res.r = res.r && ((max - min) <= 1);
    
    res.count = max + 1;
    
    return res;
}

 int _is_balanced2(Node<int>* tree) {
     
     // WRITE YOUR BRILLIANT CODE HERE
     int leftH, rightH;
    
     if (tree == nullptr) {
         return 0;
     }
    
     leftH = _is_balanced2(tree->left);
     rightH = _is_balanced2(tree->right);
     
     if ( leftH == -1 || rightH == -1 ) {
         return -1;
     }
    
     if (std::abs(leftH - rightH) > 1) {
         return -1;
     }
    
    return std::max(leftH, rightH) + 1;
}

bool is_balanced(Node<int>* tree) {
    
    /*struct balanceResult r;
    r = _is_balanced(tree);
    return r.r;*/
    
    return (_is_balanced2(tree) != -1);
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

int main() {
    std::vector<std::string> tree_vec = get_words<std::string>();
    auto tree_it = tree_vec.begin();
    Node<int>* tree = build_tree<int>(tree_it, [](auto s) { return std::stoi(s); });
    bool res = is_balanced(tree);
    std::cout << std::boolalpha << res << '\n';
}
