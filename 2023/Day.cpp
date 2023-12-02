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

/// @brief Utility function to split a sequence of numbers string representation by a delimiter.
/// @param s The string of integer numbers to split up.
/// @param delim The delimiter by which to split the string.
/// @return A vector of integers, containing the separate numbers.
std::vector<int> split(const std::string &s, char delim) {
    std::vector<int> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(strToInt(item));
    }
    return result;
}

int main() {
    // initialize file connections
    std::ifstream iFile("testinput.txt");
    std::ofstream oFile("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string line;

    if (iFile.is_open()) {
        // Read the input file line by line.
        while (getline(iFile, line)) {
            // Do stuff with line
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
