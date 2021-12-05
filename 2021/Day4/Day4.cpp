#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>
#include<map>
#include <sstream>

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

std::vector<int> split (const std::string &s, char delim) {
    std::vector<int> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        if(item != "")
            result.push_back (strToInt(item));
    }
    return result;
}

struct card{
    std::vector<int> nums[5];
    bool got[5][5];
    int col[5];
    int row[5];
} emptycard;

int calculateScore(card winner, int multiplier){
    int answer = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(!winner.got[i][j]){
                answer += winner.nums[i][j];
            }
        }
    }
    answer *= multiplier;
    return answer;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string line;///read each line
    std::vector<int> numbers;
    std::vector<card> cards;

    if (iFile.is_open()){
        getline(iFile, line);
        numbers = split(line, ',');
        getline(iFile, line); ///should be empty

        while ( getline (iFile,line) ){
            card curr = emptycard;
            curr.nums[0] = split(line, ' ');
            for(int i = 1; i < 5; i++){
                getline(iFile, line);
                curr.nums[i] = split(line, ' ');
            }
            cards.push_back(curr);
            getline(iFile, line); ///should be empty
        }
    }
    bool win = false;
    bool won[cards.size()];
    for(int i = 0; i < cards.size(); i++)
        won[i] = false;
    int leftToWin = cards.size();
    for(int n = 0; n < numbers.size(); n++){
        int currNum = numbers[n];
        for(int c = 0; c < cards.size(); c++){
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(cards[c].nums[i][j] == currNum){
                        if(cards[c].got[i][j] == false){
                            cards[c].got[i][j] = true;
                            cards[c].col[j]++;
                            cards[c].row[i]++;
                            if(cards[c].col[j] == 5 || cards[c].row[i] == 5){
                                if(!win)answer1 = calculateScore(cards[c], currNum);
                                win = true;
                                if(!won[c]){
                                    leftToWin--;
                                    if(leftToWin == 0){
                                        answer2 = calculateScore(cards[c], currNum);
                                    }
                                }
                                won[c] = true;

                            }
//                            std::cout<<currNum<<' '<<cards[c].col[j]<<' '<<cards[c].row[i]<<'\n';
                        }
                    }
                }
            }
        }
    }

    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
