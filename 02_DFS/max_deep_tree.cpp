#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <vector> // vector
#include <queue>

using namespace std;

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

int _tree_max_depth(Node<int>* root, int currentMax) {

    int left = 0, right = 0;
    
    if (root->left != nullptr) {
        left = _tree_max_depth(root->left, currentMax + 1);
    }
    
    if (root->right != nullptr) {
        right = _tree_max_depth(root->right, currentMax + 1);
    }
    
    currentMax = (currentMax > left) ? currentMax : left;
    currentMax = (currentMax > right) ? currentMax : right ;
    
    return currentMax;

}


int _tree_max_depth_it(Node<int>* root) {

    int left = 0, right = 0;
    queue<Node<int>*> treeq;
    queue<int> maxq;
    Node<int> * currNode;
    int max, currMax;
    
    if (root == nullptr) {
        return 0;
    }
    
    treeq.push(root);
    maxq.push(1);
    
    while (!treeq.empty()) {
    
        currNode = treeq.front();
        currMax = maxq.front();
        
        treeq.pop();
        maxq.pop();
        
        //set new current max
        max = currMax > max ? currMax : max;
        
        if (currNode->right != nullptr) {
            treeq.push(currNode->right);
            maxq.push(currMax + 1);
        }
        
        if (currNode->left != nullptr) {
            treeq.push(currNode->left);
            maxq.push(currMax + 1);   
        }      
    }
    
    
    return max;

}

int tree_max_depth(Node<int>* root) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //return (root != nullptr)?_tree_max_depth(root, 1) : 0;
    
    return _tree_max_depth_it(root);
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
    std::vector<std::string> root_vec = get_words<std::string>();
    auto root_it = root_vec.begin();
    Node<int>* root = build_tree<int>(root_it, [](auto s) { return std::stoi(s); });
    int res = tree_max_depth(root);
    std::cout << res << '\n';
}
