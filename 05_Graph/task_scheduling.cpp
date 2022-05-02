/*
For this problem, given a list of tasks and a list of requirements, compute a sequence of tasks that can be performed, such that we complete every task once while satisfying all the requirements.

Each requirement will be in the form of a list [a, b], where task a needs to be completed first before task b can be completed,

There is guaranteed to be a solution.

Examples
Example 1
Input:
tasks = ["a", "b", "c", "d"]
requirements = [["a", "b"], ["c", "b"], ["b", "d"]]
Output: ["a", "c", "b", "d"]
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_map>
#include <deque>

std::vector<std::string> task_scheduling(std::vector<std::string> tasks, std::vector<std::vector<std::string>> requirements) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<std::string, int> parent_count;
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::deque<std::string> q;
    std::vector<std::string> result;
    
    //initialize parent count to 0
    for (int i=0; i<tasks.size(); i++) {
        parent_count[tasks[i]] = 0;
        graph[tasks[i]] = {};
    }
    //Fill parent count with real data
    for(int i=0; i<requirements.size(); i++) {      
        parent_count[requirements[i][1]]++;
        graph[requirements[i][0]].push_back(requirements[i][1]);
    }
    
    //Prepare queue with nodes with 0 connections
    for (int i=0; i<tasks.size(); i++) {
        if (parent_count[tasks[i]] == 0) {
            q.push_back(tasks[i]);
        }
    }
    
    while (!q.empty()) {
    
        std::string curr = q.back();
        q.pop_back();
        
        result.push_back(curr);
        
        // 
        std::vector<std::string> node_list = graph[curr];
           
        for (int i=0; i<node_list.size(); i++) {
            
            parent_count[node_list[i]]--;

            if ( parent_count[node_list[i]] == 0) {
                q.push_front(node_list[i]);
            }
        }       
    }
    
    return result;
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

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::vector<std::string> tasks = get_words<std::string>();
    int requirements_length;
    std::cin >> requirements_length;
    ignore_line();
    std::vector<std::vector<std::string>> requirements;
    for (int i = 0; i < requirements_length; i++) {
        requirements.emplace_back(get_words<std::string>());
    }
    std::vector<std::string> res = task_scheduling(tasks, requirements);
    if (res.size() != tasks.size()) {
        std::cout << "output size " << res.size() << " does not match input size " << tasks.size() << '\n';
        return 0;
    }
    std::unordered_map<std::string, int> indices;
    for (int i = 0; i < res.size(); i++) {
        indices.insert({res[i], i});
    }
    for (auto req : requirements) {
        for (auto task : req) {
            if (indices.find(task) == indices.end()) {
                std::cout << "'" << task << "' is not in output" << '\n';
                return 0;
            }
        }
        std::string a = req[0];
        std::string b = req[1];
        if (indices[a] >= indices[b]) {
            std::cout << "'" << a << "' is not before '" << b + "'" << '\n';
            return 0;
        }
    }
    std::cout << "ok" << '\n';
}
