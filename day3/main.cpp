#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <set>

std::vector<int> extractNums(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::string> grid;
    std::vector<int> numbers;
    std::string line;
    //Three digit number
    static const int dx3[] = {-1,0,1,2,3,-1,3,-1,0,1,2,3};
    static const int dy3[] = {-1,-1,-1,-1,-1,0,0,1,1,1,1,1};
    int lengthDx3 = sizeof(dx3) / sizeof(dx3[0]);
    static const std::set<char> symbols = {'*', '#', '+', '$', '@', '=', '&', '%', '/', '-'};

    // Two digit number
    static const int dx2[] = {-1, 0, 1, 2, -1, 2, -1, 0, 1, 2};
    static const int dy2[] = {-1, -1, -1, -1, 0, 0, 1, 1, 1, 1};
    int lengthDx2 = sizeof(dx2) / sizeof(dx2[0]);
   

    // Single digit number
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int lengthDx = sizeof(dx) / sizeof(dx[0]);
    

    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (std::getline(file, line))
    {
        grid.push_back(line);
    }

    for (size_t i = 0; i < grid.size(); ++i)
    // i is each row
    {
        for (size_t j = 0; j < grid[i].length(); ++j)
        //  j is each column
        {
            bool validNumber = false;

            // Check horizontally
            if (j + 2 < grid[i].length() && isdigit(grid[i][j]) && isdigit(grid[i][j + 1]) && isdigit(grid[i][j + 2]))
            {
                std::cout << "Starting number for three digit: " << grid[i][j] << std::endl;
                // Check symbols around the first digit
                for (int k = 0; k < lengthDx3; ++k)
                {
                    int ny = static_cast<int>(i) + dy3[k];
                    int nx = static_cast<int>(j) + dx3[k];

                    // Boundary check
                    if (ny >= 0 && ny < static_cast<int>(grid.size()) &&
                        nx >= 0 && nx < static_cast<int>(grid[ny].length()))
                    {
                        // if the coordinate is within the boundary of the grid
                        //std::cout << "nx :" << nx<< std::endl;
                        //std::cout << "ny :" << ny << std::endl;
                        //std::cout << "The character at each checkpoint: " << grid[ny][nx] << std::endl;
                        //std::cout << "Character search: " << (symbols.find(grid[ny][nx]) == symbols.end()) << std::endl;

                        //std::cout << "Characters surrounding 4 " << grid[ny][nx] << std::endl;
                        
                        

                        if (symbols.find(grid[ny][nx]) != symbols.end())
                        {
                            // if the above statement is true, it means that the symbol wasn't found and the number wasn't valid
                            validNumber = true;
                            break;
                        }
                    }
                }

                if (validNumber)
                {
                    int number = (grid[i][j] - '0') * 100 + (grid[i][j + 1] - '0') * 10 + (grid[i][j + 2] - '0');
                    std::cout << "Valid number :" << number << std::endl;
                    numbers.push_back(number);
                    j+=2;
                }
            
            }
            else if (j + 1 < grid[i].length() && isdigit(grid[i][j]) && isdigit(grid[i][j + 1]))
            {
                std::cout << "Starting number for three digit: " << grid[i][j] << std::endl;
                // Check symbols around the first digit
                for (int k = 0; k < lengthDx2; ++k)
                {
                    int ny = static_cast<int>(i) + dy2[k];
                    int nx = static_cast<int>(j) + dx2[k];

                    // Boundary check
                    if (ny >= 0 && ny < static_cast<int>(grid.size()) &&
                        nx >= 0 && nx < static_cast<int>(grid[ny].length()))
                    {
                        // if the coordinate is within the boundary of the grid
                        // std::cout << "nx :" << nx<< std::endl;
                        // std::cout << "ny :" << ny << std::endl;
                        // std::cout << "The character at each checkpoint: " << grid[ny][nx] << std::endl;
                        // std::cout << "Character search: " << (symbols.find(grid[ny][nx]) == symbols.end()) << std::endl;

                        // std::cout << "Characters surrounding 4 " << grid[ny][nx] << std::endl;

                        if (symbols.find(grid[ny][nx]) != symbols.end())
                        {
                            // if the above statement is true, it means that the symbol wasn't found and the number wasn't valid
                            validNumber = true;
                            break;
                        }
                    }
                }

                if (validNumber)
                {
                    int number = (grid[i][j] - '0') * 10 + (grid[i][j + 1] - '0');
                    std::cout << "Valid number :" << number << std::endl;
                    numbers.push_back(number);
                    j ++;
                }
            }

            else if (isdigit(grid[i][j]))
            {
                std::cout << "Starting number for three digit: " << grid[i][j] << std::endl;
                // Check symbols around the first digit
                for (int k = 0; k < lengthDx; ++k)
                {
                    int ny = static_cast<int>(i) + dy[k];
                    int nx = static_cast<int>(j) + dx[k];

                    // Boundary check
                    if (ny >= 0 && ny < static_cast<int>(grid.size()) &&
                        nx >= 0 && nx < static_cast<int>(grid[ny].length()))
                    {
                        // if the coordinate is within the boundary of the grid
                        // std::cout << "nx :" << nx<< std::endl;
                        // std::cout << "ny :" << ny << std::endl;
                        // std::cout << "The character at each checkpoint: " << grid[ny][nx] << std::endl;
                        // std::cout << "Character search: " << (symbols.find(grid[ny][nx]) == symbols.end()) << std::endl;

                        // std::cout << "Characters surrounding 4 " << grid[ny][nx] << std::endl;

                        if (symbols.find(grid[ny][nx]) != symbols.end())
                        {
                            // if the above statement is true, it means that the symbol wasn't found and the number wasn't valid
                            validNumber = true;
                            break;
                        }
                    }
                }

                if (validNumber)
                {
                    int number = grid[i][j] - '0';
                    std::cout << "Valid number :" << number << std::endl;
                    numbers.push_back(number);
                }
            }
            // Similar check can be added for vertical numbers if needed
        }
    }

    file.close();
    return numbers;
}

int main()
{
    std::vector<int> test = extractNums("input.txt");
    int sum = 0;

    for (int num : test)
    {
        std::cout << num << std::endl;
        sum += num; // Add the current number to the sum
    }

    // Print the total sum after the loop
    std::cout << "Total sum: " << sum << std::endl;
}
