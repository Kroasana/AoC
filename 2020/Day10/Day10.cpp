#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<bits/stdc++.h>
///converts strings to long longs.
int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

int nums[128];
long long dp[128];
int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");
    std::string line;

    long long answer1 = 0,answer2 = 0;
    int cntLines = 0;
    int jolt1 = 0;
    int jolt2 = 0;
    int jolt3 = 0;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            cntLines++;
            nums[cntLines] = strToInt(line);
        }
        cntLines++;
        std::sort(nums,nums+cntLines);
        nums[cntLines] = nums[cntLines - 1] + 3;
        cntLines++;
        for(int i = 0; i < cntLines; i++){
            if(nums[i] - answer1 == 1)
                jolt1++;
            else if(nums[i] - answer1 == 2)
                jolt2++;
            else if(nums[i] - answer1 == 3)
                jolt3++;
            answer1 = nums[i];
        }
        answer1 = jolt1 * jolt3;
        dp[0] = 1;
        if(nums[1] <= 3)
            dp[1] = 1;
        if(nums[2] - nums[1] <= 3)
            dp[2]++;
        if(nums[2] - nums[0] <= 3)
            dp[2]++;
        for(int i = 3; i < cntLines; i++){
            dp[i] = dp[i-3]*(nums[i] - nums[i-3] <= 3) +
                    dp[i-2]*(nums[i] - nums[i-2] <= 3) +
                    dp[i-1]*(nums[i] - nums[i-1] <= 3);
        }
    }
    answer2 = dp[cntLines-1];

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
