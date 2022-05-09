/*
Given a list of points on a 2D plane. Find k closest points to origin (0, 0).

Input: [(1, 1), (2, 2), (3, 3)], 1

Output: [(1, 1)]
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <queue>
#include <cmath>

std::vector<std::vector<int>> k_closest_points(std::vector<std::vector<int>> points, int k) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::priority_queue<std::pair<float, int>> pq;
    std::vector<std::vector<int>> result;
    
    //Iterate over points and calculate the dinstance from 0 using sqrrot(a^2 + b^2) and push it to the heap
    for (int i=0; i< points.size(); i++) {
        float distance = sqrt((points[i][0]^2) + (points[i][0]^2));
        pq.push(std::make_pair(distance, i));
    }
    
    //For loop k times and pop it from the queue
    for(int i=0; i<k; i++) {
        auto elem = pq.top();
        pq.pop();
        
        result.push_back(points[elem.second]);
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

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    int points_length;
    std::cin >> points_length;
    ignore_line();
    std::vector<std::vector<int>> points;
    for (int i = 0; i < points_length; i++) {
        points.emplace_back(get_words<int>());
    }
    int k;
    std::cin >> k;
    ignore_line();
    std::vector<std::vector<int>> res = k_closest_points(points, k);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
