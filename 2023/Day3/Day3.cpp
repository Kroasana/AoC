#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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

bool isSymbol(char c) {
    return (!isDigit(c) && c != '.');
}

bool isGear(char c) {
    return c == '*';
}

int main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    long long answer1 = 0, answer2 = 0;
    std::string line;

    if (iFile.is_open()) {
        int numbersCount = 0;
        int gearsCount = 0;
        std::map<int, int> numberMap;
        std::map<int, std::set<int>> gears;
        std::set<int> numbersToSum;
        std::map<int, int> prevPosToNumber;
        std::map<int, int> prevPosToGear;
        std::string prevRow;
        std::vector<std::string> matrix;

        while (getline(iFile, line)) {
            matrix.push_back(line);
        }
        int rowLength = matrix[0].size();
        int rowCount = matrix.size();
        for (int r = 0; r < rowCount; r++) {
            std::string row = matrix[r];
            std::map<int, int> posToNumber;
            std::map<int, int> posToGear;

            int currNumber = 0;
            for (int i = 0; i < rowLength; i++) {
                if (isDigit(row[i])) {
                    if (i > 0 && isDigit(row[i - 1])) {
                        currNumber = currNumber * 10 + charToInt(row[i]);
                    } else {
                        currNumber = charToInt(row[i]);
                    }
                    posToNumber[i] = numbersCount;

                    // Check for symbols to mark number for summing;
                    if (r > 0) {
                        if (i > 0 && isSymbol(prevRow[i - 1])) {
                            numbersToSum.insert(numbersCount);
                            if (isGear(prevRow[i - 1])) {
                                gears[prevPosToGear[i - 1]].insert(numbersCount);
                            }
                        }
                        if (i < rowLength - 1 && isSymbol(prevRow[i + 1])) {
                            numbersToSum.insert(numbersCount);
                            if (isGear(prevRow[i + 1])) {
                                gears[prevPosToGear[i + 1]].insert(numbersCount);
                            }
                        }
                        if (isSymbol(prevRow[i])) {
                            numbersToSum.insert(numbersCount);
                            if (isGear(prevRow[i])) {
                                gears[prevPosToGear[i]].insert(numbersCount);
                            }
                        }
                    }

                    // Record number if the current row ends.
                    if (i == rowLength - 1) {
                        numberMap[numbersCount++] = currNumber;
                        currNumber = 0;
                    }
                } else {
                    if (currNumber) {
                        numberMap[numbersCount++] = currNumber;
                        currNumber = 0;
                    }
                    if (isSymbol(row[i])) {
                        if (isGear(row[i])) {
                            gears[gearsCount] = {};
                            posToGear[i] = gearsCount;
                        }
                        // Adjacent numbers in current row.
                        if (i > 0 && isDigit(row[i - 1])) {
                            numbersToSum.insert(numbersCount - 1);
                            if (isGear(row[i])) {
                                gears[gearsCount].insert(numbersCount - 1);
                            }
                        }
                        if (i < rowLength - 1 && isDigit(row[i + 1])) {
                            numbersToSum.insert(numbersCount);
                            if (isGear(row[i])) {
                                gears[gearsCount].insert(numbersCount);
                            }
                        }

                        // Check for adjacent numbers in previous row.
                        if (r > 0) {
                            if (i > 0 && isDigit(prevRow[i - 1])) {
                                numbersToSum.insert(prevPosToNumber[i - 1]);
                                if (isGear(row[i])) {
                                    gears[gearsCount].insert(prevPosToNumber[i - 1]);
                                }
                            }
                            if (isDigit(prevRow[i])) {
                                numbersToSum.insert(prevPosToNumber[i]);
                                if (isGear(row[i])) {
                                    gears[gearsCount].insert(prevPosToNumber[i]);
                                }
                            }
                            if (i < rowLength - 1 && isDigit(prevRow[i + 1])) {
                                numbersToSum.insert(prevPosToNumber[i + 1]);
                                if (isGear(row[i])) {
                                    gears[gearsCount].insert(prevPosToNumber[i + 1]);
                                }
                            }
                        }
                        if (isGear(row[i]))
                            gearsCount++;
                    }
                }
            }
            prevRow = row;
            prevPosToNumber = posToNumber;
            prevPosToGear = posToGear;
        }

        for (int num : numbersToSum) {
            answer1 += numberMap[num];
        }
        for (int i = 0; i < gearsCount; i++) {
            std::set<int> gear = gears[i];
            if (gear.size() == 2) {
                int product = 1;
                for (int num : gear) {
                    product *= numberMap[num];
                }
                answer2 += product;
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
