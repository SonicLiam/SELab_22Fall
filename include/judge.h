//
// Created by SonicLiam on 2022/11/17.
//

#ifndef SELAB_22FALL_JUDGE_H
#define SELAB_22FALL_JUDGE_H

#include <utility>

#include "execute.h"

struct judgeResult{
    string file1;
    string file2;
    bool result;
    judgeResult(string file1, string file2, bool result){
        this->file1 = std::move(file1);
        this->file2 = std::move(file2);
        this->result = result;
    };
    bool operator == (const judgeResult &judgeResult1) const{
        return (file1 == judgeResult1.file1 && file2 == judgeResult1.file2)
        || (file1 == judgeResult1.file2 && file2 == judgeResult1.file1);
    }

};

class Judge {
private:
    InputDir* inputDir;
    int executeTimes;
    vector<judgeResult> judgeResults;
public:
    Judge(InputDir* inputDir, int executeTimes);
    void judge();
    vector<judgeResult> getJudgeResults() const;
};

#endif //SELAB_22FALL_JUDGE_H
