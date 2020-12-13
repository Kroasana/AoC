#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
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

long long mul_inv(long long m, long long b){
    long long b0 = b;
    long long x0 = 0, x1= 1;
    if (b == 1)
        return 1;
    while (m>1) {
        if(b == 0)
            break;
        long long q = m / b;
        long long x = m;
        m = b;
        b = x%b;
        x = x0;
        x0 = x1 -q *x0;
        x1 = x;
    }
    if (x1<0)
        x1+= b0;
    return x1;
}

std::vector <int> busses;
std::vector <int> offsets;
long long initial;


int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;

    ///initialise both seat matrices
    if (iFile.is_open()){
        getline (iFile, line);
        initial = strToInt(line);
        getline (iFile, line);
        std::string s;
        int counter = 0;
        for(int i = 0; i < line.size(); i++){
            if(line[i] == 'x')
                counter++;
            if(isDigit(line[i])){
                s = "";
                for(int j = i; j <= line.size(); j++){
                    if(j == line.size()){
                        i = j;
                        break;
                    } else {
                        if(!isDigit(line[j])){
                            i = j;
                            break;
                        }
                        s += line[j];
                    }
                }
                busses.push_back(strToInt(s));
                offsets.push_back(counter);
                counter++;
            }
        }
    }

    /// part 1
    int busSize = busses.size();
    int busSort [busSize];
    for(int j = 0; j < busSize; j++)
        busSort[j] = busses[j];

    std::sort(busSort,busSort+busses.size());
    int minWait = 1e9+7;
    for(int i = 0; i < busSize; i++){
        int waitingTime = (busSort[i] - (initial % busSort[i])) %busSort[i];
        if( waitingTime < minWait){
                minWait = waitingTime;
                answer1 = waitingTime * busSort[i];
            }
    }

    ///part 2
    long long bigMod = busses[0];
    long long smallmod;
    for(int i = 1; i < busSize; i++)
        bigMod = bigMod * busses[i];

    for(int i = 0; i < busSize; i++){
        offsets[i] = (busses[i] - offsets[i] % busses[i])%busses[i];
        smallmod = bigMod / busses[i];
        long long inv = mul_inv(smallmod, busses[i]);
        answer2 += offsets[i] * inv * smallmod;
    }
    answer2 %= bigMod;

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
