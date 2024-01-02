#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void extractNos(int row, int col)
{
    static const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    static const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int sum = 0;

    for (int i = 0; i < 8; ++i)
    {
        int newRow = row + dx[i];
        int newCol = col + dy[i];

        // Check boundaries
        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size())
        {
            char adjacentChar = grid[newRow][newCol];
            if (isDigit(adjacentChar))
            {
                sum += adjacentChar - '0';
            }
        }
    }
}

std::vector<std::pair<int, int>> findSymbolPositions(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::pair<int, int>> symbolPositions;
    std::string line;
    int row = 0;

    if (file)
    {
        while (getline(file, line))
        {
            for (int col = 0; col < line.length(); ++col)
            // iterate through each column in the line until the end of the line
            {
                char ch = line[col]; // extract the character from a certain column
                if (ch == '*' || ch == '#' || ch == '+' || ch == '$')
                {
                    symbolPositions.push_back({row, col});
                }
            }
            // Add 1 to the row because we move onto the next line in the while loop
            ++row;
        }
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return symbolPositions;
}



int main()
{
    std::string filename = "yourfile.txt"; // Replace with your actual file name
    auto symbolPositions = findSymbolPositions(filename);

    // Example: Print the positions of the symbols
    for (const auto &position : symbolPositions)
    {
        std::cout << "Symbol found at position: [" << position.first << "," << position.second << "]" << std::endl;
    }

    return 0;
}
