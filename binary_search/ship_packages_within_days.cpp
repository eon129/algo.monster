/*
There are n packages that needs to be transported from one city to another, and you need to transport them there within d days. For the ith package, the weight of the package is weights[i]. You are required to deliver them in order with a rental truck. The rental trucks come in different sizes. The bigger trucks have greater weight capacity but cost more to rent. To minimize cost, you want to deliver the packages in one truck once per day, with a weight capacity as small as possible to save on rental cost. What is the minimum weight capacity of the truck that is required to deliver all packages within d days?

Input
weights: A list of packages and their weights.
d: The number of days to deliver all packages.
Output
The minimum weight capacity of the truck.

Examples
Example 1:
Input:

weights = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
d = 5
Output: 15

Explanation:

The first day we deliver the first 5 package. The second day we deliver the next 2, and for each following days, we deliver 1. The maximum weight delivered on each day is 15, so we can have a truck with a capacity of 15. This value is the minimum.

Constraints
1 <= len(weights) <= 5 * 10^4
1 <= d <= len(weights)
1 <= weights[i] <= 500
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

bool feasible(std::vector<int> &w, int d, int truckLimit)
{
    bool result;
    int wIndex = 0;
    int packCounter = 0;
    int dayCounter = 0;
    
    while (dayCounter < d) {
       
        if ((packCounter + w[wIndex]) > truckLimit) {
            
            dayCounter++;
            packCounter = 0;
        } else {
            packCounter += w[wIndex];
            
            if ( wIndex < w.size()) {
                wIndex++;
            } else {
                break;
            }
        }
    }
    
    result = (wIndex == w.size()) ? true: false;
    
    return result;
}

int min_max_weight(std::vector<int> weights, int d) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int l = 1;
    int r = 0;
    int m, boundary = 0, i;
    
    //Get r index by summing al  values
    for (i=0; i<weights.size(); i++) {
       r += weights[i]; 
    }
    
    while (l<=r) {
        
        m = (l+r) / 2;
        
        if (feasible(weights, d, m)) {
            
            boundary = m;
            r = m-1;
        } else {
            
            l = m+1;
        }
    
    }
    
    return boundary;
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
    std::vector<int> weights = get_words<int>();
    int d;
    std::cin >> d;
    ignore_line();
    int res = min_max_weight(weights, d);
    std::cout << res << '\n';
}
