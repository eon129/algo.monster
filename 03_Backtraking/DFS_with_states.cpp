/*
Ternary Tree Paths
Given a ternary tree (each node of the tree has at most three children), find all root-to-leaf paths.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <utility> // move
#include <vector> // vector

template <typename T>
struct Node {
    T val;
    std::vector<Node<T>> children;

    explicit Node(T val, std::vector<Node<T>> children = {})
        : val{val}, children{children} {}
};

std::vector<std::string> _ternary_tree_paths(Node<int> root, std::string string_in) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::vector<std::string> result, temp;
    
    if (root.children.size() > 0 ) {
        
        
        for (Node<int> n : root.children) {
            //Check if needs to add ->
            std::string current;
            current = string_in.empty() ? std::to_string(root.val) : (string_in + "->" + std::to_string(root.val));
            
            //Concatenate vectors
            temp = _ternary_tree_paths(n, current);
            result.insert(std::end(result), std::begin(temp), std::end(temp));
        }
    
        return result;
    }
                  
    return {string_in + "->" + std::to_string(root.val)};
}

std::vector<std::string> ternary_tree_paths(Node<int> root) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    return _ternary_tree_paths(root, "");
}

template<typename T, typename Iter, typename F>
Node<T> build_tree(Iter& it, F f) {
    std::string val = *it;
    ++it;
    int num = std::stoi(*it);
    ++it;
    std::vector<Node<T>> children;
    for (int i = 0; i < num; i++)
        children.emplace_back(build_tree<T>(it, f));
    return Node<T>{f(val), std::move(children)};
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
    std::vector<std::string> root_vec = get_words<std::string>();
    auto root_it = root_vec.begin();
    Node<int> root = build_tree<int>(root_it, [](auto s) { return std::stoi(s); });
    std::vector<std::string> res = ternary_tree_paths(root);
    for (const std::string& line : res) {
        std::cout << line << '\n';
    }
}
