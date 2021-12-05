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

struct point {
    int x;
    int y;
};

struct lineStruct {
    point start;
    point dest;
};

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    int answer1 = 0, answer2 = 0;
    std::string readLine;///read each line
    std::vector<lineStruct> lines;
    int maxX = 0, maxY = 0;
    if (iFile.is_open()){
        while(getline (iFile,readLine)){
            int i = 0, j = 0;
            point start,dest;

            while(isDigit(readLine[j]))
                j++;
            start.x = strToInt(readLine.substr(0,j));
            i = ++j;
            while(isDigit(readLine[j]))
                j++;
            start.y = strToInt(readLine.substr(i, j-i));
             i = j += 4;
            while(isDigit(readLine[j]))
                j++;
            dest.x = strToInt(readLine.substr(i, j-i));
            i = ++j;
            while(isDigit(readLine[j]))
                j++;
            dest.y = strToInt(readLine.substr(i, j-i));

            if(start.x > maxX || dest.x > maxX)
                maxX = std::max(start.x,dest.x);
            if(start.y > maxY || dest.y > maxY)
                maxY = std::max(start.y,dest.y);
            lineStruct line;
            line.start = start;
            line.dest = dest;
            lines.push_back(line);
        }
    }
    std::cout<<maxX<<' '<<maxY<<'\n';
    char matrix[maxX+1][maxY+1];
    char matrix2[maxX+1][maxY+1];
    for(int i = 0; i <= maxX; i++)
        for(int j = 0; j <= maxY; j++){
            matrix[i][j] = 0;
            matrix2[i][j] = 0;
        }
    for(int l = 0; l < lines.size(); l++){
        lineStruct current = lines[l];
        if(current.start.x == current.dest.x){
            for(int i = std::min(current.start.y, current.dest.y) ; i <= std::max(current.start.y, current.dest.y); i++){
                matrix[current.start.x][i]++;
                matrix2[current.start.x][i]++;
                if(matrix[current.start.x][i] == 2)
                    answer1 ++;
                if(matrix2[current.start.x][i] == 2)
                    answer2 ++;
            }
        } else if (current.start.y == current.dest.y){
            for(int i = std::min(current.start.x, current.dest.x); i <= std::max(current.start.x, current.dest.x); i++){
                matrix[i][current.start.y]++;
                matrix2[i][current.start.y]++;
                if(matrix[i][current.start.y] == 2)
                    answer1 ++;
                if(matrix2[i][current.start.y] == 2)
                    answer2 ++;
            }
        } else
        for(int i = current.start.x <= current.dest.x ? current.start.x : current.dest.x,
                j = current.start.x <= current.dest.x ? current.start.y : current.dest.y;
                i <= std::max(current.start.x, current.dest.x);
        ){
            matrix2[i][j] ++;
            if(matrix2[i][j] == 2){
                answer2++;
            }
            if(current.start.x != current.dest.x)
                i++;
            if(current.start.y != current.dest.y){
                if(current.start.x <= current.dest.x){
                    if(current.start.y < current.dest.y)
                        j++;
                    else j--;
                } else {
                    if(current.dest.y < current.start.y)
                        j++;
                    else j--;
                }

            }
        }
//        std::cout<<current.start.x<<' '<<current.start.y<<' '<<current.dest.x<<' '<<current.dest.y<<'\n';
//        for(int i = 0; i <= maxX; i++){
//            for(int j = 0; j <= maxY; j++){
//                std::cout<<matrix2[j][i]-0<<' ';
//            }
//            std::cout<<'\n';
//        }
//        std::cout<<'\n';
    }
    std::cout<<answer1<<' '<<answer2<<'\n';
    oFile << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
