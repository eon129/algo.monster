/*
An array of boolean values is divided into two sections; the left section consists of all false and the right section consists of all true. Find the boundary of the right section, i.e. the index of the first true element. If there is no true element, return -1.

Input: arr = [false, false, true, true, true]

Output: 2

Explanation: first true's index is 2.
*/
#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int find_boundary(std::vector<bool> arr) {
    
    int l, r, m, t;
    
    l = 0;
    r = arr.size()-1;
    t = r;
    
    if (arr.size() == 1 && arr.at(0) == true) {
        return 0;
    } else if (arr.size() == 2 && arr.at(0) == false && arr.at(1) == true) {
        return 1;
    } else{}
    
    while (l <= r) {
        
        m = (l+r)/2;
    
        if (arr.at(m) == true) {
            if ((m-1)>=0 && arr.at(m-1) == false) {
                
                return m;
            } 
            
            r = m - 1;
        } else {
            if ((m+1)<=t && arr.at(m+1) == true) {
                
                return m;
            }
            
            l = m + 1;
        }
    }
    
    if (arr.at(0) == true) {
        return 0;
    }
        
    return -1;
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<bool> arr;
    bool b;
    while (ss >> std::boolalpha >> b) {
        arr.push_back(b);
    }
    int res = find_boundary(arr);
    std::cout << res << '\n';
}
