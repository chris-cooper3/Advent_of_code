#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Function to check if a game is possible given the maximum number of cubes available for each color
bool isGamePossible(const std::vector<std::map<std::string, int>> &turns,
                    const std::map<std::string, int> &maxCubes)
{
    // Iterate through each turn of the game
    for (const auto &turn : turns)
    {
        // Each turn contains a map of colors to the count of cubes shown

        // Iterate through each color and its count in the current turn
        for (const auto &[color, count] : turn)
        {
            // Check if the number of cubes of this color in the turn exceeds the maximum available

            if (count > maxCubes.at(color))
            {
                // If the count exceeds the maximum for any color, the game is not possible
                return false;
            }
        }
    }

    // If no turn exceeds the maximum cubes for any color, the game is possible
    return true;
}
// Function to process part 1 and return the turns for each game
std::vector<std::vector<std::map<std::string, int>>> part1(const std::string &filename)
{
    std::map<std::string, int> maxCubes = {{"red", 12}, {"green", 13}, {"blue", 14}};
    int sumOfIds = 0;
    std::ifstream file(filename);
    std::string line;

    std::vector<std::vector<std::map<std::string, int>>> allGameTurns;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        int gameId;

        // Extract the game ID
        ss >> token; // Skip "Game"
        ss >> gameId;
        ss.ignore(2); // Ignore ": "

        std::vector<std::map<std::string, int>> turns;

        // Parse each turn
        while (getline(ss, token, ';'))
        // I'm now in a substring up to ; which essentially each turn (each handful) within a game
        // i.e. token = 3 blue, 4 red
        {
            std::stringstream ssTurn(token);
            std::map<std::string, int> cubesInTurn; // a map to store the colour and amount for each turn
            std::string color;
            int count;

            // Parse the count and color of cubes
            while (ssTurn >> count >> color)
            // loops over each ccolour in a turn (colour and amount)
            {
                // Remove the comma if present
                if (color.back() == ',')
                {
                    color.pop_back();
                }
                cubesInTurn[color] += count;
            }

            turns.push_back(cubesInTurn);
        }
        allGameTurns.push_back(turns);
        
        if (isGamePossible(turns, maxCubes))
        {
            sumOfIds += gameId;
        }
    }
    std::cout << "Sum of IDs of possible games: " << sumOfIds << std::endl;
    return allGameTurns;
}

//######### Part 2 #########//
std::vector<std::map<std::string, int>> part2(const std::vector<std::vector<std::map<std::string, int>>> &allGameTurns)
{
    // a vector of a map of strings
    std::vector<std::map<std::string, int>> maxCubesPerGame;

    for (const auto &game : allGameTurns)
    // a loop for each game
    {
        std::map<std::string, int> maxCubes;

        for (const auto &turn : game)
        // a loop for each turn in a game
        {
            for (const auto &[color, count] : turn)
            // a loop for each colour and corresponding count in a turn
            {
                auto it = maxCubes.find(color);
                // if the colour has already been added to the maxCubes map which belongs to the loop through each game.
                if (it != maxCubes.end())
                {
                    // compares the current colour count, to the count that has just been found for the color and adds the larger number to the map
                    maxCubes[color] = std::max(maxCubes[color], count);
                }
                else
                {
                    // because the colour wasn't found, add is to the map with the count.
                    maxCubes[color] = count;
                }
            }
        }
        // Add the maximum colourd and counts found for this game to the overall map for the whole data set.
        maxCubesPerGame.push_back(maxCubes);
    }

    long long totalSum = 0; // Use long long to avoid overflow

    for (const auto &gameMaxCubes : maxCubesPerGame)
    {
        long long product = 1; // Start with 1 because multiplying by 1 has no effect

        for (const auto &[color, count] : gameMaxCubes)
        {
            product *= count; // Multiply the counts together
        }

        totalSum += product; // Add the product to the total sum
    }

    std::cout << "Total sum of products: " << totalSum << std::endl;

    return maxCubesPerGame;
}

int main()
{
    auto allGameTurns = part1("input.txt");

    // Find the maximum cubes for each color in each game
    auto maxCubesPerGame = part2(allGameTurns);

    return 0;
}