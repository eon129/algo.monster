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
        //In boundary problems, the rule is to include the equals(=) comparation, this will give the true (T) elements.
        //Result has to be in the boundary between F and T, but in the T element
        //T cases can be in the left or right side of the list, it affects in the way l and r are 
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
