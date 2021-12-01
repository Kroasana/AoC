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

bool checkIfNum(std::string s){
    for(int i = 0; i < s.size(); i++)
        if(s[i]< '0' || s[i] > '9')
            return false;
    return true;
}

bool isCorrect(std::vector<std::string> v, std::vector<std::string> b, int problem){
    bool present[8];
    bool valid[8];
    for(int i = 0; i < 8; i++){
        present[i] = false;
        valid[i] = false;
    }
    valid[7] = true;
    if(v.size()<7)
        return false;
    for(int i = 0; i < v.size(); i++){
        if(v[i] == "byr"){
            present[0] = true;
            if(problem == 2){
                if(b[i].size() == 4){
                    if(checkIfNum(b[i])){
                        int byr = strToInt(b[i]);
                        if(byr >= 1920 && byr <= 2002){
                            valid[0] = true;
                        }
                    }
                }
            }
        }
        if(v[i] == "iyr"){
            present[1] = true;
            if(problem == 2){
                if(b[i].size() == 4){
                    if(checkIfNum(b[i])){
                        int iyr = strToInt(b[i]);
                        if(iyr >= 2010 && iyr <= 2020){
                            valid[1] = true;
                        }
                    }
                }
            }
        }
        if(v[i] == "eyr"){
            present[2] = true;
            if(problem == 2){
                if(b[i].size() == 4){
                    if(checkIfNum(b[i])){
                        int eyr = strToInt(b[i]);
                        if(eyr >= 2020 && eyr <= 2030){
                            valid[2] = true;
                        }
                    }
                }
            }
        }
        if(v[i] == "hgt"){
            present[3] = true;
            if(problem == 2){
                if(b[i].size() == 4){
                    if(b[i][2] == 'i' && b[i][3] == 'n'){
                        std::string x = "";
                        x += b[i][0];
                        x += b[i][1];
                        if(checkIfNum(x)){
                            int xa = strToInt(x);
                            if(xa >= 59 && xa <=76){
                                valid[3] = true;
                            }
                        }
                    }
                }
                if(b[i].size() == 5){
                    if(b[i][3] == 'c' && b[i][4] == 'm'){
                        std::string x = "";
                        x += b[i][0];
                        x += b[i][1];
                        x += b[i][2];
                        if(checkIfNum(x)){
                            int xa = strToInt(x);
                            if(xa >= 150 && xa <= 193){
                                valid[3] = true;
                            }
                        }
                    }
                }
            }
        }
        if(v[i] == "hcl"){
            present[4] = true;
            bool flaghcl = true;
            if(problem == 2){
                if(b[i].size() == 7){
                    if(b[i][0] == '#'){
                        for(int j = 1; j < 7; j++){
                            if(!((b[i][j] >= '0' && b[i][j] <= '9') || (b[i][j] >= 'a' && b[i][j] <= 'f')))
                                flaghcl = false;
                        }
                        if(flaghcl){
                            valid[4] = true;
                        }
                    }
                }
            }
        }
        if(v[i] == "ecl"){
            present[5] = true;
            if(problem == 2)
                if(b[i] == "amb" || b[i] == "blu" || b[i] == "brn" || b[i] == "gry" || b[i] == "grn" || b[i] == "hzl" || b[i] == "oth"){
                    valid[5] = true;
                }
        }
        if(v[i] == "pid"){
            present[6] = true;
            if(problem == 2)
                if(b[i].size() == 9 && checkIfNum(b[i])){
                    valid[6] = true;
                }
        }
        if(v[i] == "cid"){
            present[7] = true;
            valid[7] = true;
        }
    }
    if(problem == 1)
        return (present[0] && present[1] && present[2] && present[3] && present[4] && present[5] && present[6]);
    return (valid[0] && valid[1] && valid[2] && valid[3] && valid[4] && valid[5] && valid[6]) ;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line,aux;///read each line
    std::vector<int>nums;///store the numbers
    int answer1 = 0, answer2 = 0;
    int cntPassports = 0;
    std::vector<std::string> currPasport;
    std::vector<std::string> currValues;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            if(line == ""){
                cntPassports++;
                answer1 += isCorrect(currPasport,currValues,1);
                answer2 += isCorrect(currPasport,currValues,2);
                currPasport.clear();
                currValues.clear();
            } else {
                std::string aux = "";
                for (int i = 0; i < line.size(); i++){
                    if(line[i] == ':' && i < line.size()-1){
                        if(line[i+1] != ' '){
                            currPasport.push_back(aux);
                            aux = "";
                        }
                    } else
                    if(line[i] == ' ' || i+1 == line.size()){
                        if(i+1 == line.size())
                            aux += line[i];
                        currValues.push_back(aux);
                        aux="";

                    }
                    else aux +=line[i];
                }
            }
        }
        answer1 += isCorrect(currPasport,currValues,1);
        answer2 += isCorrect(currPasport,currValues,2);

    }

    std::cout<<answer1 << ' ' << answer2 <<'\n';
    oFile <<   answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
