#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
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

int part2(std::string s) {
    std::unordered_map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};

    int firstDigit = 0, lastDigit = 0;
    int idx = s.size();
    for (int i = 1; i <= 9; i++) {
        int newIdx = s.find(m[i]);
        if (newIdx != std::string::npos && newIdx < idx) {
            idx = newIdx;
            firstDigit = i;
        }
        int newIdx2 = s.find('0' + i);
        if (newIdx2 != std::string::npos && newIdx2 < idx) {
            idx = newIdx2;
            firstDigit = i;
        }
    }
    std::reverse(s.begin(), s.end());
    idx = s.size();
    for (int i = 1; i <= 9; i++) {
        int newIdx = s.find(std::string(m[i].rbegin(), m[i].rend()));
        if (newIdx != std::string::npos && newIdx < idx) {
            idx = newIdx;
            lastDigit = i;
        }
        int newIdx2 = s.find('0' + i);
        if (newIdx2 != std::string::npos && newIdx2 < idx) {
            idx = newIdx2;
            lastDigit = i;
        }
    }
    return firstDigit * 10 + lastDigit;
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string line;

    if (iFile.is_open()) {
        // Read the input file line by line.
        while (getline(iFile, line)) {
            int firstDigit = 0, lastDigit = 0;
            for (char c : line) {
                if (!isDigit(c)) continue;
                int digit = charToInt(c);
                if (!firstDigit)
                    firstDigit = digit;
                lastDigit = digit;
            }
            answer1 += firstDigit * 10 + lastDigit;
            answer2 += part2(line);
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
