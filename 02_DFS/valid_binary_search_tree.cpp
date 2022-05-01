/*
A binary search tree is a binary tree with the property that any of its node's value is greater than or equal to any node in its left subtree and less than or equal to any node's value in its right subtree.
*/

#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <vector> // vector
#include <queue>

#define INT_MAX (2147483647)

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

struct treeInfo {
    int max;
    int min;
    bool valid;
};

struct treeInfo _valid_bst(Node<int>* root, int parentValue) {
    
    struct treeInfo currentInfo;
    struct treeInfo leftInfo, rightInfo;
    
    if ( root == nullptr) {
        
        currentInfo.max = parentValue;
        currentInfo.min = parentValue;
        currentInfo.valid = true;
        
        return currentInfo;
    }
    
    leftInfo = _valid_bst(root->left, root->val);
    rightInfo = _valid_bst(root->right, root->val);
    
    currentInfo.valid = (rightInfo.valid && leftInfo.valid);
    currentInfo.valid &= root->val >= leftInfo.max;
    currentInfo.valid &= root->val <= rightInfo.min;  
    
    
    currentInfo.max = rightInfo.max;
    currentInfo.min = leftInfo.min;
    
    return currentInfo;
}


struct NodeInfo {
    
    Node<int>* n;
    int max;
    int min;
 
    NodeInfo (Node<int>*n, int min =-1, int max = INT_MAX): n{n}, min{min}, max{max} {}
};

bool _valid_bst_it(Node<int>* root)
{
    bool result = true;
    if ( root == nullptr) {
        
        return true;
    }
    
    std::queue<NodeInfo> q;
    NodeInfo currNode(root);
    
    q.push(currNode);
    
    while (!q.empty()){
    
        currNode = q.front();
        q.pop();
        
        if (!(currNode.min <= currNode.n->val && currNode.max >= currNode.n->val)) {
            result = false;
            break;
        }
        
        if ( currNode.n->right != nullptr) {
            NodeInfo r(currNode.n->right, currNode.n->val, currNode.max);
            q.push(r);
        }
        
        if ( currNode.n->left != nullptr) {
            NodeInfo l(currNode.n->left, currNode.min, currNode.n->val);
            q.push(l);    
        }
    }
    
    return result;
}

bool valid_bst(Node<int>* root) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //recursive
    //return _valid_bst(root, 0).valid;
    
    //iterative
    return _valid_bst_it(root);
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
    bool res = valid_bst(root);
    std::cout << std::boolalpha << res << '\n';
}
