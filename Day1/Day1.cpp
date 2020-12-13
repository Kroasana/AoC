#include<iostream>
#include<fstream>
#include<string>
#include<vector>

///converts a string to an integer
///assumes that all characters will be of integers
int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

///finds 2 numbers that sum to 2020 and returns their product
int find2020_2(std::vector<int> v){
    int sz = v.size();
    for(int i = 0; i < sz-1; i++){
        ///std::cout<<nums[i]<<'\n';
        for(int j = 0; j <sz; j++){
            if(v[i] + v[j] == 2020){
                return v[i] * v[j];
            }
        }
    }
    return 0;
}

///finds 3 numbers that sum to 2020 and returns their product
int find2020_3(std::vector<int> v){
    int sz = v.size();

    for(int i = 0; i < sz - 2; i++){
        for(int j = i + 1; j <sz - 1; j++){
            for(int k = j + 1; k < sz; k++){
                if(v[i] + v[j] + v[k] == 2020){
                    return v[i] * v[j] * v[k];
                }
            }
        }
    }
    return 0;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;

    std::string line;///read each line
    std::vector<int>nums;///store the numbers
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            nums.push_back(strToInt(line));
        }
    }

    answer1 = find2020_2(nums);
    answer2 = find2020_3(nums);

    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
