/*
A sorted array was rotated at an unknown pivot. For example, [10, 20, 30, 40, 50] becomes [30, 40, 50, 10, 20]. Find the index of the minimum element in this array.

Return the minimum index if the minimum number is repeated.

Input: [30, 40, 50, 10, 20]

Output: 3

Explanation: the smallest element is 10 and its index is 3.

Input: [3, 5, 7, 11, 13, 17, 19, 2]

Output: 7

Explanation: the smallest element is 2 and its index is 7.
*/
#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int find_min_rotated(std::vector<int> arr) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int l = 0;
    int r = arr.size() - 1;
    int boundary = 0;
    int last = r;
    
    while (l <= r)
    {
        int m = (l + r) / 2;
        
        if (arr[m] > arr[last]) {
            
            l = m + 1;
        } else {
            boundary = m;
            r = m -1;
        }
    }
    return boundary;
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
    std::vector<int> arr = get_words<int>();
    int res = find_min_rotated(arr);
    std::cout << res << '\n';
}
