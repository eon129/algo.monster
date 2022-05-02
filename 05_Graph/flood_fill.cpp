/*
In computer graphics, an uncompressed raster image is presented as a matrix of numbers. Each entry of the matrix represents the color of a pixel. A flood fill algorithm takes a coordinate r, c and a replacement color, and replaces all pixels connected to r, c that have the same color (i.e., the pixels connected to the given coordinate with of same color and all the other pixels connected to the those pixels of the same color) with the replacement color. (e.g. MS-Paint's paint bucket tool).

Input
r: row
c: column
replacement: replacement color
image: an 2D array of integers representing the image
Output
the replaced image

Examples
Example 1:
Input:

r = 2
c = 2
replacement = 9
arr = [[0,1,3,4,1],[3,8,8,3,3],[6,7,8,8,3],[12,2,8,9,1],[12,3,1,3,2]]
Output: [[0,1,3,4,1],[3,9,9,3,3],[6,7,9,9,3],[12,2,9,9,1],[12,3,1,3,2]]

Explanation:

From

0 1 3 4 1
3 8 8 3 3
6 7 8 8 3
12 2 8 9 1
12 3 1 3 2

to

0 1 3 4 1
3 9 9 3 3
6 7 9 9 3
12 2 9 9 1
12 3 1 3 2
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <utility>

std::vector<std::vector<int>> flood_fill1(int r, int c, int replacement, std::vector<std::vector<int>> image) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    int matrix_size = image.size();
    std::deque<std::pair<int, int>> q;
    int find_val = image[r][c];

    q.push_back(std::make_pair(r, c));
    
    //Set first vertex as visited
    image[r][c] = replacement;
    
    while (!q.empty()) {
        
        int n = q.size();
        
        while (n) {
            
            std::pair<int, int> curr = q.back();
            q.pop_back();
            
            int row = curr.first;
            int col = curr.second;
    
            //iterate over neighbors
            for (int i=0; i<4 ;i++) {
                
                int nRow = row+delta_row[i];
                int nCol = col+delta_col[i];

                if((nRow) >=0 &&
                   (nRow) < matrix_size &&
                   (nCol) >=0 &&
                   (nCol) < matrix_size &&
                   image[nRow][nCol] == find_val) {
                    
                    //set vertex as visited
                    image[nRow][nCol] = replacement;
                    
                    //push vertex to queue
                    q.push_front(std::make_pair(nRow, nCol));
                }
            }
            n--;
        }
    }
    
    return image;
}

std::vector<std::vector<int>> flood_fill(int r, int c, int replacement, std::vector<std::vector<int>> image) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    int matrix_size = image.size();
    std::deque<std::pair<int, int>> q;
    int find_val = image[r][c];

    q.push_back(std::make_pair(r, c));
    
    //Set first vertex as visited
    image[r][c] = replacement;
    
    while (!q.empty()) {
            
        std::pair<int, int> curr = q.back();
        q.pop_back();
            
        int row = curr.first;
        int col = curr.second;
    
        //iterate over neighbors
        for (int i=0; i<4 ;i++) {
                
            int nRow = row+delta_row[i];
            int nCol = col+delta_col[i];

            if((nRow) >=0 &&
               (nRow) < matrix_size &&
               (nCol) >=0 &&
               (nCol) < matrix_size &&
               image[nRow][nCol] == find_val) {
                    
                //set vertex as visited
                image[nRow][nCol] = replacement;
                    
                //push vertex to queue
                q.push_front(std::make_pair(nRow, nCol));
            } 
        }
    }
    
    return image;
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

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    int r;
    std::cin >> r;
    ignore_line();
    int c;
    std::cin >> c;
    ignore_line();
    int replacement;
    std::cin >> replacement;
    ignore_line();
    int image_length;
    std::cin >> image_length;
    ignore_line();
    std::vector<std::vector<int>> image;
    for (int i = 0; i < image_length; i++) {
        image.emplace_back(get_words<int>());
    }
    std::vector<std::vector<int>> res = flood_fill(r, c, replacement, image);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
