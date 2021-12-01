#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>

///converts strings to long longs.
long long strToLL(std::string s){
    long long answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

long long nums[25];///stores the last 25 nums.
long long allnums[1024];///stores all nums.

///checks if any two numbers among the last 25 add up to x.
bool checkIfAddsUp(long long x){
    for(int i = 0; i < 24; i++){
        for(int j = i + 1; j < 25; j++){
            if(nums[i] + nums[j] == x)
                return true;
        }
    }
    return false;
}

///solves problem 2 - finding a contiguous set of numbers between the 0th and the border that add up to sought.
///returns the sum of the maximum and minimum number among the set.
long long solve2(int border,long long sought){
    long long sum, mini, maxi;
    for(int i = 2; i < border; i++){
        for(int j = 0; j < border - i; j++){
            sum = 0;
            for(int k = j; k < j + i; k++)
                sum += allnums[k];

            if(sum == sought){
                mini = maxi = allnums[j];

                for(int k = j; k < j + i; k++){
                    if(allnums[k] < mini)
                        mini = allnums[k];
                    if(allnums[k] > maxi)
                        maxi = allnums[k];
                }
                return mini + maxi;
            }
        }
    }
    return 0;///shouldn't be reachable if input conforms to spec
}


int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");
    std::string line;

    long long answer1 = 0,answer2 = 0;
    int cntLines = 0;

    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            cntLines++;
            long long currnum = strToLL(line);
            allnums[cntLines] = currnum;

            if(cntLines <= 25){
                nums[cntLines % 25] = currnum;
                continue;
            }
            if(checkIfAddsUp(currnum))
                nums[cntLines % 25] = currnum;
            else {
                answer1 = currnum;
                answer2 = solve2(cntLines,answer1);
                break;
            }
        }
    }

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
