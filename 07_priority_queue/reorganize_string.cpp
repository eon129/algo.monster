/*
Given a string s, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result. If not possible, return the empty string.

Example 1:
Input:s = "aab"
Output: aba
Example 2:
Input:s = "aaab"
Output: ``
Note:
s will consist of lowercase letters and have length in range [1, 500].
*/

#include <iostream> // cin, cout
#include <string> // getline, string
#include <queue>
#include <unordered_map>

std::vector<std::pair<int, char>> count_characters(std::string &s) {
    
    std::vector<std::pair<int, char>> result;
    std::unordered_map<char, int> map;
       
    for(int i=0; i<s.size(); i++) {
      
        if (map.find(s[i]) == map.end()) {
            map[s[i]] = 0; 
        }
        map[s[i]]++;
    }
    
    for(auto elem : map) {   
        result.push_back(std::make_pair(elem.second, elem.first));
    }
    
    return result;
}

std::string reorganize_string(std::string s) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::string result = s;
    int index;
    bool odds;
    
    //First buld a vector of pairs consisting on "char, count"
    auto count_c = count_characters(s);
    
    //Build a heap, so we have the character that repeats most at the begining
    std::make_heap(count_c.begin(), count_c.end());
    
    //initialize index value
    index = 0;
    odds = false;
    while(!count_c.empty()) {
    
        auto curr_elem = count_c.front();
        
        pop_heap(count_c.begin(), count_c.end());
        count_c.pop_back();
        
        for(int i=0; i<curr_elem.first; i++) {
            
            //Chars can't be accomodated
            if( index  >= s.size()) {
                return "Impossible";
            }
        
            result[index] = curr_elem.second;
            
            index+=2;
        }
        //We finished with even spaces, go to odds
        if (!odds && index >= s.size()) {
            odds = true;
            index = 1;
        }      
    }
    
    //std::cout << result;
    
    return "Valid";
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::string res = reorganize_string(s);
    std::cout << res << '\n';
}
