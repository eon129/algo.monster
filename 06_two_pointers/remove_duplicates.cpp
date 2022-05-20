/*
Given a sorted list of numbers, remove duplicates and return the new length. You must do this in-place and without using extra memory.

Input: [0, 0, 1, 1, 1, 2, 2].

Your function should modify the list in place so the first 3 elements becomes 0, 1, 2.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int remove_duplicates(std::vector<int>& arr) {
    // WRITE YOUR BRILLIANT CODE HERE
    int fast_i, slow_i;
    
    for (slow_i = 0, fast_i = 0; fast_i < arr.size(); fast_i++) {
        
        if (arr[slow_i] != arr[fast_i]) {
            //Increment slow index
            slow_i++;
            //Update value
            arr[slow_i] = arr[fast_i];        
        }
    }
    
    return slow_i+1;
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
    std::vector<int> arr = get_words<int>();
    int res = remove_duplicates(arr);
    arr.resize(res);
    put_words(arr);
}
