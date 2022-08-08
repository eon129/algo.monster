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

//This solution avoids creating copies of the letters array
std::vector<std::string> _permutations_2(std::string letters, std::string currPath, std::vector<bool> visited) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if (currPath.size() == letters.size()) {
        
        return {currPath};
    }
    
    std::vector<std::string> result, temp;
    
      
    for (int i=0; i < letters.length(); i++) {
            
        //Skip char if already visited
        if (visited[i] == true) {
            continue;
        }
            
        //Set current position to already visited so in next fuction call
        // it will be omited
        visited[i] = true;
            
        temp = _permutations_2(letters, currPath + letters[i], visited);
        result.insert(std::end(result), std::begin(temp), std::end(temp));
            
        //Set it to not visited again so we can have all te combinations
        visited[i] = false;
    }
     
    
    return result;
}

std::vector<std::string> permutations(std::string letters) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //return _permutations_it(letters);
    //return _permutations(letters, "");
    std::vector<bool> visited(letters.size(), false);
    return _permutations_2(letters, "", visited);
}

int main() {
    std::string letters;
    std::getline(std::cin, letters);
    std::vector<std::string> res = permutations(letters);
    for (const std::string& line : res) {
        std::cout << line << '\n';
    }
}
