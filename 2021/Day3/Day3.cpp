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

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;
    int gamma = 0, epsilon = 0;
    std::string line;///read each line
    int numlines = 0;
    int lineCount = 0;
    std::vector<std::string> lines1;
    std::vector<std::string> lines2;
    if (iFile.is_open()){
        getline (iFile,line);
        int maxNum = (1 << (line.size())) - 1;
        int counts[line.size()];
        int counts2[line.size()];
        for(int i=0; i < line.size(); i++){
            counts[i]=0;
            counts2[i]=0;
        }
        do {
            numlines++;
            for(int i = 0; i < line.size(); i++){
                if(line[i] == '1') {
                    counts[i]++;
                    counts2[i]++;
                }
            }
            lines1.push_back(line);
            lines2.push_back(line);
        }
        while ( getline (iFile,line) );
        for(int i = 0; i < line.size(); i++){
            if(counts[i] >= numlines/2)
                gamma += (1 << (line.size() - i-1));
        }
        epsilon = maxNum - gamma;
        answer1 = epsilon * gamma;

        for(int i = 0; i < line.size(); i++){
            if(lines1.size() > 1){
                bool more1 = counts[i] >= lines1.size()*1.0/2;
                for(int l = 0; l < lines1.size(); l++){

                    if(more1){
                        while(l < lines1.size() && lines1[l][i] == '0'){
                            for(int bit = 0; bit < line.size(); bit++){
                                if(lines1[l][bit] == '1')
                                    counts[bit]--;
                            }
                            lines1.erase(lines1.begin()+l);
                        }
                    } else {
                        while(l < lines1.size() && lines1[l][i] == '1'){
                            for(int bit = 0; bit < line.size(); bit++){
                                if(lines1[l][bit] == '1')
                                    counts[bit]--;
                            }
                            lines1.erase(lines1.begin()+l);
                        }
                    }
                }
            }
            if(lines2.size() > 1){
                bool more1 = counts2[i] >= lines2.size()*1.0/2;
                for(int l = 0; l < lines2.size(); l++){
                    if(more1){
                        while(l < lines2.size() && lines2[l][i] == '1'){
                            for(int bit = 0; bit < line.size(); bit++){
                                if(lines2[l][bit] == '1')
                                    counts2[bit]--;
                            }
                            lines2.erase(lines2.begin()+l);
                        }
                    } else {
                        while(l < lines2.size() && lines2[l][i] == '0'){
                            for(int bit = 0; bit < line.size(); bit++){
                                if(lines2[l][bit] == '1')
                                    counts2[bit]--;
                            }
                            lines2.erase(lines2.begin()+l);
                        }
                    }
                }
            }
        }
         int line1=0, line2 = 0;
         for(int i = 0; i < line.size(); i++){
            if(lines1[0][i] == '1')
                line1 += (1 << (line.size() - i-1));
            if(lines2[0][i] == '1')
                line2 += (1 << (line.size() - i-1));
        }
        answer2 = line1*line2;
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
