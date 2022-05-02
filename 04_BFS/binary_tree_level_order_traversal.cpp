/*
Given a binary tree, return its level order traversal. The input is the root node of the tree. The output should be a list of lists of integers, with the ith list containing the values of nodes on level i, from left to right.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <vector> // vector
#include <deque>

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

std::vector<std::vector<int>> level_order_traversal(Node<int>* root) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::deque<Node<int>*> q;
    std::vector<std::vector<int>> result;
    
    q.push_back(root);
    
    /*std::deque<int> qi;
    qi.push_back(1);
    qi.push_back(2);
    qi.push_back(3);
    qi.push_front(1);
    qi.push_front(2);
    qi.push_front(3);
    std::cout << qi.back() << " ";*/
    
    while(!q.empty()) {
        
        int n = q.size();
        std::vector<int> list;
        
        while (n) {
            
            Node<int>* curr = q.front();
            q.pop_front();
            
            //Add value to vector
            list.push_back(curr->val);
            
            if (curr->left != nullptr) {
                q.push_back(curr->left);
            }
            
            if (curr->right != nullptr) {
                q.push_back(curr->right);
            }
            
            n--;
        }
        
        result.push_back(list);
    }
    
    return result;
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

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<std::string> root_vec = get_words<std::string>();
    auto root_it = root_vec.begin();
    Node<int>* root = build_tree<int>(root_it, [](auto s) { return std::stoi(s); });
    std::vector<std::vector<int>> res = level_order_traversal(root);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
