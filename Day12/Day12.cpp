#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<stdlib.h>
///converts strings to long longs.

int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

/// 0 - east, 1 - north, 2 - west, 3 - south
int travelled[4];

///first is EW, second is NS
std::pair<long long,long long> waypoint;
std::pair<long long,long long> ship;

int main(){
    ///initialize file connections.
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;
    long long answer1 = 0,answer2 = 0;

    /// initial coordinates of the ship and waypoint
    waypoint.first = 10;
    waypoint.second = 1;
    ship.first = 0;
    ship.second = 0;

    ///initialise both seat matrices
    if (iFile.is_open()){
        int fw = 0;
        while ( getline (iFile,line) ){
            int magnitude = strToInt(line.substr(1));
            if(line[0] == 'E'){
                travelled[0] += magnitude;
                waypoint.first += magnitude;
            }
            if(line[0] == 'N'){
                travelled[1] += magnitude;
                waypoint.second += magnitude;
            }
            if(line[0] == 'W'){
                travelled[2] += magnitude;
                waypoint.first -= magnitude;
            }
            if(line[0] == 'S'){
                travelled[3] += magnitude;
                waypoint.second -= magnitude;
            }
            if(line[0] == 'F'){
                travelled[fw] += magnitude;
                ship.first  += waypoint.first * magnitude;
                ship.second += waypoint.second * magnitude;
            }
            if(line[0] == 'L'){
                fw = (fw + (magnitude/90))%4;

                ///rotate 90 degrees counterclockwise per step
                for(int i = 0; i < magnitude/90; i++){
                    int x = waypoint.first;
                    int y = waypoint.second;
                    waypoint.first = y * (-1);
                    waypoint.second = x;
                }
            }
            if(line[0] == 'R'){
                fw = (fw - (magnitude/90) + 4)%4;

                ///rotate 90 degrees clockwise per step
                for(int i = 0; i < magnitude/90; i++){
                    int x = waypoint.first;
                    int y = waypoint.second;
                    waypoint.first = y;
                    waypoint.second = x * (-1);
                }
            }
        }
    }

    answer1 = abs(travelled[0] - travelled[2]) + abs(travelled[1] - travelled[3]);
    answer2 = abs(ship.first) + abs(ship.second);

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
