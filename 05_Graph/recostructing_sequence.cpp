/*
Check whether the original sequence original can be uniquely reconstructed from the sequences in seqs.

The original sequence is a permutation of the integers from 1 to n.

Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it).

Determine whether there is only one sequence that can be reconstructed from seqs and it is the orginal sequence.

Parameters
original: A list of integers of size n representing the original sequence.
seqs: A list of sequences of size m representing the sequences to be reconstructed.
Result
true or false, depending on whether the original sequence can be uniquely reconstructed.
Examples
Example 1:
Input: orgignal: [1,2,3], seqs: [[1,2], [1,3]]

Output: false

Explanation:

[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.

Example 2:
Input: orgignal: [1,2,3], seqs: [[1,2]]

Output: false

Explanation:

The reconstructed sequence can only be [1,2].

Example 3:
Input: orginal: [1,2,3], seqs: [[1,2], [1,3], [2,3]]

Output: true

Explanation:

The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].

Example 4:
Input: orgignal: [4,1,5,2,6,3], seqs: [[5,2,6,3], [4,1,5,2]]

Output: true
*/

#include <algorithm> // copy
#include <iostream> // boolalpha, cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <unordered_map>
#include <set>

bool sequence_reconstruction(std::vector<int> original, std::vector<std::vector<int>> seqs) {
    // WRITE YOUR BRILLIANT CODE HERE
       
    std::unordered_map<int, std::set<int>> graph;
    std::unordered_map<int, int> parent_count;
    std::vector<int> reconstruction;
    std::deque<int> q;
    bool result = true;
    
    //Building graph from sequences
    for(int s=0; s < seqs.size(); s++) {
      
        int e;
        //Start in 1, so we can check parent->child relation with index e-1 -> e
        for (e=1; e < seqs[s].size(); e++) {
        
            //Build graph
            graph[seqs[s][e-1]].insert(seqs[s][e]);
            //initialize parent count
            parent_count[seqs[s][e-1]] = 0;
        }
        
        //Check if last element on squence already exists
        //otherwise insert an empty set
        if(graph.find(seqs[s][e-1]) == graph.end()) {
            
            graph[seqs[s][e-1]] = {};
            //initialize parent_count in last element of sequence
            parent_count[seqs[s][e-1]] = 0;
        }
    }
    
    //Build paret_count map.
    for (auto list : graph) { 
        
        for (auto node : list.second) {
            parent_count[node]++;            
        }
    }
        
    //Add to queue elements with parent_count 0
    for (auto node : parent_count) {     
        if(node.second == 0) {
            
            q.push_back(node.first);
        }
    }
    
    while(!q.empty()) {
    
        int n = q.size();
        
        //if in some level there are more than one node in the queue with parent_count 0, this mean
        //we wont have a unique recostruction
        if (n > 1) {
            result = false;
            break;
        }
        
        int curr = q.back();
        q.pop_back();
        
        reconstruction.push_back(curr);
        
        for(int element : graph[curr]) {
            
            parent_count[element] --;
            
            if (parent_count[element] == 0) {
                q.push_front(element);
            }
        }
    }
    
    //Check if original can be described with sequences
    if(result && (reconstruction != original)) {
        result = false;
    }
    
    return result;
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

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::vector<int> original = get_words<int>();
    int seqs_length;
    std::cin >> seqs_length;
    ignore_line();
    std::vector<std::vector<int>> seqs;
    for (int i = 0; i < seqs_length; i++) {
        seqs.emplace_back(get_words<int>());
    }
    bool res = sequence_reconstruction(original, seqs);
    std::cout << std::boolalpha << res << '\n';
}
