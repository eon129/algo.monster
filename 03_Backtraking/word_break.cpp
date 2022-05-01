/*
Given a string and a list of words, determine if the string can be constructed from concatenating words from the list of words. A word can be used multiple times.

Input:

s = "algomonster"
words = ["algo", "monster"]
Output: true

Input:

s = "aab"
words = ["a", "c"]
Output: false
*/
#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_map>

int isPartOf1(std::string &currWord, std::string &s)
{
    int countS = 0;
    int result = -1;
    int i;
    
    for (i=0; i<currWord.size(); i++) {
        
        if (i >= s.size() || s[i] != currWord[i]) {
            return -1;
        }
    }
    //std::cout << "pos: " << i<< ",";
    return i;
}

bool _word_break1(std::string s, std::vector<std::string> &words) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if (s.size() == 0) {
        return true;
    }
    
    for (std::string currWord : words) {
        
        int pos = isPartOf1(currWord, s);
        
        if (pos > 0) {
            
            if (_word_break1(s.substr(pos, s.size()-pos), words)) {
                
                return true;
            }
        }
    }
    
    return false;
}

int isPartOf(std::string &currWord, std::string &s, int stringPos)
{
    int countS = 0;
    int result = -1;
    int i;
    
    if (currWord.size() > (s.size() - stringPos)) {
        return -1;
    }
    
    for (i=0; i<currWord.size(); i++) {
        
        if (s[i+stringPos] != currWord[i]) {
            return -1;
        }
    }
    //std::cout << "pos: " << i<< ",";
    return stringPos + i;
}

bool _word_break(std::string &s, int stringPos, std::vector<std::string> &words, std::unordered_map<int, bool> &map) {
    // WRITE YOUR BRILLIANT CODE HERE
    if (s.size() == stringPos) {
        return true;
    }
    
    //If case exists already in map, return it
    if (map.find(stringPos) != map.end()) {
    
        return map[stringPos];
    }
    
    for (std::string currWord : words) {
        
        int newPos = isPartOf(currWord, s, stringPos);
        
        if (newPos > 0) {
            
            if (_word_break(s, newPos, words, map)) {
                
                return true;
            }
        }
    }
    
    //Add use case to map
    map[stringPos] = false;
    
    return false;
}

bool word_break(std::string s, std::vector<std::string> words) {
    // WRITE YOUR BRILLIANT CODE HERE
    
   
    //return _word_break1(s, words);
    
    std::unordered_map<int, bool> map;
    
    return _word_break(s, 0, words, map);
}

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
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
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::string> words = get_words<std::string>();
    bool res = word_break(s, words);
    std::cout << std::boolalpha << res << '\n';
}
