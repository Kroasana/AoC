#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>
#include<map>
///converts strings to long longs.
struct brick{
    int id;
    int l,r,t,b;
    int rotation;
};

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

std::vector<brick>wall;
int u[1024];
int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    brick kek;
    if (iFile.is_open()){
        long long currID,currLine,left,right,top,bot;
        while(getline (iFile, line)){
            if(line.substr(0,4) == "Tile"){
                currID = strToLL(line.substr(5,4));
                currLine = 0;
                kek.l = kek.r = kek.t = kek.b = 0;
                kek.ut = kek.ub = kek.ur = kek.ul = false;

            }

            if(line == ""){

            }
        }
    }
    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
