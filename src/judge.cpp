//
// Created by SonicLiam on 2022/11/17.
//

#include <fstream>
#include "../include/judge.h"

Judge::Judge(InputDir *inputDir, int executeTimes) {
    this->inputDir = inputDir;
    this->executeTimes = executeTimes;

}

void Judge::judge() {
    vector<ProgramDir> programDirs = inputDir->getProgramDirs();
    for (auto &programDir : programDirs) {
        auto files = programDir.getFileNames();
        for(auto &file1 : files){
            for(auto &file2 : files){
                if(file1 == file2){
                    continue;
                }
                judgeResult judgeResult(file1, file2, true);
                for(int i = 0; i < executeTimes; i++){
                    bool result;
                    string result_file1 = programDir.getDir() + "/result/" + to_string(i) + "/" + file1.substr(file1.find_last_of('/') + 1, file1.find_last_of('.') - file1.find_last_of('/') - 1) + ".txt";
                    string result_file2 = programDir.getDir() + "/result/" + to_string(i) + "/" + file2.substr(file2.find_last_of('/') + 1, file2.find_last_of('.') - file2.find_last_of('/') - 1) + ".txt";
                    string command = "diff " + result_file1 + " " + result_file2 + " > /dev/null";
                    result = system(command.c_str());
                    if(result != 0){
                        judgeResult.result = false;
                        break;
                    }
                }
                bool result_exist = false;
                for(auto &judgeResult1 : judgeResults){
                    if(judgeResult == judgeResult1){
                        result_exist = true;
                        break;
                    }
                }
                if(!result_exist){
                    judgeResults.push_back(judgeResult);
                }
            }
        }
    }
}

vector<judgeResult> Judge::getJudgeResults() const {
    return judgeResults;
}