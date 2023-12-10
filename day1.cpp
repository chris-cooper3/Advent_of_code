#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    // 'std::vector' a dynamic array that can grow in size
    // '<std::vector<int>>' The type of data stored in the vectors --> which is vector of intergers.
    // 'vec' is the name of the vector variable
    std::vector<std::vector<int> > vec;

    // 'std::ifstream' a c++ library which stands for input file stream
    // 'file_in' is an instance name of the object method ifstream
    std::ifstream file_in("test.txt");

    // A string called line (i.e. each line of the txt file)
    std::string line;

    // 'std::getline' a function that reads a line from an input stream.
    // 'std::getline(file_in, line)' line will store each line from the input stream as a string
    while (std::getline(file_in, line))
    { // line in the loop will be the current line

        // 'istringstream' input string stream instance
        // 'ss' name of the instance 'string stream'
        // 'ss(line) inputs the string
        std::istringstream ss(line);

        vec.push_back({}); // Add one more empty vector (of vectors) to `vec`.

        // Reads in an interger from the input stream ss and stores it as x
        // add the interger x to the sub vector
        // if there are no more interegrs ss>> x is false and the next line is read.
        int x;
        while (ss >> x)
            vec.back().push_back(x); // Add it to the last sub-vector of `vec`.

            // Check if the next character is not an integer
            if (ss.peek() == ',' || ss.peek() == ' ' || ss.peek() == '\t')
            {
                ss.ignore(); // Ignore the non-integer character
            }
    }

    // Print the contents of the vector
    for (const auto &subvec : vec)
    {
        for (int num : subvec)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

/*
std::string loadString(const std::string &filename)
{
    // Open the file
    std::ifstream file(filename);

    // Read the content of the file into a string variable
    std::string Content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    // Close the file
    file.close();

    return Content;
}

std::vector<int> extractIntegersFromString(const std::string &inputString)
{
    std::istringstream iss(inputString);
    std::vector<int> extractedIntegers;

    int intValue;

    // Extract integers from the string and store them in the vector
    while (iss >> intValue)
    {
        extractedIntegers.push_back(intValue);
    }

    // Return the vector containing the extracted integers
    return extractedIntegers;
}

int main()
{
    // Call the loadString function with the filename "cal_doc.txt"
    std::string loadedString = loadString("test.txt");

    // Extract integers from the loaded string
    std::vector<int> numbers = extractIntegersFromString(loadedString);

    // Print the extracted integers
    std::cout << "The extracted integers: ";
    for (int value : numbers)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/