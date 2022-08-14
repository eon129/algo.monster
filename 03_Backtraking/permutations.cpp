/*
Permutations
Given a string of unique letters, find all of its distinct permutations.

Input
letters: a string of unique letters
Output
all of its distinct permutations

Examples
Example 1:
Input:

letters = `abc`
Output: ```` abc acb bac bca cab cba
*/

#include <iostream> // cin, cout
#include <string> // getline, string
#include <vector> // vector
#include <stack>

std::vector<std::string> _permutations_it(std::string letters) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::vector<std::string> result;
    std::stack<std::string> letterS, currPathS;
    
    letterS.push(letters);
    currPathS.push("");
    
    while (!letterS.empty()) {
        
        std::string currString = letterS.top();
        letterS.pop();
        std::string currPath = currPathS.top();
        currPathS.pop();
        
        if (currString.length() > 1) {
            
            for(int i = currString.size()-1; i>= 0; i--) {
                
                std::string tempString = currString;
                
                letterS.push(tempString.erase(i, 1));
                currPathS.push(currPath + currString[i]);
            }
        } else {
            
            result.push_back(currPath + currString[0]);
        }      
    }
    
    return result;
}

std::vector<std::string> _permutations(std::string letters, std::string currPath) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::vector<std::string> result, temp;
    //std::cout << "letters: " << letters << std::endl; 
    
    if (letters.length() > 1) {
        
        for (int i=0; i < letters.length(); i++) {
            //First make a copy of the original string, so in every loop
            //we remove only one character
            std::string tempString = letters;
            
            //This erase function works on contiguos memory it might take a lot of time
            //Preferably use linked list
            temp = _permutations(tempString.erase(i, 1), currPath + letters[i]);
            result.insert(std::end(result), std::begin(temp), std::end(temp));
        }
        
        return result;
    }
    
    return {currPath + letters[0]};
}

void _permutations_with_masking(std::string &letters, std::string currPath, int mask, std::vector<std::string> &res) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //All characters has been used
    if ((1 << letters.size()) == mask + 1) {
        //Concatenate result
        res.emplace_back(currPath);
        return;
    }
    
    for (int i=0; i < letters.length(); i++) {      
        //Character is not used yet
        if (!((1<<i) & mask)) {           
            //Concatenation of string might be optimized
            _permutations_with_masking(letters, currPath + letters[i], ((1<<i) | mask), res);
        }
    }
}

std::vector<std::string> permutations(std::string letters) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //return _permutations_it(letters);
    //return _permutations(letters, "");
    
    std::vector<std::string> res;
    _permutations_with_masking(letters, "", 0, res);
    return res;
    
}

int main() {
    std::string letters;
    std::getline(std::cin, letters);
    std::vector<std::string> res = permutations(letters);
    for (const std::string& line : res) {
        std::cout << line << '\n';
    }
}