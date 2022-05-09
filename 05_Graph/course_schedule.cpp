/*
There are a total of n courses a student has to take, numbered from 0 to n-1. A course may have prerequisites. The "depends on" relationship is expressed as a pair of numbers. For example, [0, 1] means you need to take course 1 before taking course 0. Given n and the list of prerequisites, decide if it is possible to take all the courses.

Example 1:

Input: n = 2, prerequisites = [[0, 1]]

Output: true

Explanation: we can take 1 first and then 0.

Example 2:

Input: n = 2, prerequisites = [[0, 1], [1, 0]]

Output: false

Explanation: the two courses depend on each other, there is no way to take them
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

bool is_valid_course_schedule_BFS(int n, std::vector<std::vector<int>> prerequisites) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::unordered_map<int, std::vector<int>> graph;
    std::deque<int> q;
    std::unordered_map<int, int> parent_count;
    int visited_count = 0;
    
    //Build graph using prerequisites pairs
    for(int i=0; i<prerequisites.size(); i++) {
        
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
        parent_count[prerequisites[i][0]] = 0;
        parent_count[prerequisites[i][1]] = 0;
    }
    //Build parent count
    for(auto elem : graph) {
        for(int i=0; i<elem.second.size(); i++) {
            
            parent_count[elem.second[i]]++;
        }
    }
    //Add to queue nodes with parent 0
    for(auto elem : parent_count) {
        if (elem.second == 0) {
            
            q.push_back(elem.first);
        }
    }  
    //Perform BFS using topo sort
    //If at the end of the loop, we have not visited the n courses, there is a cycle
    while(!q.empty()) {
        
        int curr =  q.back();
        q.pop_back();
        
        visited_count++;
        
        for(int i=0; i<graph[curr].size(); i++) {
            
            parent_count[graph[curr][i]]--;  
            if (parent_count[graph[curr][i]] == 0) {
                
                q.push_front(parent_count[graph[curr][i]]);
            } 
        }
    }  
    
    return (n == visited_count);
}

enum elem_state {
    NOT_VISITED = 0,
    VISITING,
    VISITED
};

bool check_for_cycle(std::unordered_map<int, std::vector<int>> &graph, int start, std::unordered_map<int, enum elem_state> &elem_status) {
 
    bool result = true;
    
    elem_status[start] = VISITING;
    
    for (int i=0; i< graph[start].size(); i++) {
        if(elem_status[graph[start][i]] == VISITING) {
            return false;
        }
        if (elem_status[graph[start][i]] == NOT_VISITED) {
            if (!check_for_cycle(graph, graph[start][i], elem_status)) {
                return false;
            }
        }
    }
           
    elem_status[start] = VISITED;
         
    return result;
}

bool is_valid_course_schedule(int n, std::vector<std::vector<int>> prerequisites) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> parent_count;
    std::unordered_map<int, enum elem_state> elem_status;
    int start = -1;
    
    //Build graph using prerequisites pairs
    for(int i=0; i<prerequisites.size(); i++) {
        
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
        parent_count[prerequisites[i][0]] = 0;
        parent_count[prerequisites[i][1]] = 0;
        elem_status[prerequisites[i][0]] = NOT_VISITED;
        elem_status[prerequisites[i][1]] = NOT_VISITED;
        
    }
    //Build parent count
    for(auto elem : graph) {
        for(int i=0; i<elem.second.size(); i++) {
            
            parent_count[elem.second[i]]++;
        }
    }
    
    //Check for nodes with parents == 0 to set as a starting point
    //If there is more than one only the first will be used
    for(auto elem : parent_count) {
        if (elem.second == 0) {
            
            start = elem.first;
            break;
        }
    }
    //If there is no nodes with 0 parents, return false
    if (start == -1 ) {
        return false;
    }
    
    return check_for_cycle(graph, start, elem_status);
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    int n;
    std::cin >> n;
    ignore_line();
    int prerequisites_length;
    std::cin >> prerequisites_length;
    ignore_line();
    std::vector<std::vector<int>> prerequisites;
    for (int i = 0; i < prerequisites_length; i++) {
        prerequisites.emplace_back(get_words<int>());
    }
    bool res = is_valid_course_schedule(n, prerequisites);
    std::cout << std::boolalpha << res << '\n';
}