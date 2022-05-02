/*
You commissioned a locksmith to craft a special combination lock for you, because you are a lich and you want to hide your phylactery in somewhere secure. It looks like a regular 4-digit combination lock, with each digit can be one of the digits from 0~9. Each digit can be turned forwards by 1 and backwards by 1, and the first and the last digit is connected (9 goes to 0 when moving forward, and 0 goes to 9 when moving backward). The lock starts at 0000.

However, because you don't want people to find your phylactery, you have trapped certain combinations of this combination lock. If someone were to set the combination to a trapped combination, bad things happen to them, which this question would not elaborate upon.

You know the combination, and you know the trapped combinations. You wonder if the lock can be opened without triggering the traps, and if so, how many digit changes must be made to the lock to unlock it.

Input
combo: a string representing the four digit combination to open the lock.
trapped_combos: a list of strings representing the trapped combinations.
Output
An integer representing the number of steps it takes to open the lock, or -1 if you can't open it without triggering the trap.

Examples
Example 1:
Input:

combo = "0202"
trapped_combos = ["0201","0101","0102","1212","2002"]
Output: 6

Explanation:

0000 -> 1000 -> 1100 -> 1200 -> 1201 -> 1202 -> 0202, a total of 6 steps.

Constraints
The starting combination (0000) and the final combination is not trapped because that defeats the purpose of the lock.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <unordered_set>

std::string getCombination(std::string curr, int i, int n)
{
    //0 is 48
    //9 is 57
    
    if (n == 1 && (int)curr[i] == 57) {    
        curr[i] = '0'; 
        return curr;
    }
    
    if (n == -1 && (int)curr[i] == 48) {    
        curr[i] = '9';  
        return curr;
    }
    
    curr[i] = curr[i] + n;
    
    return curr;
}

bool isATrap(std::string &combo, std::vector<std::string> &trapped_combos) 
{
    for (int i=0; i<trapped_combos.size(); i++) {
    
        if ( combo.compare(trapped_combos[i]) == 0) {
            
            return true;
        }
    }
    
    return false;
}

int num_steps(std::string combo, std::vector<std::string> trapped_combos) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::deque<std::string> q;
    std::unordered_set<std::string> visited;
    int step;
    
    if (combo.compare("0000") == 0) {
        return 0;
    }
    
    q.push_back("0000");
    visited.insert("0000");
    
    step = 1;
    
    while (!q.empty()) {
        
        int n = q.size();
        
        while(n) {
    
            std::string curr = q.back();
            q.pop_back();

            for (int i=0; i < 4; i++) {
            
                //Check for combination +1 in position i
                std::string comb1 = getCombination(curr, i, 1);
                
                if (combo.compare(comb1) == 0) {
                    return step;
                }
                
                //Check for combination -1 in position i
                std::string comb2 = getCombination(curr, i, -1);
                
                if (combo.compare(comb2) == 0) {
                    return step;
                }
                
                //If combinations are not a trap, enqueue it
                if ( visited.find(comb1) == visited.end() && !isATrap(comb1, trapped_combos) ) {
                    q.push_front(comb1);
                    visited.insert(comb1);
                }              
                if ( visited.find(comb2) == visited.end() && !isATrap(comb2, trapped_combos) ) {
                    q.push_front(comb2);
                    visited.insert(comb2);
                }
            }
            n--;
        } 
        step++;
    }
    
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
    std::string combo;
    std::getline(std::cin, combo);
    std::vector<std::string> trapped_combos = get_words<std::string>();
    int res = num_steps(combo, trapped_combos);
    std::cout << res << '\n';
}
