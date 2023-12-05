#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
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

struct rang {
    long long start;
    long long end;
};

bool operator<(rang lhs, rang rhs) {
    return lhs.start < rhs.start;
}

std::pair<rang, rang> splitRange(rang range, long long splitStart) {
    rang temp;
    std::pair<rang, rang> out;
    temp.start = range.start;
    temp.end = splitStart - 1;
    out.first = temp;
    temp.start = splitStart;
    temp.end = range.end;
    out.second = temp;
    return out;
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");
    auto tStart = std::chrono::high_resolution_clock::now();
    long long answer1 = 0, answer2 = 0;
    std::string line;

    if (iFile.is_open()) {
        getline(iFile, line);
        std::vector<std::string> seedStrings = split(split(line, ':')[1], ' ');
        std::set<long long> source, destination;
        std::set<rang> source2, destination2;
        for (std::string seed : seedStrings) {
            source.insert(strToLL(seed));
        }
        for (int i = 0; i < seedStrings.size(); i += 2) {
            rang range;
            range.start = strToLL(seedStrings[i]);
            range.end = range.start + strToLL(seedStrings[i + 1]) - 1;
            source2.insert(range);
        }

        getline(iFile, line);
        for (int i = 0; i < 7; i++) {
            getline(iFile, line);
            // seed-to-soil
            while (getline(iFile, line)) {
                if (!line.size()) break;
                std::set<long long> toRemove;
                std::set<rang> toRemove2;
                std::vector<std::string> mapStrings = split(line, ' ');
                long long dst = strToLL(mapStrings[0]), src = strToLL(mapStrings[1]), rng = strToLL(mapStrings[2]);
                for (long long seed : source) {
                    if (seed >= src && seed < src + rng) {
                        destination.insert(dst + (seed - src));
                        toRemove.insert(seed);
                    }
                }
                for (long long seed : toRemove) {
                    source.erase(seed);
                }

                for (rang range : source2) {
                    std::pair<rang, rang> splitResult;
                    // Begins before src, ends at or after src
                    if (range.start < src && range.end >= src) {
                        toRemove2.insert(range);
                        splitResult = splitRange(range, src);
                        destination2.insert(splitResult.first);
                        // Ends before src+rng
                        if (range.end < src + rng) {
                            splitResult.second.start = dst;
                            splitResult.second.end = dst - src + splitResult.second.end;
                            destination2.insert(splitResult.second);
                        } else {  // Ends at or after src+rng
                            splitResult = splitRange(splitResult.second, src + rng);
                            splitResult.first.start += dst - src;
                            splitResult.first.end = dst + rng - 1;

                            destination2.insert(splitResult.first);
                            destination2.insert(splitResult.second);
                        }
                    } else if (range.start >= src && range.start < src + rng) {
                        // Starts after src, before src+rng
                        toRemove2.insert(range);
                        // Ends after src+rng
                        if (range.end >= src + rng) {
                            splitResult = splitRange(range, src + rng);
                            splitResult.first.start += dst - src;
                            splitResult.first.end = dst + rng - 1;
                            destination2.insert(splitResult.first);
                            destination2.insert(splitResult.second);
                        } else {  // Entirely within the range
                            rang newRange = range;
                            newRange.start += dst - src;
                            newRange.end += dst - src;
                            destination2.insert(newRange);
                        }
                    }
                }
                for (rang range : toRemove2) {
                    source2.erase(range);
                }
            }
            for (long long seed : source) {
                destination.insert(seed);
            }
            for (rang range : source2) {
                destination2.insert(range);
            }

            source = destination;
            source2 = destination2;

            destination = {};
            destination2 = {};
        }
        long long min = 1e18 + 7;
        for (long long seed : source) {
            min = std::min(seed, min);
        }
        answer1 = min;

        long long min2 = 1e18 + 7;
        for (rang range : source2) {
            if (range.start < min2) min2 = range.start;
        }
        answer2 = min2;
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
