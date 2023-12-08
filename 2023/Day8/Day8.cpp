#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "../Utils.h"

long long gcd(long long int a, long long int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
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
