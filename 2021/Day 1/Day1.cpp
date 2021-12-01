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
    std::vector<int>nums;///store the numbers
    int lineCount=0;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            nums.push_back(strToInt(line));
        }
    }
    std::vector<int>sums;
    sums.push_back(nums[0]+nums[1]+nums[2]);
    sums.push_back(nums[1]+nums[2]);
    sums.push_back(nums[2]);
    for(int i = 1; i < nums.size(); i++){
        if(nums[i]>nums[i-1]){
            answer1++;
        }
        if(i > 2){
            sums[sums.size() - 1] += nums[i];
            sums[sums.size() - 2] += nums[i];
            if(sums[sums.size() - 2] > sums[sums.size() - 3]){
                answer2++;
            }
            sums.push_back(nums[i]);
        }
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
