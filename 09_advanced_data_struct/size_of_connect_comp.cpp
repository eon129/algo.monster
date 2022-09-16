/*
For this problem we now ask you to do something similar to the introductory problem, but this time instead of checking whether or not 2 values belong to the same set, we want to know the size of the set that a value belongs to. Therefore, we now support a different set of 2 operations:

    merge(x, y) merge the sets that x and y belong to,
    count(x) returns the size of the set that x belongs to.

Example:

merge(1, 2)

merge(2, 3)

count(3) => 3

count(4) => 1

Explanation:

We merge elements 1 and 2 then we merge the set of 1 and 2 with the element 3, so we should have now have 2 sets, [1, 2, 3] and [4]. Therefore the set that 3 belongs to contains 3 elements, while the set that 4 belongs to contains 1 element.
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

class SetCounter {

private:

    UnionFind<int> dsu;

    std::unordered_map<int, int> sizes;


public:

    void merge(int x, int y) {

        int new_size = count(x) + count(y);

        dsu.union_(x, y);

        sizes[dsu.find(x)] = new_size;

    }

    int count(int x) {

        return sizes.count(dsu.find(x)) ? sizes[dsu.find(x)] : 1;
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
    SetCounter sol;
    int query_length;
    std::cin >> query_length;
    ignore_line();
    for (int i = 0; i < query_length; i++) {
        std::vector<std::string> segs = get_words<std::string>();
        std::string op = segs.at(0);
        int x = std::stoi(segs.at(1));
        if (op == "union") {
            int y = std::stoi(segs.at(2));
            sol.merge(x, y);
        } else if (op == "count") {
            int res = sol.count(x);
            std::cout << res << '\n';
        }
    }
}
