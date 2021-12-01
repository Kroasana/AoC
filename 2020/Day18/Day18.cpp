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

long long solve1(std::string line){
    long long answer = 0;
    std::queue<bool> ops;

    for(int i = 0; i < line.size(); i++){
        if(line[i] == ' ')
            continue;
        if(isDigit(line[i]) && answer == 0){
            answer = line[i] - '0';
            continue;
        }

        if(isDigit(line[i])){
            if(ops.front())
                answer *= line[i] - '0';
            else answer += line[i] - '0';
            ops.pop();
        }
        if(line[i] == '('){
            int cntb = 1;
            for(int j = i+1; j < line.size(); j++){
                if(line[j] == '(')
                   cntb++;
                if(line[j] == ')'){
                    cntb--;
                    if(cntb == 0){

                        std::string subline = line.substr(i+1, j - i-1);
                        long long number = solve1(subline);
                        if(answer != 0){
                            if(ops.front())
                                answer *= number;
                            else answer += number;
                            ops.pop();
                        }
                        else answer = number;
                        i = j;
                        break;
                    }
                }
            }
        }

        if(line[i] == '+')
            ops.push(false);
        if(line[i] == '*'){
            ops.push(true);
        }
    }
    return answer;
}

long long solve2(std::string line){
    long long answer = 0;

    for(int i = 0; i < line.size(); i++){
        if(line[i] == ' ')
            continue;
        if(isDigit(line[i]))
            answer += line[i] - '0';
        if(line[i] == '('){
            int cntb = 1;
            for(int j = i+1; j < line.size(); j++){
                if(line[j] == '(')
                   cntb++;
                if(line[j] == ')'){
                    cntb--;
                    if(cntb == 0){
                        std::string subline = line.substr(i+1, j - i-1);
                        long long number = solve2(subline);
                        answer += number;
                        i = j;
                        break;
                    }
                }
            }
        }

        if(line[i] == '*')
            return answer * solve2(line.substr(i + 1));
    }
    return answer;
}

int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    if (iFile.is_open()){
        while(getline (iFile, line)){
            answer1 += solve1(line);
            answer2 += solve2(line);
        }
    }
    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
