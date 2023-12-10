#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    std::vector<std::vector<int>> vec;

    std::ifstream file_in("my_file.txt");

    std::string line;

    while (std::getline(file_in, line)) // Read next line to `line`, stop if no more lines.
    {
        // Construct so called 'string stream' from `line`, see while loop below for usage.
        std::istringstream ss(line);

        vec.push_back({}); // Add one more empty vector (of vectors) to `vec`.

        int x;
        while (ss >> x)              // Read next int from `ss` to `x`, stop if no more ints.
            vec.back().push_back(x); // Add it to the last sub-vector of `vec`.
    }
}

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
