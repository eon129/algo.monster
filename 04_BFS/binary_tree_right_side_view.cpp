/*
Given a binary tree, return the rightmost node of each level.
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

std::vector<int> binary_tree_right_side_view(Node<int>* root) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::deque<Node<int>*> q;
    std::vector<int> result;
    
    q.push_back(root);
    
    while (!q.empty()) {
    
        int n = q.size();
        
        while(n) {
            
            Node<int>* currN = q.back();
            q.pop_back();
            
            if (currN->left != nullptr) {  
                q.push_front(currN->left);
            }
            if (currN->right != nullptr) {    
                q.push_front(currN->right);
            }
            
            if(n == 1) {          
                result.push_back(currN->val);
            }
            
            n--;
        }

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
    std::vector<int> res = binary_tree_right_side_view(root);
    put_words(res);
}
