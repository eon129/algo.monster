/*
Determine whether a string is a palindrome, ignoring non-alphanumeric characters and case. Examples:

Input: Do geese see God? Output: True

Input: Was it a car or a cat I saw? Output: True

Input: A brown fox jumping over Output: False
*/

#include <iostream> // boolalpha, cin, cout
#include <string> // getline, string
#include <algorithm>

void lowerString(std::string &s) {

    std::for_each(s.begin(), s.end(), [](char & c){
        c = ::tolower(c);
    });
}

void updateIndexIfNecesary(int &i, int side, std::string &s) {

    if ((int)s[i]>=97 && (int)s[i]<=122) {
        return;
    }
    
    int c; 
    c = (side == 1)? 1 : -1;
    
    while ((int)s[i]<97 || (int)s[i]>122) {
        
        i = i + c;
    }
}

bool is_palindrome(std::string s) {
    // WRITE YOUR BRILLIANT CODE HERE
    int left, right;
    
    //std::cout << (int) 'a';
    //return false;
    
    lowerString(s);
    
    for(left=0, right=s.size()-1; left<right; left++, right--) {
        
        updateIndexIfNecesary(left, 1, s);
        updateIndexIfNecesary(right, 0, s);
        
        if (s[left] != s[right]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    bool res = is_palindrome(s);
    std::cout << std::boolalpha << res << '\n';
}
