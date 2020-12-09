#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>
///checks if a character is a digit.
bool isDigit(char c){
    return c >= '0' && c <= '9';
}
///converts a character to a digit.
int charToInt(char c){
    return c - '0';
}

std::vector<int> predecessor [1000];///stores the bags that contain each bag type
std::vector<std::pair<int,int> > successor [1000];///stores what type and how many of each bag type each bag type contains.
bool u[1000];///stores which bag types have been visited for 1 so as not to count them twice.
std::queue<int>q;/// used for the BFS for 1.

///visits and calls all (indirect) predecessors of the source.
int solve1(int source){
    int answer = 0;
    q.push(source);
    u[source] = true;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        for(int i = 0; i < predecessor[x].size(); i++){
            int pred = predecessor[x][i];
            if(!u[pred]){
                answer++;
                u[pred] = true;
                q.push(pred);
            }
        }
    }
    return answer;
}

///counts the number of bags that the bag labeled as idx must contain for 2.
int solve2(int idx, int val){
    int ans = 1;
    if(successor[idx].size() == 0)
        return val;
    for(int i = 0; i < successor[idx].size(); i++){
        ans = ans + solve2(successor[idx][i].first,successor[idx][i].second);
    }
    return val*ans;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");
    std::map<std::string, int> k;
    std::string line;
    int answer1 = 0;
    long long answer2 = 0;
    int cutoff = 0;
    int nextToMap = 1;
    std::string s;

    int from,to;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            for(int i = 0; i < line.size(); i ++){
                if(cutoff == 0 && isDigit(line[i])){
                    cutoff = i+2;

                    s = line.substr(0,cutoff - 16);
                    if(!k[s]){
                        k[s] = nextToMap;
                        nextToMap++;
                    }
                    from = k[s];
                }
                if(line[i] == ',' || line[i] == '.'){
                    s = line.substr(cutoff, i - cutoff- 4 - (line[i-1] == 's'));
                    if(!k[s] && cutoff != 0){
                        k[s] = nextToMap;
                        nextToMap++;
                    }
                    int amount = charToInt(line[cutoff-2]);
                    to = k[s];
                    if(to != 0 && from != 0 && amount > 0){
                        predecessor[to].push_back(from);
                        successor[from].push_back(std::pair<int,int>(to,amount));
                    }
                    cutoff = i + 4;
                }
            }
            cutoff = 0;
        }
    }
    answer1 = solve1(k["shiny gold"]);
    answer2 = solve2(k["shiny gold"],1) - 1;

    std::cout<<answer1<<' '<<answer2<<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
