#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

/// @brief Utility function to check whether a character is a digit.
/// @param c The character to check.
/// @return true if c is a digit character, false otherwise.
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

/// @brief Utility function to convert a char to a digit.
/// @param c The character to convert.
/// @return -1 if c is not between '0' and '9', the respective digit as an int otherwise.
int charToInt(char c) {
    if (!isDigit(c)) return -1;
    return c - '0';
}

/// @brief Utility function to transform a string to a 32-bit integer
/// @param s The string to transform.
/// @return The integer value of the input string of decimal characters.
int strToInt(std::string s) {
    int answer = 0;
    for (int i = 0; i < s.size(); i++) {
        answer = answer * 10 + s[i] - '0';
    }
    return answer;
}

/// @brief Utility function to transform a string to a 64-bit integer.
/// @param s The string to transform.
/// @return The long long int value of the input string of decimal characters.
long long strToLL(std::string s) {
    long long answer = 0;
    for (int i = 0; i < s.size(); i++) {
        answer = answer * 10 + s[i] - '0';
    }
    return answer;
}

/// @brief Utility function to split a strings by a delimiter.
/// @param s The string of words to split up.
/// @param delim The delimiter by which to split the string.
/// @return A vector strings, containing the separated substrings.
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string substring;

    while (getline(ss, substring, delim)) {
        result.push_back(substring);
    }
    return result;
}

std::map<std::string, int> getDrawResults(std::string draw) {
    std::map<std::string, int> result;

    std::vector<std::string> balls = split(draw, ',');
    for (std::string ball : balls) {
        std::vector<std::string> cntColor = split(ball, ' ');
        result[cntColor[2]] = strToInt(cntColor[1]);
    }

    return result;
}

std::vector<std::map<std::string, int>> getGameResults(std::string game) {
    std::vector<std::map<std::string, int>> results;
    for (std::string draw : split(game, ';')) {
        results.push_back(getDrawResults(draw));
    }
    return results;
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    long long answer1 = 0, answer2 = 0;
    std::string line;

    if (iFile.is_open()) {
        // Read the input file line by line.
        int gameNumber;
        while (getline(iFile, line)) {
            std::vector<std::string> gameSplit = split(line, ':');
            gameNumber = strToInt(split(gameSplit[0], ' ')[1]);
            std::vector<std::map<std::string, int>> results = getGameResults(gameSplit[1]);
            bool isValid = 1;
            int minRed = 0;
            int minGreen = 0;
            int minBlue = 0;

            for (std::map<std::string, int> result : results) {
                std::cout << "Game " << gameNumber << ": " << result["red"] << ' ' << result["green"] << ' ' << result["blue"] << '\n';
                if (result["red"] > 12 || result["green"] > 13 || result["blue"] > 14) {
                    isValid = 0;
                }
                minRed = std::max(minRed, result["red"]);
                minGreen = std::max(minGreen, result["green"]);
                minBlue = std::max(minBlue, result["blue"]);
            }
            answer1 += isValid * gameNumber;
            answer2 += minRed * minGreen * minBlue;
        }
    }
    // Output to the console/terminal
    std::cout << answer1 << ' ' << answer2 << '\n';
    // Output to output.txt
    oFile << answer1 << ' ' << answer2 << '\n';

    iFile.close();
    oFile.close();
    return 0;
}
