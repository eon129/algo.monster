/*
Word Ladder is "a puzzle begins with two words, and to solve the puzzle one must find a chain of other words to link the two, in which two adjacent words (that is, words in successive steps) differ by one letter."

For example: COLD → CORD → CARD → WARD → WARM

Given a start word, an end word, and a list of dictionary words, determine the minimum number of steps to go from the start word to the end word using only words from the dictionary.

Input:

start = "COLD"
end = "WARM"
word_list = ["COLD", "GOLD", "CORD", "SOLD", "CARD", "WARD", "WARM", "TARD"]
Output:

4

Explanation: We can go from COLD to WARM by going through COLD → CORD → CARD → WARD → WARM
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>

bool isAdjacentWord(int s1, int s2, std::vector<std::string> &word_list) {
    
    for (int i=0, count=0; i<word_list[s1].size(); i++) {
        
        if(count > 1) {
            return false;
        }      
        if (word_list[s1][i] != word_list[s2][i]) {
            count++;
        } 
    }
            
    return true;
}

int word_ladder(std::string begin, std::string end, std::vector<std::string> word_list) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //Checar porque se necesita hacer el level +1
    
    std::deque<int> q;
    int visited[word_list.size()];
    int level;
    
    //initialize visited array
    for (int i=0; i<word_list.size(); i++) {
        
        visited[i] = 0;
    }
    
    /*std::cout << "adj " << isAdjacentWord(0, 3, word_list) << " ";
    return 0;*/
    
    q.push_back(0);
    visited[0] = 1;
    level = 1;
    
    while (!q.empty()) {
    
        int n = q.size();
        
        while(n) {
            
            int curr = q.back();
            q.pop_back();
            
            for (int i=0; i<word_list.size(); i++) {
                
                if (!visited[i] && isAdjacentWord(curr, i, word_list)) {
                    
                    if (end.compare(word_list[i]) == 0) {
                        return level+1;
                    }
                   
                    q.push_front(i);
                    visited[i] = 1;
                }
            }           
            n--;
        }
        level++;
    }
    
    /*std::cout << ", ";
    for (int i=0; i<word_list.size(); i++) {
        std::cout << word_list[i] << " ";
    }*/
    
    return -1;
}

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

int main() {
    std::string begin;
    std::getline(std::cin, begin);
    std::string end;
    std::getline(std::cin, end);
    std::vector<std::string> word_list = get_words<std::string>();
    int res = word_ladder(begin, end, word_list);
    std::cout << res << '\n';
}
