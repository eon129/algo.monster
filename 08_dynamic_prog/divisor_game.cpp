/*
James and Oliver take turns playing a game, with James starting first.

Initially, there is a number N on the chalkboard. On each player's turn, that player makes a move consisting of:

Choosing any x with 0 < x < N and N % x == 0 where 1 <= N <= 1000.
Replacing the number N on the chalkboard with N - x.
Also, if a player cannot make a move, they lose the game.

Return True if and only if James wins the game, assuming both players play optimally.

Example 1:
Input: 2
Output: true
Explanation:
James chooses 1, and Oliver has no more moves.

Example 2:
Input: 3
Output: false
Explanation:
James chooses 1, and Oliver chooses 1, and James has no more moves.
*/


#include <iostream> // boolalpha, cin, cout, streamsize
#include <limits> // numeric_limits

bool divisor_game(int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    bool dp[n+1];
    dp[0] = false;
    dp[1] = false;
    
    //Default condition
    if (n == 1 ) {
        return false;
    }
    
    //All numbers are divisible by 1, so if n - 1 results
    //on False, it means James wins
    if (dp[n - 1] == false) {  
        return true;
    }
    
    for (int i = 2; i<=n; i++) {
        
        bool result = true;
        
        for (int x=1; x<=(n/2); x++) {
            
            // n is divisible by j
            if (i % x == 0) {              
                //Save result using AND so False condition will stay
                result &= dp[i-x];
            }
        }
        
        //Save result at i. Use negation, because it means
        //Next turn will win or lose.
        dp[i] = !result;
    }
    
    return dp[n];
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cin >> n;
    ignore_line();
    bool res = divisor_game(n);
    std::cout << std::boolalpha << res << '\n';
}
