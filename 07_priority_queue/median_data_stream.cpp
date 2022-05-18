/*
Given a stream of numbers, find the median number at any given time (accurate to 1 decimal place). Do this in O(1) time complexity.

Example:

add_number(1)
add_number(2)
add_number(3)
get_median() == 2.0
add_number(4)
get_median() == 2.5
*/

#include <iomanip> // setprecision
#include <iostream> // cin, cout
#include <sstream> // istringstream
#include <string> // string
#include <queue>

class MedianOfStream {
    
private:
    
    std::priority_queue<int> min;
    std::priority_queue<int> max;
    int flag = 0;
    
public:
    
    MedianOfStream () {
        flag = 0;
    }
    
    
    void add_number(float num) {
        // Implement function here
        //std::cout << num << " , ";
        
        if (max.size() == 0) {    
            max.push(num);
            flag = 1;
            return;
        }
        
        if (min.size() == 0) {
            
            if (num >= max.top()) {  
                min.push(-num);
            } else {
                int temp = max.top();
                max.pop();
                max.push(num);
                min.push(-temp);
            }
            flag = 0;
            return;
        }
        //Put at max
        if (num < max.top()) { 
            
            if(flag == 0) {
                max.push(num);
                flag = 1;
            } else {
                int temp = max.top();
                max.pop();
                max.push(num);
                min.push(-temp);
                flag = 0;
            }
            return;
        }
        //Put al min
        if (num > -min.top()) {    
            if(flag == 0) {
                int temp = -min.top();
                min.pop();
                min.push(-num);
                max.push(temp);
                flag = 1;
            } else {
                min.push(-num);
                flag = 0;
            }
            return;
        }
        //Num is in the middle so put depending on flag
        if(flag == 0) {
            max.push(num);
            flag = 1;
        } else {
            min.push(-num);
            flag = 0;
        }     
        return;
    }

    float get_median() {
        // Implement function here
        //If both heaps have the same size, return both top mean value
        if (flag == 0) {
            int max_val = max.top();
            int min_val = -min.top();
            return (max_val + min_val) / 2.0;
        }
        //Otherwhise median will be on the max top
        return (float)max.top();
    }
};

int main() {
    MedianOfStream median_of_stream;
    int n;
    std::cin >> n;
    std::string input;
    for (int i = 0; i < n; ++i) {
        std::cin >> input;
        if (input == "get") {
            float median = median_of_stream.get_median();
            std::cout << std::fixed << std::setprecision(1) << median << '\n';
        } else {
            float num;
            std::stringstream ss;
            ss << input;
            ss >> num;
            median_of_stream.add_number(num);
        }
    }
}
