/*
Given a string original and a string check, find the starting index of all substrings of original that is an anagram of check. The output must be sorted in ascending order.

Parameters
original: A string
check: A string
Result
A list of integers representing the starting indices of all anagrams of check.
Examples
Example 1
Input: original = "cbaebabacd", check = "abc"

Output: [0, 6]

Explanation: The substring from 0 to 2, "cba", is an anagram of "abc", and so is the substring from 6 to 8, "bac".

Example 2
Input: original = "abab", check = "ab"

Output: [0, 1, 2]

Explanation: All substrings with length 2 from "abab" is an anagram of "ab".

Constraints
1 <= len(original), len(check) <= 10^5
Each string consists of only lowercase characters in standard English alphabet.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // ostream_iterator, prev
#include <string> // getline, string
#include <vector> // vector
#include <unordered_set>
#include <unordered_map>


void reset_window(std::unordered_map<char, int> &check_map, std::unordered_map<char, int> &window_map) {
    
    for(auto elem : check_map) {
    
        window_map[elem.first] = elem.second;
    }
}

std::vector<int> find_all_anagrams(std::string original, std::string check) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<char, int> check_map, window_map;
    std::pair<std::unordered_set<char>::iterator, bool> insert_res;
    int check_size;
    int slow, fast, count;
    std::vector<int> result;
    
    //Build check set
    for(int i=0; i<check.size(); i++) {
        //Element not found in map initialize with 1
        if (check_map.find(check[i]) == check_map.end()) {
            check_map[check[i]] = 1;
            window_map[check[i]] = 1;
        } else {
            check_map[check[i]]++;
            window_map[check[i]]++;
        }
    }
    
    check_size = check_map.size();
    
    /*for (auto elem : check_map) {
        std::cout << elem.first << ": " << elem.second << ", ";
    }
    
    return {};*/
    
    slow = fast = count = 0;
    
    //First loop to move window step by step
    while(slow <= (original.size() - check_size)) {
        
        //std::cout << "f: " << fast << ", c: " << count << ", ";
        
        //If element is found in check
        if (window_map.find(original[fast]) != window_map.end()) {
            
            window_map[original[fast]]--;
            
            //Check from map if we have
            if ( window_map[original[fast]] == 0) {
                count++;
            } else if ( window_map[original[fast]] < 0) {
                //Element is duplicated in current window
                reset_window(check_map, window_map);
                count = 0;
                slow++;
                fast = slow;
                continue;
            } else {
            
            }
            
            if (count == check_size) {
                //anagram found
                result.push_back(slow);
                //Reset window map
                reset_window(check_map, window_map);
                //window_set.insert(original[fast]);
                count = 0;
                slow++;
                fast = slow;
            } else {
                fast++;
            }
            
        } else {
            //element not found in check
            reset_window(check_map, window_map);
            count = 0;
            slow++;
            fast = slow;
        }       
    }
    
    return result;
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
    std::string original;
    std::getline(std::cin, original);
    std::string check;
    std::getline(std::cin, check);
    std::vector<int> res = find_all_anagrams(original, check);
    put_words(res);
}
