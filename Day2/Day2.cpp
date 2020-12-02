#include<iostream>
#include<fstream>
#include<string>
#include<vector>

///converts a string to an integer
///assumes that all characters will be of integers
int strToInt(std::string s){
    int answer = 0;
    for(int i = 0; i < s.size(); i++){
        answer = answer*10 + s[i] - '0';
    }
    return answer;
}

///takes a line and reports if the password adheres to the provided specification
///assumes the lines are in the format as given by the challenges.
///problem == 1 assumes silver challenge, problem == 2 assumes gold challenge
bool isCorrect(std::string line, int problem){
    std::string aux = "";
    int num1,num2;///the two numbers at the beginning of the line
    char seeked;///the character to look out for
    bool ans2 = false;
    int flag = 0;///see which part of the line we're in.
    int counter1 = 0, counter2 = 0;
    for(int i = 0; i < line.size(); i++){
        char c = line[i];
        if(flag == 0){///fetching the first number
            if(c == '-'){///first number is over
                flag = 1;
                num1 = strToInt(aux);
                aux = "";
                continue;
            }
            aux += c;
        } else if (flag == 1) {///fetching 2nd number
            if(c == ' '){///2nd number is over
                flag = 2;
                num2 = strToInt(aux);
                aux = "";
                continue;
            }
            aux += c;
        } else if(flag == 2) {///fetching character of interest
            seeked = c;
            flag = 3;
            continue;
        } else if(flag == 3) {///going over the string afterwards
            if(c < 'a' || c > 'z')///string hasn't begun yet
                continue;
            counter2++;
            if(problem == 1 && c == seeked)
                counter1++;
            if (problem == 2 && c == seeked && (counter2 == num1 || counter2 == num2))
                ans2 ^= true;
        }
    }
    ///return answer corresponding to the problem
    if(problem == 1)
        return (counter1 >= num1 && counter1 <= num2);
    else
        return ans2;
}

int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line,aux;///read each line
    std::vector<int>nums;///store the numbers
    int answer1 = 0, answer2 = 0;
    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            if(isCorrect(line,1))
                answer1++;
            if(isCorrect(line,2))
                answer2++;
        }
    }
    std::cout<<answer1<<'\n'<<answer2<<'\n';


    iFile.close();
    oFile.close();
    return 0;
}
