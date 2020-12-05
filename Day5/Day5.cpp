#include<iostream>
#include<fstream>
#include<string>

///Converts strings of BRTL to binary with B,R = 1, T,L = 0
int strToBinaryToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer *= 2;
        if(s[i] == 'B' || s[i] == 'R')
            answer += 1;
    }
    return answer;
}

bool presentSeat[1024];

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;///read each line
    int answer1 = 0, answer2 = 0;

    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            int aux = strToBinaryToInt(line);
            if(aux > answer1)
                answer1 = aux;
            presentSeat[aux] = true;
        }
    }
    for(int i = 1 ; i < 987; i++)
        if(!presentSeat[i] && presentSeat[i - 1] && presentSeat[i + 1])
            answer2 = i;
    std::cout<<answer1<<' '<<answer2<<'\n';



    iFile.close();
    oFile.close();
    return 0;
}
