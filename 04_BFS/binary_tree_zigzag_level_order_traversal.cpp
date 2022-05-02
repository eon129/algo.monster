/*
Given a binary tree, return its level order traversal but in alternate left to right order.
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

void q_push(std::deque<Node<int>*> &q, Node<int>* node, int flag) 
{
    if (node != nullptr) {
        
        if (flag) {

            q.push_front(node);
        } else {

            q.push_back(node);
        }
    }
}

Node<int>* q_pop(std::deque<Node<int>*> &q, int flag) 
{
    Node<int>* result;
    
    if (flag) {
        result = q.front();
        q.pop_front();
        return result;
    }
    
    result = q.back();
    q.pop_back();
    return result;
    
}

std::vector<std::vector<int>> zig_zag_traversal(Node<int>* root) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::vector<std::vector<int>> result;
    std::deque<Node<int>*> q;
    int flag = 1;
    
    q.push_back(root);
    
    while (!q.empty()) {
        
        int n = q.size();
        std::vector<int> list;
        
        while (n) {
            
            Node<int>* curr = q_pop(q, flag);
            
            list.push_back(curr->val);
            
            if (flag) {
                
                q_push(q, curr->left, 1-flag);
                q_push(q, curr->right, 1-flag);
            } else {
                
                q_push(q, curr->right, 1-flag);
                q_push(q, curr->left, 1-flag);          
            }
        
            n--;
        }
        
        flag = 1 - flag;
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
    std::vector<std::vector<int>> res = zig_zag_traversal(root);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
