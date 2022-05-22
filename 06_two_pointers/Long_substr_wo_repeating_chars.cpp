/*
Find the length of the longest substring of a given string without repeating characters.

Input: abccabcabcc

Output: 3

Explanation: longest substrings are abc, cab, both of length 3

Input: aaaabaaa

Output: 2

Explanation: ab is the longest substring, length 2
*/
#include <iostream> // cin, cout
#include <string> // getline, string
#include <unordered_set>

int longest_substring_without_repeating_characters(std::string s) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_set<char> repeated;
    int slow=0, fast=0, max=0;
    
    while(fast < s.size()) {
    
        if(repeated.find(s[fast]) == repeated.end()) {
            repeated.insert(s[fast]);
            fast++;
        } else {
            max = (max > (fast-slow))? max : (fast-slow);
            repeated.erase(s[slow]);
            slow++;
        }
    } 
    max = (max > (fast-slow))? max : (fast-slow);
    
    return max;
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    int res = longest_substring_without_repeating_characters(s);
    std::cout << res << '\n';
}
