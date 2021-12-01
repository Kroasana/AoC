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
int lm[30000000];///last mention
int cnt = 0;
int lastnum = 0;
int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    ///initialise both seat matrices
    if (iFile.is_open()){
        getline (iFile, line);
        int last = 0;
        for(int i = 0; i < line.size(); i ++){
            if(line[i] == ','){
                lm[strToInt(line.substr(last, i-last))] = cnt;
                cnt++;
                last = i+1;
            }
        }
        lastnum = strToInt(line.substr(last, line.size()-last));
        lm[lastnum] = cnt;
        cnt++;
    }
    while(cnt < 30000000){
        int newnum = cnt - lm[lastnum] - 1;
        if(newnum == cnt - 1 && lastnum != 0)
            newnum = 0;
        lm[lastnum] = cnt - 1;
        lastnum = newnum;

        cnt++;
        if(cnt == 2020)
            answer1 = lastnum;
    }
    answer2 = lastnum;
    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
