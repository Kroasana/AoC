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
    int prevNum = INT_MAX;
    int currNum = 0;
    std::string line;///read each line
    std::vector<int>sums;///store the numbers
    int lineCount=0;
    if (iFile.is_open()){
        sums.push_back(0);
        while ( getline (iFile,line) ){
            sums.push_back(sums[sums.size()-1]+strToInt(line));
        }
    }
    for(int i = 2; i < sums.size(); i++){
        if(sums[i] - sums[i-1] > sums[i-1]-sums[i-2]){
            answer1++;
        }
        if(i > 3){
            if(sums[i]-sums[i-3] > sums[i-1] - sums[i-4]){
                answer2++;
            }
        }
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
