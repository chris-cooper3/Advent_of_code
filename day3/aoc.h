// The below two lines are what's called include guards

#ifndef MY_AOC_HEADER_H // Checks that this header has not been defined previously --> compiler exectues the code until #endif
// ifndef stands for if not defined
#define MY_AOC_HEADER_H // This header will be defined on the first time it is used in some source code for example in a different header file.

/*
For example, if you define a function in a file called common.h 

and then you have two different header files (header1.h and header2.h) where you have included common.h in both of these header files,
then witout the above guard, the function in common.h would be re-defined twice if you don't have the guard.

With the guard, common.h is only compiled once.
*/

#include <iostream>   // Header that defines the standard input/output stream objects.
#include <fstream>    // Header providing file stream classes used for file reading and writing.
#include <sstream>    // Header providing string stream classes, useful for parsing strings.
#include <cstdio>     // C Standard Input and Output Library, for operations like printf and scanf.
#include <string>     // Header introducing string class in the standard library.
#include <vector>     // Header introducing the vector container, a dynamic array.
#include <array>      // Header providing the array container, a fixed-size array.
#include <set>        // Header introducing the set container, which stores unique elements following a specific order.
#include <map>        // Header providing map container, which stores key-value pairs following a specific order.
#include <list>       // Header introducing the list container, a doubly linked list.
#include <utility>    // Header providing utility functions like std::pair and std::swap.
#include <tuple>      // Header introducing the tuple, a fixed-size collection of heterogeneous values.
#include <deque>      // Header providing the deque (double-ended queue) container.
#include <numeric>    // Header providing numeric operations on values in containers.
#include <algorithm>  // Header providing a collection of algorithms to operate on containers.
#include <functional> // Header providing a set of function objects, designed for use with the standard algorithms.
#include <cctype>     // Header providing functions to test character types (e.g., isdigit, isalpha).
#include <locale>     // Header providing localization utilities for specific cultural regions.
#include <regex>      // Header providing classes and functions to work with regular expressions.


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

/**
 * @brief This function takes a string as an input which will return a vector of an array of strings.
 * 
 * @param s the input string
 * @return auto (A vector of strings for each line in the input string)
 */
auto read_ip(std::string s){
    // A vector of an array of strings
    std::vector<std::string> lines;
    // The string representing each line
    std::string line;
    // Reads in the string
    std::ifstream ip(s);
    // get each line (string) and store it as a vector
    while(std::getline(ip,line))
        lines.push_back(line);
    return lines;
}

auto read_paragraph_ip(std::string s){
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> para;
    auto lines = read_ip(s);
    std::set<size_t> breaks = {0,lines.size()};
    for(auto line : lines) {
        if(!line.empty()) {
            para.push_back(line);
        } else {
            if(!para.empty()) result.push_back(para);
            para.clear();
        }
    }
    if(!para.empty()) result.push_back(para);
    return result;
}

#endif
