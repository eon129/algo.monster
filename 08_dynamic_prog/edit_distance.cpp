/*
There are two words word1 and word2, you have to find the minimum number of operations required to convert word1 to word2.

You are allowed to use the following 3 operations on a word:

Insert a character
Delete a character
Replace a character
Example 1:
Input:
word1 = "almost"
word2 = "algomonster"
Output:5
Explanation:
almost    ->  algmost    (insert 'g')
algmost   ->  algomost   (insert 'o')
algomost  ->  algmonst   (insert 'n')
algomonst ->  algomoste  (insert 'e')
algomoste ->  algomoster (insert 'r')
Example 2:
Input:
  word1 = "intention"
  word2 = "execution"
Output:5
Explanation:
intention  ->  inention   (remove 't')
inention   ->  enention   (replace 'i' with 'e')
enention   ->  exention   (replace 'n' with 'x')
exention   ->  exection   (replace 'n' with 'c')
exection   ->  execution  (insert 'u')
*/
#include <iostream> // cin, cout
#include <string> // getline, string
#include <vector>

int top_down(std::string &word1, std::string &word2, int idx_w1, int idx_w2, std::vector<std::vector<int>> &memo) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //Return value if already calculated and saved in memo
    if (memo[idx_w1][idx_w2] != 0) {
        return memo[idx_w1][idx_w2];
    }
    
    //At the end of word1, return insertion operations needed from word2
    if(idx_w1 == word1.size()) {
        memo[idx_w1][idx_w2] = word2.size() - idx_w2;
        return memo[idx_w1][idx_w2];
    }
    //At the end of word2, return deletion operations needed to match
    if(idx_w2 == word2.size()) {
        
        memo[idx_w1][idx_w2] = word1.size() - idx_w1;
        return memo[idx_w1][idx_w2];
    }
    
    if (word1[idx_w1] == word2[idx_w2]) {
        
        memo[idx_w1][idx_w2] = top_down(word1, word2, idx_w1+1, idx_w2+1, memo);
        return memo[idx_w1][idx_w2];
    } else {
    
        memo[idx_w1][idx_w2] = 1 + std::min(
            //replace
            top_down(word1, word2, idx_w1+1, idx_w2+1, memo),
            std::min(
                //insert
                top_down(word1, word2, idx_w1, idx_w2+1, memo),
                //remove
                top_down(word1, word2, idx_w1+1, idx_w2, memo)
            )
        );
        
        return memo[idx_w1][idx_w2];
    }
}

int min_distance(std::string word1, std::string word2) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int max = std::max(word1.size(), word2.size()) + 1;
    std::vector<std::vector<int>> memo(max, std::vector<int>(max));
    
    for (int i=0; i<max; i++) {
        for (int j=0; j<max; j++) {
        
            memo[i][j] = 0;
        }
    }
    
    
    return top_down(word1, word2, 0, 0, memo);
}

int main() {
    std::string word1;
    std::getline(std::cin, word1);
    std::string word2;
    std::getline(std::cin, word2);
    int res = min_distance(word1, word2);
    std::cout << res << '\n';
}
