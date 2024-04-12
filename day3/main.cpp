#include "aoc.h"

/*
Instead of doing:
int main() {
    std::vector<int> vec;  // Using std:: to access the vector class
    std::cout << "Hello, World!" << std::endl;  // Using std:: to access cout and endl
    return 0;
}

you can do:
int main() {
    vector<int> vec;  // Directly using vector without std::
    cout << "Hello, World!" << endl;  // Directly using cout and endl without std::
    return 0;
}

by including:
using namespace std;
*/
using namespace std;

/**
 * @brief Extracts a number from a string starting from a given position.
 *
 * This function iterates over the characters of a string starting from
 * index `i` and accumulates digits into a new string until a non-digit
 * character is encountered or the end of the string is reached.
 *
 * @param line The string from which to extract the number.
 * @param i The index at which to start the extraction.
 * @return A string containing the number extracted from the input string.
 */
string read_num(const string & line, int i) {
    string snum = ""; // string to store the found digits
    // while the index is less than the size of the line and the string at the index is a digit
    while(i < line.size() && isdigit(line.at(i))) {
        // add the string digit into snum
        snum += line.at(i);
        // add 1 to the index
        i++;
    }
    // return the found number. 
    return snum;
}
/**
 * @brief Checks if the character at the given indices within a 2D grid (vector of strings) is not a period.
 *
 * This function assumes a 2D grid where each string in the vector represents a row of the grid.
 * It checks if the specified position, defined by indices i (row) and j (column), contains a character
 * that is not a period ('.'). The function also ensures that the indices are excluding the first/law row 
 * and column.
 *
 * @param scheme The 2D grid represented as a vector of strings.
 * @param i The row index within the grid.
 * @param j The column index within the row.
 * @return True if the character at the specified position is not a period and the indices are within
 *         the valid range, excluding the first/last row and column. Otherwise, returns false.
 */
bool is_symbol(const vector<string> & scheme, int i, int j) {
    // Number of rows
    int ni = scheme.size();
    // Number of columns 
    int nj = scheme.at(0).size();

    // return true if the symbol at the index location is not a '.' if not the first/last row or first/last column 
    return i>0 && j>0 && i<ni && j<nj && scheme.at(i).at(j) != '.';
}

/**
 * @brief Generates a list of neighboring coordinates based on the current position and length.
 *
 * This function calculates the neighbors of a cell located at (i, j) in a 2D grid. It considers neighbors
 * to be those cells directly adjacent horizontally, vertically, and diagonally. The function does not check
 * for boundary conditions, so some returned coordinates may be outside the grid if (i, j) is near the edge.
 * Specifically, it adds the cell immediately to the left, all the cells to the right up to `len` distance,
 * and the cells above and below the current row within the same horizontal range.
 *
 * @param i The row index of the current position.
 * @param j The column index of the current position.
 * @param len The length to the right of (i, j) to consider for neighboring cells.
 * @return A vector of array<int, 2> where each array<int, 2> represents the coordinates of a neighbor.
 */
vector<array<int,2>> neighbours(int i, int j, int len) {
    // A vector of coordinates [i,j]
    vector<array<int,2>> nbrs;

    // Add the coordinates of the neighbour directly to the left
    nbrs.push_back({i,j-1});
    // Add the coordinate directly to the right of the last digit in the found number
    nbrs.push_back({i,j+len});
    
    // for the rows directly above and below the current row
    // The for loop would iterate over i-1(above) first, then i+1(below)
    for(int ii : {i-1,i+1}) {
        // loop over the columns to the left up until the specifcied length
        for(int jj = j-1; jj<=j+len; jj++) {
            nbrs.push_back({ii,jj});
        }
    }
    return nbrs;
}

/**
 * @brief 
 * 
 * @param scheme The input file as a vector of strings
 * @param i The currrent row of the found number
 * @param j The current column of the first interger in the number
 * @param len The length of the full number
 * @return true 
 * @return false 
*/
bool is_symbol_neighbour(const vector<string> & scheme, int i, int j, int len) {
    // neighbours returns the coordinates of all neighbours of the found number
    // loops over each neighbour
    for(auto [ii,jj] : neighbours(i,j,len)) {
        // checks if the neighbour is a symbol
        // if true return true else return false
        if(is_symbol(scheme,ii,jj)) return true;
    }
    return false;
}


/**
 * @brief 
 * 
 * @param scheme 
 * @param i 
 * @param j 
 * @param sn 
 * @param gear_map 
 */
void gear_check(const vector<string> & scheme,
                int i,
                int j,
                const string & sn,
                map<array<int,2>,vector<string>> & gear_map) {
    // loop over the neighbours
    for(auto [ii,jj] : neighbours(i,j,sn.size())) {
        // if the neighbour is a symbol and a gear (*)
        if(is_symbol(scheme,ii,jj) && scheme.at(ii).at(jj) == '*') {
            // Add the row and column of the gear for the corresponding found number
            gear_map[{ii,jj}].push_back(sn);
        }
    }
}

void day3(const string & fn) {
    // ip is a vector of strings of the input file.
    const auto ip = read_ip(fn);
    // A dictionary  
    map<array<int,2>,vector<string>> gears_map;
    // The number of rows 
    int ni = ip.size();
    // The number of columns
    int nj = ip.at(0).size();
    int ans = 0;
    // loop over the rows
    for(int i = 0; i < ni; i++) {
        int j = 0;
        // loop over the columns 
        while(j < nj) {

            // the line (string)
            string line = ip[i];
            // is j is part of a number of a number, read num will return the full number as a string
            string sn = read_num(line,j);

            // if sn is an empty string, skip to the next column
            if(sn.empty()) {
                j++;
            } else {

                if(is_symbol_neighbour(ip,i,j,sn.size())) {
                    // Sum the number to the total
                    // stoi converts a string to an interger
                    ans += stoi(sn);
                }
                gear_check(ip,i,j,sn,gears_map);

                // skip the other columns that are part of the digit to peform the next search along the row.
                j += sn.size();
            }
        }
    }
    cout << fn << " day 3 part 1 answer = " << ans << endl;
    int ans2 = 0;
    // loop over the dictionary
    for(auto [ij,sns] : gears_map) {
        // If a found gear has 2 numbers
        if(sns.size() == 2) {
            // calculate the gear ratio by multiplying two numbers and add to answer.
            ans2 += stoi(sns.at(0)) * stoi(sns.at(1));
        }
    }
    cout << fn << " day 3 part 2 answer = " << ans2 << endl;
}

int main() {
    //day3("test_input");
    day3("input");

    // Create a test grid (vector of strings).
    std::vector<std::string> scheme = {
        "467..114.."
        "...*......"
        "..35..633."
        "......#..."
        "617*......"
        ".....+.58."
        "..592....."
        "......755."
        "...$.*...."
        ".664.598.."};

    is_symbol(scheme,1,1);

    return 0;
}
