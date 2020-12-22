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
long long cnt2 = 0;
std::map<int,int>m;
std::map<long long,int>m2;
long long memory[500];
long long memory2[5000000];
std::bitset<36>mask;
std::bitset<36>pos;
std::bitset<36>ovrride;///for part 2
std::queue<int>maskq;///keeps X-es in part 2

///recursion to branch out each bit position of mem in q to 0 and 1
///if q is empty, it sets memory2 at location mem to data
void recurse(std::queue<int> q, long long mem, long long data){
    if(q.empty()){
        if(!m2[mem]){///count the entries in the map
            cnt2++;
            m2[mem] = cnt2;
        }
        memory2[m2[mem]] = data;
        return;
    }
    int x = q.front(); q.pop();
    long long y = 1;
    for(int i = 0; i < x; i++){
        y *= 2;
    }
    recurse (q,mem,data);
    recurse (q,mem ^ y ,data);
    return;
}

int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    int cnt = 0;
    ///initialise both seat matrices
    if (iFile.is_open()){
        while(getline (iFile, line)){
            ///setting the mask
            if(line[1] == 'a'){
                maskq = std::queue<int>();
                line = line.substr(7);

                for(int i = 0; i < line.size(); i++){
                    if(line[i] == '0'){
                        mask[35 - i] = false;
                        pos[35 - i] = true;
                        ovrride[35 - i] = false;
                    } else
                    if(line[i] == '1'){
                        mask[35 - i] = true;
                        pos[35 - i] = true;
                        ovrride[35 - i] = true;
                    } else
                    if(line[i] == 'X'){
                        mask[35 - i] = false;
                        pos[35 - i] = false;
                        maskq.push(35-i);
                        ovrride[35 - i] = false;
                        ///std::cout<<35-i<<' ';
                    }
                }
            } else{///setting a memory address to a value
                int start,len;
                long long num = 0, mem = 0;
                long long num2 = 0, mem2 = 0;
                for(int i = 0; i < line.size(); i++){
                    if(line[i] == '['){
                        start = i+1;
                    }
                    if(line[i] == ']'){
                        len = i - start;
                        mem = strToLL(line.substr(start,len));
                        mem2 = mem;
                        num = strToLL(line.substr(i + 4));
                        num2 = num;
                        break;
                    }
                }
                long long currPow = 1;///work with the mask to set the number for part 1, and for part 2 to set the memory
                for(int i = 0; i < 36; i++){
                    if(pos[i] == true){
                        ///std::cout<<currPow<<' '<<num<<' ';
                        if(mask[i] == true && num%(currPow*2) / currPow == 0)
                            num = num + currPow;
                        if(mask[i] == false && num%(currPow*2) / currPow == 1)
                            num = num - currPow;
                        if(ovrride[i] == true && mem2%(currPow*2) / currPow == 0)
                            mem2 = mem2 + currPow;
                    }
                    currPow *= 2;
                }
                if(!m[mem]){///count the entries in the memory map
                    cnt++;
                    m[mem] = cnt;
                }
                memory[m[mem]] = num;///set memory for part 1

                recurse(maskq,mem2,num2);///recurse for part 2
            }
        }
    }
    ///add up all the memory addresses' values.
    for(int i = 1; i <= cnt; i++)
        answer1 += memory[i];
    for(int i = 1; i <= cnt2; i++)
        answer2 += memory2[i];

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
