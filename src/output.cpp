//
// Created by SonicLiam on 2022/11/17.
//

#include "../include/output.h"
#include <fstream>

Output::Output(Judge *judge) {
    this->judge = judge;
}

void Output::output() {
    vector<judgeResult> judgeResults = judge->getJudgeResults();
    string command = "rm -rf output";
    system(command.c_str());
    command = "mkdir -p output";
    system(command.c_str());
    ofstream equal_f("output/equal.csv");
    ofstream unequal_f("output/unequal.csv");
    equal_f << "file1,file2" << endl;
    unequal_f << "file1,file2" << endl;
    for(auto &judgeResult : judgeResults){
        if(judgeResult.result){
            equal_f << judgeResult.file1 << "," << judgeResult.file2 << endl;
        } else{
            unequal_f << judgeResult.file1 << "," << judgeResult.file2 << endl;
        }
    }
}

