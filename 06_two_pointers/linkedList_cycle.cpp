/*
Given a linked list with potentially a loop, determine whether the linked list from the first node contains a cycle in it. For bonus points, do this with constant space.
*/

#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

template <typename T>
struct Node {
    T val;
    Node<T>* next;

    explicit Node(T val, Node<T>* next = nullptr)
        : val{val}, next{next} {}

    ~Node() {
        delete next;
    }
};

//This solution destroys the internal structure of the linked list
//but it works and is faster
bool has_cycle_old(Node<int>* nodes) {
    // WRITE YOUR BRILLIANT CODE HERE    

    while(nodes!= nullptr) {
    
        if (nodes->next == nodes) {
            return true;
        }
        Node<int> * temp;
        temp = nodes->next;
        //Create a cycle in the same node to detect
        //if we have a loop in a second pass
        nodes->next = nodes;
        //Go to the next element
        nodes = temp;
    }
    return false;
}

bool has_cycle(Node<int>* nodes) {
    // WRITE YOUR BRILLIANT CODE HERE    
    Node<int>* slow, *fast;
    bool goSlow = false;
    
    slow = fast = nodes;
    while(fast!= nullptr) {
        
        fast = fast->next;
        
        //Cycle found when fast reches slow
        if (slow == fast) {
            return true;
        }
        
        //Slow pointer will go half the speed of fast ptr
        if (goSlow) {
            slow = slow->next;
        }
        goSlow = !goSlow;
        
    }
    return false;
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
    std::vector<int> rawInput = get_words<int>();
    std::vector<Node<int>*> nodeList;
    for (int i = 0; i < rawInput.size(); i++) {
        nodeList.push_back(new Node<int>(i));
    }
    for (int i = 0; i < rawInput.size(); i++) {
        if (rawInput[i] != -1) {
            nodeList[i]->next = nodeList[rawInput[i]];
        }
    }
    Node<int>* nodes = nodeList[0];
    bool res = has_cycle(nodes);
    std::cout << std::boolalpha << res << '\n';
}
