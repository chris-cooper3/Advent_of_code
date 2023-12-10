#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    // We've made a vector, that stores subvectors intergers called vec
    std::vector<std::vector<int>> vec;

    // 'std::ifstream' a c++ library which stands for input file stream
    // 'file_in' is an instance name of the object method ifstream
    std::ifstream file_in("cal_doc.txt");

    // A string called line (i.e. each line of the txt file)
    std::string line;

    // 'std::getline' a function that reads a line from an input stream.
    // 'std::getline(file_in, line)' line will store each line from the input stream as a string
    while (std::getline(file_in, line))
    {
        // a dynamic vector called subvec which will store the intergers for each line
        std::vector<int> subvec;

        // iterates over each character in the line
        for (char ch : line)
        {   
            //checks if the character is a digit and then if it is, adds it to the subvector.
            if (isdigit(ch))
            {
                // '0' has as ascii value of 48
                // '1' has an ascii value of 49 hence 49 - 48 = 1
                subvec.push_back(ch - '0'); // Convert character to integer and add to subvector
            }
        }

        // adds the subvector to the vector
        vec.push_back(subvec);
    }

    // Print the contents of the vector
    // 'const' means the intergers can't be edited
    // vec is the outer vector loop
    // subvec is the inner loop
    for (const std::vector<int> &subvec : vec)
    {
        // loops through subvector and prints intergers
        for (int num : subvec)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int totalSum = 0;

    // for subvec in vec
    for (const std::vector<int> &subvec : vec)
    {
        std::string concatenated; 

        if (!subvec.empty())
        {
            concatenated += std::to_string(subvec[0]);

            if (subvec.size() > 1)
            {
                // subvec.back() returns the last element in the vector
                concatenated += std::to_string(subvec.back());
            }
            else
            {
                // Duplicate the single integer
                concatenated += std::to_string(subvec[0]);
            }
        }

        // Convert the concatenated string to an integer and add to the total sum
        // stio means string to interger
        totalSum += std::stoi(concatenated);

        std::cout << "Concatenated: " << concatenated << std::endl;
    }

    std::cout << "Total Sum: " << totalSum << std::endl;

    return 0;
}

