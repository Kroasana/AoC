#include "Utils.h"

#include <chrono>
#include <fstream>
#include <iostream>

int main() {
    // initialize file connections
    std::ifstream iFile("testinput.txt");
    std::ofstream oFile("output.txt");

    auto tStart = std::chrono::high_resolution_clock::now();

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

    auto tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_double = tEnd - tStart;
    std::cout << "Time: " << duration_double.count() << "ms\n";

    iFile.close();
    oFile.close();
    return 0;
}
