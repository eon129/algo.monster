/*
Given k sorted lists of numbers, merge them into one sorted list.

Input: [[1, 3, 5], [2, 4, 6], [7, 10]]

Output: [1, 2, 3, 4, 5, 6, 7, 10]
*/
#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <queue>

/* For this first approach the complexity is not optimal. This two step solution first put all numbers
into the heap, this takes n insertions on the heap, with every insertion taking log(i) time.
Then going through all heap poping elements, and rearanging heap
*/
std::vector<int> merge_k_sorted_lists_old(std::vector<std::vector<int>> lists) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::priority_queue<int> pq;
    std::vector<int> result;
    int c = 0;
    int list_finished;
        
    do {
        
        list_finished = 0;
        //iterate over lists
        for(int i=0; i<lists.size(); i++) {
            
            if ( c < lists[i].size() ) {
                
                //Push negative numbers, we have a min heap
                pq.push(lists[i][c] * -1);
            } else {
                //Increment flag indicating number of lists finished
                list_finished++;
            }
        }
        
        c++;    
    } while (list_finished < lists.size());
    
    while(!pq.empty()) {
        
        auto e =  pq.top();
        pq.pop();
        
        //Push negative values, so at the end we have original sign
        result.push_back(e * -1);
    }
    
    return result;
}

/* This algorithm works better in the case you get a small number of lists with 
a big number of elements, on every iteration you will spend only log(num_lists) time to get
the next number.
*/
std::vector<int> merge_k_sorted_lists(std::vector<std::vector<int>> lists) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::priority_queue<std::pair<int, std::pair<int, int>>> pq;
    std::vector<int> result;
    int c = 0;
    int list_finished;
    
    //Put first element of every list in the heap
    for (int i=0; i<lists.size(); i++) {
    
        pq.push(std::make_pair( -lists[i][0], std::make_pair(i, 0)));
    }
    
    //Push to heap every element on list in order
    //until we finish
    while(!pq.empty()) {
    
        auto curr = pq.top();
        pq.pop();
        
        result.push_back(-curr.first);
        
        //Go to the next value in the list if posible
        if (curr.second.second + 1 < lists[curr.second.first].size()) {
                 
            auto listIndex = curr.second.first;
            auto valIndex = curr.second.second + 1;
            pq.push(std::make_pair( -lists[listIndex][valIndex], std::make_pair(listIndex, valIndex)));
        }
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
    int lists_length;
    std::cin >> lists_length;
    ignore_line();
    std::vector<std::vector<int>> lists;
    for (int i = 0; i < lists_length; i++) {
        lists.emplace_back(get_words<int>());
    }
    std::vector<int> res = merge_k_sorted_lists(lists);
    put_words(res);
}