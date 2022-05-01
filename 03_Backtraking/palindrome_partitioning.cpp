/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

Examples
Example 1:
Input: aab
Output:
  [
  ["aa","b"],
  ["a","a","b"]
  ]
  */

  #include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // ostream_iterator, prev
#include <string> // getline, string
#include <vector> // vector

bool isPalindrome(std::string &s, int l, int r) {

    for (int i=l, j=r; i<j; i++, j--) {
        
        if (s[i] != s[j]) {
            
            return false;
        }
    }
    
    return true;
}

std::vector<std::vector<std::string>> _partition(std::string &s, int pos, std::vector<std::string> currPath) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::vector<std::vector<std::string>> result, tempV;
    
    if (pos == s.size()) {
        
        result.push_back(currPath);
        return result;
    }
    
    for (int i=pos; i<s.size(); i++) {
        
        if (isPalindrome(s, pos, i)) {
            
            std::vector<std::string> tempS = currPath;
            
            tempS.push_back(s.substr(pos, i+1-pos)); 
         
            tempV = _partition(s, i+1, tempS);       
            result.insert(std::end(result), std::begin(tempV), std::end(tempV));
        }
    }
  
    return result;
}

std::vector<std::vector<std::string>> partition(std::string s) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    return _partition(s, 0, {});
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
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::vector<std::string>> res = partition(s);
    for (const std::vector<std::string>& row : res) {
        put_words(row);
    }
}
