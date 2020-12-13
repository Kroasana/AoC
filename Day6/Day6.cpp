#include<iostream>
#include<fstream>
#include<string>
#include<bitset>



int main(){
    ///initialize file connections
    std::ifstream iFile ("input.txt");
    std::ofstream oFile ("output.txt");

    std::string line;///read each line
    int answer1 = 0, answer2 = 0;

    std::bitset<26> bset;
    std::bitset<26> bset2;
    bset2.set();
    std::bitset<26> currbset;

    if (iFile.is_open()){
        while ( getline (iFile,line) ){
            if(line == ""){
                answer1 += bset.count();
                answer2 += bset2.count();
                bset.reset();
                bset2.set();
            } else{
                for(int i = 0; i < line.size(); i++){
                    int idx = line[i] - 'a';
                    currbset.set(idx, true);
                    bset.set(idx, true);
                }
                bset2 &= currbset;
                currbset.reset();
            }
        }
    }
    answer1+=bset.count();
    answer2+=bset2.count();

    std::cout<< answer1 << ' ' << answer2 <<'\n';
    oFile    << answer1 << ' ' << answer2 <<'\n';

    iFile.close();
    oFile.close();
    return 0;
}
