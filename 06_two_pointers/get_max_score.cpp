/*
You are given two sorted arrays of distinct integers, arr1, and arr2. Your goal is to start from the beginning of one array, and arrive to the end of one array (it could be the same array or not).

For each step, you can either move forward a step on an array, or move to a square in the other array where the number is the same as the number in your current square ("teleport"). Your total score is defined as the sum of all unique numbers that you have been on.

Find the maximum score that you can get given the above rules. Since the result might be very large and cause overflow, return the maximum score modded by 10^9 + 7.

Parameters
arr1: A list of ordered, distinct integers.
arr2: Another list of ordered, distinct integers.
Result
The maximum score possible, modded by 10^9 + 7.
Examples
Example 1
Input: arr1 = [2, 4, 5, 8, 10], arr2 = [4, 6, 8, 9]

Output: 30
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int maximum_score(std::vector<int> arr1, std::vector<int> arr2) {
    // WRITE YOUR BRILLIANT CODE HERE
    int ptr1, ptr2, len1, len2;
    int MODULO_AMT = 1000000007;
    long long result, seg1, seg2;
    
    result = 0;
    ptr1 = 0;
    ptr2 = 0;
    seg1 = 0;
    seg2 = 0;
    len1 = arr1.size();
    len2 = arr2.size();
    
    while (ptr1 < len1 || ptr2 < len2) {
        
        if ((ptr1<len1 && ptr2<len2) && arr1[ptr1] == arr2[ptr2]) {
            
            //Sum to result the max segment and current position
            result += std::max(seg1, seg2) + arr1[ptr1];
            result %= MODULO_AMT;
            seg1=0;
            seg2=0;
            ptr1++;
            ptr2++;
            
            continue;
        }
        
        //Falta checar cuando estamos al final de la lista
        //Y el otro ya termino
        if (ptr2 == len2 || (ptr1 < len1 && arr1[ptr1] < arr2[ptr2])) {
            
            seg1+= arr1[ptr1];
            ptr1++;
            continue;
        } else {
            
            seg2+= arr2[ptr2];
            ptr2++;
        }
    }
    
    result += std::max(seg1, seg2);
    
    return result % MODULO_AMT;
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
    std::vector<int> arr1 = get_words<int>();
    std::vector<int> arr2 = get_words<int>();
    int res = maximum_score(arr1, arr2);
    std::cout << res << '\n';
}
