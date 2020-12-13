#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<bits/stdc++.h>
///converts strings to long longs.
int charToInt(char c){
    return c - '0';
}

int seats[100][100];
int seats2[100][100];
int newSeats[100][100];
int rows;
int cols;
int checkTaken1(int x,int y){
    int cntTaken = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(i != x || j != y){
                if(seats[i][j] == 2)
                    cntTaken++;
            }
        }
    }
    return cntTaken;
}

int checkTaken2(int x, int y){
    int cntTaken = 0;
    int taken[8];
    for(int i = 0; i < 8; i++)
        taken[i] = 0;
    int mini = std::min(x,std::min(y,std::min(rows - x, cols - y)));
    for(int i = 1; x - i > 0; i++){
        if(seats2[x-i][y] == 2){
            taken[0] = 1;
        }
        if(seats2[x-i][y] > 0)
            break;
    }
    for(int i = 1; x + i <= rows; i++){
        if(seats2[x+i][y] == 2){
            taken[1] = 1;
        }
        if(seats2[x+i][y] > 0)
            break;
    }

        for(int i = 1; y - i > 0; i++){
        if(seats2[x][y-i] == 2){
            taken[2] = 1;
        }
        if(seats2[x][y-i] > 0)
            break;
    }

    for(int i = 1; y + i <= cols; i++){
        if(seats2[x][y+i] == 2){
            taken[3] = 1;
        }
        if(seats2[x][y+i] > 0)
            break;
    }

    for(int i = 1; y + i <= cols && x + i <= rows; i++){
        if(seats2[x+i][y+i] == 2){
            taken[4] = 1;
        }
        if(seats2[x+i][y+i] > 0)
            break;
    }

    for(int i = 1; y - i > 0 && x + i <= rows; i++){
        if(seats2[x+i][y-i] == 2){
            taken[5] = 1;
        }
        if(seats2[x+i][y-i] > 0)
            break;
    }

    for(int i = 1; y - i > 0 && x - i > 0; i++){
        if(seats2[x-i][y-i] == 2){
            taken[6] = 1;
        }
        if(seats2[x-i][y-i] > 0)
            break;
    }

    for(int i = 1; y + i <= cols && x - i > 0; i++){
        if(seats2[x-i][y+i] == 2){
            taken[7] = 1;
        }
        if(seats2[x-i][y+i] > 0)
            break;
    }
    for(int i = 0; i < 8; i++)
        cntTaken += taken[i];
    return cntTaken;
}

int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");
    std::string line;

    long long answer1 = 0,answer2 = 0;

    ///initialise both seat matrices
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            rows++;
            for(int i = 0; i < line.size(); i++){
                if(line[i] == 'L')
                    seats[rows][i+1] = seats2[rows][i+1] = 1;
                else seats[rows][i+1] = 0;
            }
        }
    }
    cols = line.size();

    ///part 1
    int changes = 1;
    int cntTaken;
    while(changes != 0){
        changes = 0;
        for(int i = 1; i <= rows; i++){
            for(int j = 1; j <= cols; j++){
                cntTaken = 0;
                cntTaken = checkTaken1(i,j);
                if(seats[i][j] == 2 && cntTaken >= 4){
                    changes++;
                    newSeats[i][j] = 1;
                }
                if(seats[i][j] == 1 && cntTaken == 0){
                    changes++;
                    newSeats[i][j] = 2;
                }
            }
        }
        int cntTaken = 0;
        for(int i = 1; i <= rows; i++){
            for(int j = 1; j <= cols; j++){
                seats[i][j] = newSeats[i][j];
                if(seats[i][j] == 2)
                    cntTaken++;
            }
        }
        answer1 = cntTaken;
    }

    ///part 2
    changes = 1;
    while(changes != 0){
        changes = 0;
        for(int i = 1; i <= rows; i++){
            for(int j = 1; j <= cols; j++){
                cntTaken = 0;
                cntTaken = checkTaken2(i,j);
                if(seats2[i][j] == 2 && cntTaken >= 5){
                    changes++;
                    newSeats[i][j] = 1;
                }
                if(seats2[i][j] == 1 && cntTaken == 0){
                    changes++;
                    newSeats[i][j] = 2;
                }
            }
        }
        int cntTaken = 0;
        for(int i = 1; i <= rows; i++){
            for(int j = 1; j <= cols; j++){
                seats2[i][j] = newSeats[i][j];
                if(seats2[i][j] == 2)
                    cntTaken++;
            }
        }
        answer2 = cntTaken;
    }

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
