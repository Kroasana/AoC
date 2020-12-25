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

std::map<std::string, int> fieldToInt;
std::vector<std::pair<std::pair<int,int>,std::pair<int,int> > > fields;
int myTicket[25],currTicket[25];
int locations[25];
int globalCnt;

void createFields(std::string line, int cnt){
    int cntNum = 0;
    int nums[4];
    int lastDiv = 0;
    for(int i = 0; i < line.size(); i++){
        if(line[i] == ':'){
            std::string subline = line.substr(0,i);
            fieldToInt[subline] = cnt;
            lastDiv = i+2;
        }
        if(line[i] == '-'){
            nums[cntNum] = strToInt(line.substr(lastDiv,i - lastDiv));
            lastDiv = i + 1;
            cntNum++;
        }
        if(line[i] == ' ' && isDigit(line[i+1])){
            lastDiv = i + 1;
        }
        if(line[i] == ' ' && isDigit(line[i-1])){
            nums[cntNum] = strToInt(line.substr(lastDiv,i - lastDiv));
            cntNum++;
        }
    }
    nums[cntNum] = strToInt(line.substr(lastDiv,line.size() - lastDiv));
    std::pair<std::pair<int,int>,std::pair<int,int> > field;
    field.first.first = nums[0];
    field.first.second = nums[1];
    field.second.first = nums[2];
    field.second.second = nums[3];
    fields.push_back(field);
}

int notHit = 0;
int findHits(int number){
    int cntHits = 0;
    for(int i = 0; i < fields.size(); i++){
        if((number >= fields[i].first.first && number <= fields[i].first.second) ||
           (number >= fields[i].second.first && number <= fields[i].second.second)){
            cntHits++;
        }
    }
    return cntHits;
}

int searchFields(int number){
    notHit = -1;
    int cntHits = findHits(number);
    if(cntHits > 0)
        for(int i = 0; i < fields.size(); i++){
            if(!((number >= fields[i].first.first && number <= fields[i].first.second) ||
               (number >= fields[i].second.first && number <= fields[i].second.second))){
                notHit = i+1;
            }
        }
    return cntHits;
}

bool notAvailable [25][25]; ///notAvailable[i][j] = feature j not available for column i
int colToFeature[25];
int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;
    int phase = 0,cntFields = 0;
    ///initialise both seat matrices
    if (iFile.is_open()){
        while(getline (iFile, line)){
            if(line == "")
                phase++;
            if(phase == 0){///create the fields where each number can fit
                createFields(line,cntFields);
                cntFields++;
            }

            if(phase == 1){
                if(isDigit(line[0])){
                    int last = 0,cnt = 0;
                    for(int i = 0; i < line.size(); i ++){
                        if(line[i] == ','){
                            cnt++;
                            myTicket[cnt] = strToInt(line.substr(last,i - last));
                            last = i+1;
                        }
                    }
                    cnt++;
                    myTicket[cnt] = strToInt(line.substr(last, line.size() - last));
                    globalCnt = cnt;
                }
            }

            if(phase == 2){
                if(isDigit(line[0])){
                    int last = 0,cnt = 0;
                    for(int i = 0; i < line.size(); i ++){
                        if(line[i] == ','){
                            cnt++;
                            currTicket[cnt] = strToInt(line.substr(last,i - last));
                            last = i+1;
                        }
                    }
                    currTicket[globalCnt] = strToInt(line.substr(last, line.size() - last));
                    int cntFound = 0;
                    for(int i = 1; i <= globalCnt; i++){
                        int searched = searchFields(currTicket[i]);
                        if(searched == 0)
                            answer1 += currTicket[i];
                        else {
                            cntFound++;
                            if(notHit != -1){
                                notAvailable[i][notHit] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 1; i <= globalCnt; i++){
        for(int j = 1; j <= globalCnt; j++)
            std::cout<<notAvailable[i][j]<<' ';
        std::cout<<'\n';
    }
    int onlyNotHit;
    for(int k = 1; k <= globalCnt; k++){
        for(int i = 1; i <= globalCnt; i++){
            int cntHits = 0;
            for(int j = 1; j <= globalCnt; j++){
                if(notAvailable[i][j])
                    cntHits++;
                else
                    onlyNotHit = j;
            }
            if(cntHits == globalCnt - 1){
                colToFeature[i] = onlyNotHit;
                for(int l = 1; l <= globalCnt; l++){
                    notAvailable[l][onlyNotHit] = true;
                }
            }
        }
    }
///    for(int i = 1; i <= globalCnt; i++){
///        for(int j = 1; j <= globalCnt; j++)
///            std::cout<<notAvailable[i][j]<<' ';
///        std::cout<<'\n';
///    }
    answer2 = 1;
    for(int i = 1; i <= globalCnt; i++){
        if(colToFeature[i] <= 6)
            answer2 *= myTicket[i];
    }
    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
