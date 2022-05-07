/*
This problem is similar to Task Scheduling. The primary difference is now we assign times to tasks and we ask for the minimum amount of time to complete all tasks. There will be an extra times array such that times[i] indicates the time required to complete task[i]. You have also invited all your friends to help complete your tasks so you can work on any amount of tasks at a given time. Be sure to remember that task a must be completed before task b so despite your unlimited manpower your friends must still wait for task a to complete before starting task b.

There is guaranteed to be a solution.

Examples
Example 1
Input:
tasks = ["a", "b", "c", "d"]
times = [1, 1, 2, 1]
requirements = [["a", "b"], ["c", "b"], ["b", "d"]]
Output: 4
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <unordered_map>
#include <bits/stdc++.h>

int task_scheduling_2(std::vector<std::string> tasks, std::vector<int> times, std::vector<std::vector<std::string>> requirements) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<std::string, int> parent_count;
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> node_time;
    std::deque<std::string> q;
    int time = 0;
    int currMinTime = INT_MAX;
    
    //initialize graph and parent count
    for (int i=0; i<tasks.size(); i++) {
        graph[tasks[i]] = {};
        parent_count[tasks[i]] = 0;
        node_time[tasks[i]] = times[i];
    }
    
    //Build graph and parent count
    for (int i=0; i<requirements.size(); i++) {
        graph[requirements[i][0]].push_back(requirements[i][1]);
        parent_count[requirements[i][1]]++;
    }
    
    //Prepare queue with elemenths with parent 0 and priority_queue with times
    for (auto elem : parent_count) {
        if (elem.second == 0) {
            q.push_back(elem.first);
            if (node_time[elem.first] < currMinTime) {
                currMinTime = node_time[elem.first];
            }
        }
    }
    
    while (!q.empty()) {
        
        int n = q.size();
        int nextMinTime = INT_MAX;
        
        time += currMinTime;
        
        while (n) {
            
            auto curr = q.back();
            q.pop_back();
            
            node_time[curr] -= currMinTime;
            
            //if current node time is already 0, remove as parent
            if (node_time[curr] == 0) {        
            
                //go through neighbors, add to the queue the ones with parent 0
                for (int i=0; i< graph[curr].size(); i++) {

                    parent_count[graph[curr][i]]--;
                    
                    if (parent_count[graph[curr][i]] == 0) {
                        
                        q.push_front(graph[curr][i]);
                        //Set currentMinTime if new node is lower
                        if (node_time[graph[curr][i]] < nextMinTime) {
                            nextMinTime = node_time[graph[curr][i]];
                        }
                    }
                }
            } else {
                //If current node time is > 0, push again to the queue
                q.push_front(curr);
                //Set currentMinTime if current node is lower
                if (node_time[curr] < nextMinTime) {
                    nextMinTime = node_time[curr];
                }
            }
            n--;
        }
        currMinTime = nextMinTime;
    }
    
    return time;
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
    std::vector<int> times = get_words<int>();
    int requirements_length;
    std::cin >> requirements_length;
    ignore_line();
    std::vector<std::vector<std::string>> requirements;
    for (int i = 0; i < requirements_length; i++) {
        requirements.emplace_back(get_words<std::string>());
    }
    int res = task_scheduling_2(tasks, times, requirements);
    std::cout << res << '\n';
}
