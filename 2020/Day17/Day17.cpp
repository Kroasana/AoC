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
bool u[30][30][30];
bool un[30][30][30];

bool u2[30][30][30][30];
bool u2n[30][30][30][30];
//std::vector<std::vector<int> >currcubes;
//std::vector<std::vector<int> >nextcubes;

bool check(int x, int y, int z){
    int cntAdj = 0;
    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            for(int k = z - 1; k <= z + 1; k++){
                if(i == x && j == y && k == z)
                    continue;
                cntAdj+= u[i][j][k];
            }
        }
    }
    if((u[x][y][z] && cntAdj == 2) || cntAdj == 3)
        return true;
    return false;
}
bool check2(int x, int y, int z, int a){
    int cntAdj = 0;
    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            for(int k = z - 1; k <= z + 1; k++){
                for(int m = a - 1; m <= a + 1; m ++){
                    if(i == x && j == y && k == z && m == a)
                        continue;
                    cntAdj+= u2[i][j][k][m];
                }
            }
        }
    }
    if((u2[x][y][z][a] && cntAdj == 2) || cntAdj == 3)
        return true;
    return false;
}

int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    int phase = 0;
    int cnt = 0;
    if (iFile.is_open()){
        while(getline (iFile, line)){
            for(int i = 0; i < line.size(); i++)
                if(line[i] == '#'){
                    un[cnt+10][i+10][10] = true;
                    u2n[cnt+10][i+10][10][10] = true;
                }
            cnt++;
        }
    }
    for(phase = 0; phase < 6; phase++){
        for(int i = 1; i < 25; i++){
            for(int j = 1; j < 25; j++){
                for(int k = 1; k < 25; k++){
                    u[i][j][k] = un[i][j][k];
                    for(int m = 1; m < 25; m ++){
                        u2[i][j][k][m] = u2n[i][j][k][m];
                    }
                }
            }
        }
        for(int i = 1; i < 25; i++){
            for(int j = 1; j < 25; j++){
                for(int k = 1; k < 25; k++){
                    un[i][j][k] = check(i,j,k);
                    for(int m = 1; m < 25; m ++){
                        u2n[i][j][k][m] = check2(i,j,k,m);
                    }
                }
            }
        }
    }
    for(int i = 1; i < 25; i++){
            for(int j = 1; j < 25; j++){
                for(int k = 1; k < 25; k++){
                    answer1 += un[i][j][k];
                    for(int m = 1; m < 25; m ++){
                        answer2 += u2n[i][j][k][m];
                    }
                }
            }
    }
//    if (iFile.is_open()){
//        while(getline (iFile, line)){
//            for(int i = 0; i < line.size(); i++)
//                if(line[i] == '#'){
//                    std::vector<int> bruh;
//                    bruh.push_back(cnt+10);
//                    bruh.push_back(i+10);
//                    bruh.push_back(10);
//                    currcubes.push_back(bruh);
//                }
//            cnt++;
//        }
//    }
//
//    for(phase = 0; phase < 1; phase++){
//        for(int l = 0; l < currcubes.size(); l++){
//            ///std::cout<<currcubes[l][0]<<' '<<currcubes[l][1]<<' '<<currcubes[l][2]<<'\n'; /// check if input is parsed correctly, with phase < 1.
//            for(int i = currcubes[l][0] - 1; i <= currcubes[l][0] + 1; i++){
//                for(int j = currcubes[l][1] - 1; j <= currcubes[l][1] + 1; j++){
//                    for(int k = currcubes[l][2] - 1; k <= currcubes[l][2] + 1; k++){
//                        if(i == currcubes[l][0] && j == currcubes[l][1] && k == currcubes[l][2])
//                            continue;
//                        std::vector<int> bruh;
//                        bruh.push_back(i); bruh.push_back(j); bruh.push_back(k);
//                        nextcubes.push_back(bruh);
//                    }
//                }
//            }
//        }
//    }
    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
