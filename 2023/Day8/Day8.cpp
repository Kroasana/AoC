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

long long gcd(long long int a, long long int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

template <typename TI, typename T>
std::vector<T> mapVector(std::vector<TI> input, std::function<T(TI)> func) {
    std::vector<T> result;
    for (TI inputElement : input) {
        result.push_back(func(inputElement));
    }
    return result;
}

// TODO: Export the functions to a utils header

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    auto tStart = std::chrono::high_resolution_clock::now();

    long long answer1 = 0, answer2 = 0;
    std::string line;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::queue<char> queue;
    std::queue<char> queue2;
    if (iFile.is_open()) {
        // Read the input file line by line.
        getline(iFile, line);
        for (char c : line) {
            queue.push(c);
        }
        queue2 = queue;
        getline(iFile, line);

        std::vector<std::string> current2;
        while (getline(iFile, line)) {
            std::string key = split(line, '=')[0];
            if (key[2] == 'A')
                current2.push_back(key);
            std::string left = split(split(split(line, '=')[1], ',')[0], '(')[0];
            std::string right = split(split(split(line, '=')[1], ',')[1], ')')[0];
            map[key] = {left, right};
        }

        std::string current = "AAA";
        while (current != "ZZZ") {
            char step = queue.front();
            queue.pop();
            queue.push(step);
            if (step == 'L') {
                current = map[current].first;
            } else {
                current = map[current].second;
            }
            answer1++;
        }
        bool allEndWithZ = false;
        std::vector<long long> individualAnswers;
        for (int thread = 0; thread < current2.size(); thread++) {
            std::queue<char> lq = queue2;  // local queue
            current = current2[thread];
            long long currAns = 0;
            while (current[2] != 'Z') {
                char step = lq.front();
                lq.pop();
                lq.push(step);
                if (step == 'L') {
                    current = map[current].first;
                } else {
                    current = map[current].second;
                }
                currAns++;
            }
            individualAnswers.push_back(currAns);
        }
        answer2 = individualAnswers[0];
        for (int i = 1; i < individualAnswers.size(); i++) {
            answer2 = lcm(answer2, individualAnswers[i]);
        }
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
