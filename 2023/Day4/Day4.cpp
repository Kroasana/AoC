#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

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
        trim(substring);
        if (substring.size())
            result.push_back(substring);
    }
    return result;
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string line;
    std::unordered_map<int, int> m;
    if (iFile.is_open()) {
        // Read the input file line by line.
        while (getline(iFile, line)) {
            std::set<int> winners;

            int cardNumber = strToInt(split(split(line, ':')[0], ' ')[1]);
            auto it = m.find(cardNumber);
            if (it == m.end()) {
                m[cardNumber] = 1;
            }

            std::string winning = split((split(line, ':')[1]), '|')[0];
            std::string mine = split((split(line, ':')[1]), '|')[1];

            for (std::string str : split(winning, ' ')) {
                winners.insert(strToInt(str));
            }

            int value = 0;
            int cnt = 0;
            for (std::string str : split(mine, ' ')) {
                int num = strToInt(str);

                auto it = winners.find(num);
                if (it != winners.end()) {
                    value = std::max(value + 1, value * 2);
                    cnt++;
                }
            }
            answer1 += value;
            answer2 += m[cardNumber];
            for (int newCard = cardNumber + 1; newCard <= cardNumber + cnt; newCard++) {
                auto it = m.find(newCard);
                if (it == m.end()) {
                    m[newCard] = 1;
                }
                m[newCard] = m[newCard] + m[cardNumber];
            }
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
