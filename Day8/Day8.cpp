#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>

///converts a string to an integer. Negates the number if isNegative is true.
int strToInt(std::string s, bool isNegative){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    if(isNegative)
        answer *= (-1);
    return answer;
}

int optype[1024],opval[1024];///store each operation type and it's value.
bool u[1024];///store which operations have been visited already.
int cntOps;///Counts the number of operations. Rolling count that allows the filling of the data structures.

///Solves problem 1 by finding the first operation that gets visited twice and returning the sum of acc operation values up till then as the first argument.
///Used by problem 2. If the loop terminates by reaching the end of the operations, then this is a solution for 2, and the second argument is true.
std::pair<int,bool> solve(){
    int currOp = 0, ans = 0;
    bool isTrueFor2 = false;
    while(!u[currOp] && currOp < cntOps){
        u[currOp] = true;
        if(optype[currOp] == 0){
            currOp++;
            continue;
        }
        if(optype[currOp] == 1){
            ans += opval[currOp];
            currOp++;
            continue;
        }
        if(optype[currOp] == 2){
            currOp += opval[currOp];
            continue;
        }
    }
    if(currOp == cntOps)
        isTrueFor2 = true;
    std::pair<int,bool> returnable;
    returnable.first = ans;
    returnable.second = isTrueFor2;
    return returnable;
}

///Computes which operation needs to be changed in order to solve problem 2.
int solve2(){
    for(int i = 0; i < cntOps; i++){
        if(optype[i] == 0 || optype[i] == 2){
            for(int j = 0; j < 1024; j++)
                u[j] = false;
            optype[i] ^= 2;
            std::pair<int,bool> ans = solve();
            if(ans.second == true){
                return ans.first;
            }
            optype[i] ^= 2;
        }
    }
}

int main(){
    ///Initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");
    std::string line;

    int answer1 = 0,answer2 = 0;
    std::string s;

    bool isNegative;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            if(line.substr(0,3) == "nop")
                optype[cntOps] = 0;
            if(line.substr(0,3) == "acc")
                optype[cntOps] = 1;
            if(line.substr(0,3) == "jmp")
                optype[cntOps] = 2;
            if(line[4] == '-')
                isNegative = true;
            else
                isNegative = false;
            opval[cntOps] = strToInt(line.substr(5),isNegative);
            cntOps++;
        }
    }
    int currOp = 0,prevOp = 0;
    answer1 = solve().first;
    answer2 = solve2();
    std::cout<<answer1<<' '<<answer2<<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
