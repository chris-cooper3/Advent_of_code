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

int main()
{
    std::ifstream file("input.txt"); // Open the input file
    std::string line;
    int sumOfIds = 0;
    // Define the maximum number of cubes for each color
    std::map<std::string, int> maxCubes = {{"red", 12}, {"green", 13}, {"blue", 14}};

    while (getline(file, line))
    {
        // I'm in a line here which is a gane
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

        std::cout << "Game turns: ";
        for (const auto &turn : turns)
        {
            std::cout << "{ ";
            for (const auto &pair : turn)
            {
                std::cout << pair.first << " " << pair.second << ", ";
            }
            std::cout << "} ";
        }
        std::cout << std::endl;

        // Check if the game is possible with the constraints
        if (isGamePossible(turns, maxCubes))
        {
            sumOfIds += gameId; // Add the game ID to the sum
        }
    }

    std::cout << "Sum of IDs of possible games: " << sumOfIds << std::endl;
    return 0;
}
