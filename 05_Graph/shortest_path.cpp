/*
Given an (unweighted) graph, return the length of the shortest path between two nodes A and B, in terms of the number of edges.

Input:

graph: {
  0: [1, 2],
  1: [0, 2, 3],
  2: [0, 1],
  3: [1]
}
A: 0
B: 3
Output: 2
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <unordered_set>

int shortest_path(std::vector<std::vector<int>> graph, int r, int c) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::deque<int> q;
    std::unordered_set<int> visited;
    int level = 0;
    
    q.push_back(r);
    visited.insert(r);
    
    while (!q.empty()) {
    
        int n = q.size();
        
        while(n) {
            
            int curr = q.back();
            q.pop_back();

            std::vector<int> currVertex = graph[curr];
            
            for(int i=0; i<currVertex.size(); i++) {
                
                //vertex found
                if (currVertex[i] == c) {
                   
                    return level+1;
                }
             
                if(visited.find(currVertex[i]) == visited.end()) {
                    q.push_front(currVertex[i]);
                    visited.insert(currVertex[i]);
                }
            }       
            n--;
        }      
        level++;
    }
    
    return 0;
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
    int graph_length;
    std::cin >> graph_length;
    ignore_line();
    std::vector<std::vector<int>> graph;
    for (int i = 0; i < graph_length; i++) {
        graph.emplace_back(get_words<int>());
    }
    int r;
    std::cin >> r;
    ignore_line();
    int c;
    std::cin >> c;
    ignore_line();
    int res = shortest_path(graph, r, c);
    std::cout << res << '\n';
}
