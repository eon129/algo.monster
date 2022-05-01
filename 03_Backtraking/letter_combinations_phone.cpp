/*
Given a phone number that contains digits 2-9, find all possible letter combinations the phone number could translate to.

Input:

"56"
Output:

["jm","jn","jo","km","kn","ko","lm","ln","lo"]
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // ostream_iterator, prev
#include <string> // getline, string
#include <vector> // vector

std::vector<std::string> find_combinations_until(std::vector<std::string> &letters, std::string currPath, int level) {
    
    std::vector<std::string> result, temp;
    
    
    if (level < letters.size()) {
        
        std::string currentString = letters[level];
        
        for (int i = 0; i < currentString.size(); i++) {

            temp = find_combinations_until(letters, currPath + currentString[i], level+1);
            result.insert(std::end(result), std::begin(temp), std::end(temp));
        }
        
    } else {
        result = {currPath};
    }

    return result;
}

std::vector<std::string> letter_combinations_of_phone_number(std::string digits) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::vector<std::string> directory = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "xyz"};
    std::vector<std::string> letters;
    
    for (int i=0; i<digits.size(); i++) {
        
        //Convert char to int for index
        letters.push_back(directory[(int)(digits[i] - 48)]);
    }
    
    return find_combinations_until(letters, "", 0);
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
    std::string digits;
    std::getline(std::cin, digits);
    std::vector<std::string> res = letter_combinations_of_phone_number(digits);
    put_words(res);
}
