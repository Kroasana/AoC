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

struct Hand {
    std::string hand;
    int type;
    int bid;
};

struct Hand2 {
    std::string hand;
    int type;
    int bid;
};

std::map<char, int> priorities = {{'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};
std::map<char, int> priorities2 = {{'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 1}, {'Q', 12}, {'K', 13}, {'A', 14}};

bool operator<(Hand lhs, Hand rhs) {
    if (lhs.type != rhs.type) return lhs.type < rhs.type;

    for (int i = 0; i < lhs.hand.size(); i++) {
        if (lhs.hand[i] != rhs.hand[i]) {
            return priorities[lhs.hand[i]] < priorities[rhs.hand[i]];
        }
    }
    return lhs.bid < rhs.bid;
}

bool operator==(Hand lhs, Hand rhs) {
    return lhs.hand == rhs.hand && lhs.bid == rhs.bid;
}

bool operator<(Hand2 lhs, Hand2 rhs) {
    if (lhs.type != rhs.type) return lhs.type < rhs.type;

    for (int i = 0; i < lhs.hand.size(); i++) {
        if (lhs.hand[i] != rhs.hand[i]) {
            return priorities2[lhs.hand[i]] < priorities2[rhs.hand[i]];
        }
    }
    return lhs.bid < rhs.bid;
}

bool operator==(Hand2 lhs, Hand2 rhs) {
    return lhs.hand == rhs.hand && lhs.bid == rhs.bid;
}

Hand2 transformHand(Hand h) {
    Hand2 hand;
    hand.hand = h.hand;
    hand.bid = h.bid;
    hand.type = h.type;
    std::map<char, int> m;
    for (int i = 0; i < hand.hand.size(); i++) {
        if (m.find(hand.hand[i]) != m.end()) {
            m[hand.hand[i]]++;
        } else {
            m[hand.hand[i]] = 1;
        }
    }
    if (m.find('J') == m.end())
        return hand;
    switch (m['J']) {
        case 5:
        case 4:
            hand.type = 6;  // Five of a kind;
            return hand;
        case 3:
            if (m.size() == 2) {
                hand.type = 6;  // Five of a kind
                return hand;
            }
            if (m.size() == 3) {
                hand.type = 5;  // Four of a kind
                return hand;
            }
        case 2:
            if (m.size() == 2) {
                hand.type = 6;  // Five of a kind
                return hand;
            }
            if (m.size() >= 3) {
                hand.type = 7 - m.size();  // Four or three of a kind
            }
        case 1:
            if (m.size() == 2) {
                hand.type = 6;  // Five of a kind
                return hand;
            }
            if (m.size() == 3) {
                for (auto x : m) {
                    if (x.first != 'J' && x.second == 1) {
                        hand.type = 5;  // Four of a kind
                        return hand;
                    }
                }
                hand.type = 4;  // Full house
                return hand;
            }
            if (m.size() == 4) {
                hand.type = 3;  // Three of a kind
                return hand;
            }
            // m.size() == 5
            hand.type = 1;  // One pair
            return hand;
        default:
            return hand;
    }
}

int computeType(std::string hand) {
    std::map<char, int> m;
    for (int i = 0; i < hand.size(); i++) {
        if (m.find(hand[i]) != m.end()) {
            m[hand[i]]++;
        } else {
            m[hand[i]] = 1;
        }
    }

    switch (m.size()) {
        case 1:
            return 6;  // five of a kind
        case 2:
            for (auto x : m) {
                if (x.second == 4)
                    return 5;  // four of a kind
                if (x.second == 3)
                    return 4;  // full house
            }
            std::cout << "case overflow 2";
        case 3:
            for (auto x : m) {
                if (x.second == 3)
                    return 3;  // three of a kind
                if (x.second == 2)
                    return 2;  // two pair
            }
            std::cout << "case overflow 3";
        case 4:
            return 1;  // one pair
        case 5:
            return 0;  // high card
    }
}

main() {
    // initialize file connections
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");

    auto tStart = std::chrono::high_resolution_clock::now();

    int answer1 = 0, answer2 = 0;
    std::string line;

    std::vector<Hand> hands;
    std::vector<Hand2> hands2;

    if (iFile.is_open()) {
        // Read the input file line by line.
        while (getline(iFile, line)) {
            Hand hand;
            hand.hand = split(line, ' ')[0];
            hand.bid = strToInt(split(line, ' ')[1]);
            hand.type = computeType(hand.hand);
            hands.push_back(hand);
            Hand2 hand2 = transformHand(hand);
            hands2.push_back(hand2);
        }
        std::sort(hands.begin(), hands.end());
        std::sort(hands2.begin(), hands2.end());
        for (int i = 0; i < hands.size(); i++) {
            answer1 += hands[i].bid * (i + 1);
            answer2 += hands2[i].bid * (i + 1);
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
