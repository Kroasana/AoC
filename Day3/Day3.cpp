#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::vector<std::string>loc;
///converts a string to an integer
///assumes that all characters will be of integers
int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

bool cntTrees(std::string line, int offset, int cntLines){
    return(line[(cntLines*offset)%line.size() ] == '#');
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line,aux;///read each line
    std::vector<int>nums;///store the numbers
    int answer1 = 0, answer2 = 0;
    int cntLines = 0;

    std::pair<int,int> slopes[5];
    int answers[5]={0,0,0,0,0};
    slopes[0] = std::pair<int,int>(1,1);
    slopes[1] = std::pair<int,int>(3,1);///answer to problem 1
    slopes[2] = std::pair<int,int>(5,1);
    slopes[3] = std::pair<int,int>(7,1);
    slopes[4] = std::pair<int,int>(1,2);

    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            for(int i = 0; i < 5; i++){
                if(cntLines % slopes[i].second == 0){
                    if(cntTrees(line,slopes[i].first,cntLines/slopes[i].second)){
                        answers[i]++;
                    }
                }
            }
            cntLines++;
        }
    }
    long long answer = 1;
    for(int i= 0 ; i < 5; i++)
        answer *= answers[i];

    std::cout<<answers[1]<<' '<<answer<<'\n';
    oFile    <<answers[1]<<' '<<answer<<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
