/*
Given two strings word1 and word2, return the length of their longest common subsequence.

A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings is a subsequence that is common to both strings.

If there is no common subsequence, return 0.
Example 1:
Input:

word1 = "abcde"

word2 = "ace"

Output: 3
Explanation:

The longest common subsequence is ace and its length is 3.
Example 2:
Input:

word1 = "almost"

word2 = "algomonster"

Output: 6
Explanation:

The longest common subsequence is almost and its length is 6.
Example 3:
Input:

word1 = "abc"

word2 = "def"

Output: 0
Explanation:

There is no such common subsequence, so the result is 0.
*/

#include <iostream> // cin, cout
#include <string> // getline, string

int getOccurenceIndex(std::string &s, char c) {
    
    for (int i=0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    
    return -1;
}

int longest_common_subsequence(std::string word1, std::string word2) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //first is count, second is index
    std::pair<int, int> dp[word1.size()];
    int globalMax = 0;
    
    for (int i=0; i<word1.size(); i++) {
        
        int index = getOccurenceIndex(word2, word1[i]);
        if ( index == -1) {
            dp[i].first = 0;
            dp[i].second = -1;
        } else {
            int max=0;
            dp[i].second = index;
            for(int j=0; j<i; j++) {

                if (dp[j].second < index) {
                    max = (dp[j].first > max) ? dp[j].first : max; 
                }
            }
            
            dp[i].first = max + 1;
            
            globalMax = (dp[i].first > globalMax) ? dp[i].first : globalMax;
        }
    }
    
    return globalMax;
}

int main() {
    std::string word1;
    std::getline(std::cin, word1);
    std::string word2;
    std::getline(std::cin, word2);
    int res = longest_common_subsequence(word1, word2);
    std::cout << res << '\n';
}