/*
Output the minimum cost to traverse every node in a directed weighted graph. The graph will be in the form of a 2D list where element [i,j] in the array denotes the weight of the directed edge from i to j. If the value is 0 then the edge doesn't exist. You do not have to end at the starting node. All edges are guaranteed to be in the range [0,1000], there will not exceed 15 nodes in the graph. The starting node will always be at node 0. If a solution does not exist return -1.

Example:
Input:

Output:
3
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int solution_1(std::vector<std::vector<int>> &graph, int node, int visited) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //This value has to be large enough, but not that large.
    //When a path doesn't visit every node, all previous edge values
    //will be sumed up to this value, so it can't overflow.
    //If a graph has no posible result, this value will be the smaller.
    int result = 0x3f3f3f3f;
    
    //All nodes already visited
    if (visited == (1 << graph.size()) -1) {
        return 0;
    }
    
    //Iterate over all nodes
    //if some path can't reach any other node, but we arent visited all nodes
    // 0x3f3f3f3f value will be returned
    for (int j=0; j<graph.size(); j++) {
        
        if (graph[node][j] != 0 && !(visited & (1 << j))) {            
            result = std::min(result, solution_1(graph, j, visited | (1 << j)) + graph[node][j]);                                   
        }
    }
    
    return result;
}

int solution_2_dp(std::vector<std::vector<int>> &graph, int node, int visited, std::vector<std::vector<int>> &dp) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //This value has to be large enough, but not that large.
    //When a path doesn't visit every node, all previous edge values
    //will be sumed up to this value, so it can't overflow.
    //If a graph has no posible result, this value will be the smaller.
    int result = 0x3f3f3f3f;
    
    //All nodes already visited
    if (visited == (1 << graph.size()) -1) {
        return 0;
    }
    
    if (dp[visited][node] != 0) {
        return dp[visited][node];
    }
    
    //Iterate over all nodes
    //if some path can't reach any other node, but we arent visited all nodes
    // 0x3f3f3f3f value will be returned
    for (int j=0; j<graph.size(); j++) {
        
        if (graph[node][j] != 0 && !(visited & (1 << j))) {            
            result = std::min(result, solution_2_dp(graph, j, visited | (1 << j), dp) + graph[node][j]);                                   
        }
    }
    
    return dp[visited][node] = result;
}

int min_cost_to_visit_every_node(std::vector<std::vector<int>> graph) {
    // WRITE YOUR BRILLIANT CODE HERE
    //std::vector<std::vector<bool>> visited(graph.size(), std::vector<bool>(graph.size(), false));
    //int res = solution_1(graph, 0, 1);
    std::vector<std::vector<int>> dp(1 << graph.size(), std::vector<int>(graph.size()));
    int res = solution_2_dp(graph, 0, 1, dp); 
    return (res == 0x3f3f3f3f) ? -1 : res;
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
    int res = min_cost_to_visit_every_node(graph);
    std::cout << res << '\n';
}