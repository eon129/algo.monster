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

int top_down(std::string &word1, std::string &word2, int idx_w1, int idx_w2) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if(idx_w1 >= word1.size() && idx_w2 >= word2.size()) {
        return 0;
    }
    
    if (idx_w1 < word1.size() && idx_w2 < word2.size() && word1[idx_w1] == word2[idx_w2]) {
        
        return top_down(word1, word2, idx_w1+1, idx_w2+1);
    } else {
    
        return 1 + std::min(
            //replace
            top_down(word1, word2, idx_w1+1, idx_w2+1),
            std::min(
                //insert
                top_down(word1, word2, idx_w1, idx_w2+1),
                //remove
                top_down(word1, word2, idx_w1+1, idx_w2)
            )
        );
    }
}

int min_distance(std::string word1, std::string word2) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    return top_down(word1, word2, 0, 0);
}

int main() {
    std::string word1;
    std::getline(std::cin, word1);
    std::string word2;
    std::getline(std::cin, word2);
    int res = min_distance(word1, word2);
    std::cout << res << '\n';
}
