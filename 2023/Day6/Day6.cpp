#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
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

template <typename TI, typename T>
std::vector<T> mapVector(std::vector<TI> input, std::function<T(TI)> func) {
    std::vector<T> result;
    for (TI inputElement : input) {
        result.push_back(func(inputElement));
    }
    return result;
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    auto tStart = std::chrono::high_resolution_clock::now();

    long long answer1 = 1, answer2 = 1;
    std::string line;

    std::vector<long long> times;
    std::vector<long long> distances;

    long long time2 = 0, distance2 = 0;
    if (iFile.is_open()) {
        // Read the input file line by line.
        getline(iFile, line);
        std::vector<std::string> vec = split(split(line, ':')[1], ' ');
        times = mapVector<std::string, long long>(vec, strToLL);
        for (int i = 0, max = vec.size(); i < max; i++) {
            for (char c : vec[i]) {
                time2 = time2 * 10 + charToInt(c);
            }
        }

        getline(iFile, line);
        vec = split(split(line, ':')[1], ' ');
        distances = mapVector<std::string, long long>(vec, strToLL);
        for (int i = 0, max = vec.size(); i < max; i++) {
            for (char c : vec[i]) {
                distance2 = distance2 * 10 + charToInt(c);
            }
        }

        for (int i = 0; i < times.size(); i++) {
            int min = -1, max = 0;
            for (long long t = 0; t < times[i]; t++) {
                long long dist = (times[i] - t) * t;
                if (dist > distances[i]) {
                    if (min == -1) min = t;
                    max = t;
                }
            }
            answer1 *= (1 + max - min);
        }
        int min2 = -1, max2 = 0;
        for (int t = 0; t < time2; t++) {
            long long dist = (time2 - t) * t;
            if (dist > distance2) {
                if (min2 == -1) min2 = t;
                max2 = t;
            }
        }
        answer2 = 1 + max2 - min2;
    }
    // Output to the console/terminal
    std::cout << answer1 << ' ' << answer2 << '\n';
    // Output to output.txt
    oFile << answer1 << ' ' << answer2 << '\n';

    auto tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_double = tEnd - tStart;
    std::cout << "Time: " << duration_double.count() << "ms\n";

    iFile.close();
    oFile.close();
    return 0;
}
