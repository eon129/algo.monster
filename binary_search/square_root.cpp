/*
Given an integer, find its square root without using the built-in square root function. Only return the integer part (truncate the decimals).

Input: 16

Output: 4

Input: 8

Output: 2

Explanation: square root of 8 is 2.83..., return integer part 2
*/
#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits

int square_root(int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int l = 0;
    int r = n - 1;
    int boundary = -1;
    
    while (l <= r)
    {
        int m = (l + r) / 2;
        
        if ( n >= (m*m) ) {
            
            boundary = m;
            l = m+1;     
        } else {
            
            r = m-1;
        }
    }
    
    return boundary;
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cin >> n;
    ignore_line();
    int res = square_root(n);
    std::cout << res << '\n';
}
