#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>
#include<map>
///converts strings to long longs.
bool isDigit(char c){
    return c >= '0' && c <= '9';
}

int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

long long strToLL(std::string s){
    long long answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

std::vector<int> split (const std::string &s, char delim) {
    std::vector<int> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (strToInt(item));
    }
    return result;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("testinput.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string line;///read each line
    if (iFile.is_open()){
        while ( getline (iFile,line) ){

        }
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
