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

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;
    int length = 0, depth = 0, depth2 = 0, aim = 0;
    std::string line;///read each line
    int lineCount=0;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            int split = line.find(' ');
            int num = strToInt(line.substr(line.size()-1, 1));
            switch (split) {
            case 2:
                depth = std::max(depth - num, 0);
                aim = std::max(aim - num, 0);
                break;
            case 4:
                depth += num;
                aim += num;
                break;
            case 7:
                length += num;
                depth2 += num*aim;
                break;
            default: break;
            }
        }
        answer1 = length * depth;
        answer2 = length * depth2;
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
