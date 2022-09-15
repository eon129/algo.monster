/*
Now we will start with an introductory problem to get you familiar with the data structure. Complete the class below to support the following two operations:

    merge(x, y) merges the sets that the x and y belong to,
    is_same(x, y) determines if x and y belong to the same set. If so return true, otherwise false.

Example:

merge(1, 2)

merge(2, 3)

is_same(1, 3) => true

is_same(2, 4) => false

Explanation:

We merge elements 1 and 2 then we merge the set of 1 and 2 with the element 3, so we should have now have 2 sets, [1, 2, 3] and [4]. Therefore 1 and 3 are in the same set, while 2 and 4 are in different sets.
*/

#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, stoi, string
#include <vector> // vector

template <class T> class UnionFind {
private:
    //std::unordered_map<T, T> id;

public:
    std::unordered_map<T, T> id;
    T find(T x) {

        T y = id.count(x) ? id[x] : x;
        
        if (y != x) {
            y = find(y);
            id[x] = y;
        }
        return y;
    }


    void union_(T x, T y) {
        id[find(x)] = find(y);
    }

};

class SameSet {
    
private:
    UnionFind<int> uf;
    
public:
    void merge(int x, int y) {
        // WRITE YOUR BRILLIANT CODE HERE
        
        uf.union_(x, y);
    }

    bool is_same(int x, int y) {
        // AND HERE
        
        return uf.find(x) == uf.find(y);
    }
};

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

int main() {
    
    SameSet sol;
    int query_length;
    std::cin >> query_length;
    ignore_line();
    for (int i = 0; i < query_length; i++) {
        std::vector<std::string> segs = get_words<std::string>();
        std::string op = segs.at(0);
        int x = std::stoi(segs.at(1));
        int y = std::stoi(segs.at(2));
        if (op == "union") {
            sol.merge(x, y);
        } else if (op == "is_same") {
            bool res = sol.is_same(x, y);
            std::cout << std::boolalpha << res << '\n';
        }
    }
}