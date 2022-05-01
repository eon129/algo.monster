/*
We have a message to decode. Letters are encoded to digits by their positions in the alphabet

A -> 1
B -> 2
C -> 3
...
Y -> 25
Z -> 26
Given a non-empty string of digits, how many ways are there to decode it?

Input: "18"

Output: 2

Explanation: "18" can be decoded as "AH" or "R"

Input: "123"

Output: 3

Explanation: "123" can be decoded as "ABC", "LC", "AW"
*/
#include <iostream> // cin, cout
#include <string> // getline, string
#include <unordered_map>

bool isCombinationPosible(char c1, char c2) {
    
    //Digit is > 30
    if( (int)c1 > 50) {
        
        return false;
    }
    
    //ditit is > 26
    if( (int)c1 == 50 && (int)c2 > 54) {
        
        return false;
    }
   
    //otherwhise return true
    return true;
}

int _decode_ways(std::string &digits, int pos, std::unordered_map<int, int> &map) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int result = 0;
    
    if (pos == digits.size()) {
        
        return 1;
    } 
    
    //If result is found in map, return it
    if (map.find(pos) != map.end()) {
        return map[pos];
    }
    
    //There is at least 1 digit so send this combination
    result += _decode_ways(digits, pos+1, map);
    
    //If two digit combination is posible
    if (pos+2 <= digits.size() && isCombinationPosible(digits[pos], digits[pos+1])) {
        
        result += _decode_ways(digits, pos+2, map);
    }
    
    map[pos] = result;
    
    return result;
}

int decode_ways(std::string digits) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<int, int> map;
    
    /*std::string s = "hola";
    char c = '1';
    std::cout << (int)c << std::endl;
    return 1;*/
    
    return _decode_ways(digits, 0, map);
}

int main() {
    std::string digits;
    std::getline(std::cin, digits);
    int res = decode_ways(digits);
    std::cout << res << '\n';
}
