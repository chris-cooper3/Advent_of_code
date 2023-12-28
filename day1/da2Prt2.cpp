#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

// Function to check if a substring is a valid number word and convert it
int convertNumberWord(const std::string &word, const std::map<std::string, int> &numberMap)
{
    // Iterate over each pair in the numberMap
    for (const auto &pair : numberMap)
    {
        // Search for the spelled-out number (pair.first) within the given word
        size_t found = word.find(pair.first);

        // Check if the spelled-out number is found in the word
        if (found != std::string::npos)
        {
            // If found, return the corresponding numerical value (pair.second)
            return pair.second;
        }
    }

    // If no spelled-out number is found in the word, return -1
    return -1;
}

int main()
{
    std::ifstream file("input"); // Replace 'test2.txt' with your file name
    std::string line;
    std::vector<std::vector<int>> extractedNums;
    std::map<std::string, int> numberMap = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::string currentWord;
            std::vector<int> subVec;
            for (char c : line)
            {
                if (isdigit(c))
                {
                    
                    currentWord.clear();
                    subVec.push_back(c - '0');
                }
                else if (isalpha(c))
                {
                    currentWord += c;
                    int num = convertNumberWord(currentWord, numberMap);
                    if (num != -1)
                    {
                        subVec.push_back(num);
                        currentWord.clear();
                    }
                }
            }
            if (!currentWord.empty())
            {
                int num = convertNumberWord(currentWord, numberMap);
                if (num != -1)
                {
                    subVec.push_back(num);
                }
            }
            extractedNums.push_back(subVec);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    int total = 0;

    for (const auto &subVec : extractedNums)
    {
        if (!subVec.empty())
        {
            // Get first and last digit
            int firstDigit = subVec.front();
            int lastDigit = subVec.size() > 1 ? subVec.back() : firstDigit; // Use firstDigit if only one element

            // Concatenate digits to create a new number
            int newNumber = firstDigit * 10 + lastDigit;

            // Add new number to total
            total += newNumber;

            // Print new number
            std::cout << "New Number: " << newNumber << std::endl;
        }
    }

    // Print total
    std::cout << "Total: " << total << std::endl;
    return 0;
}
