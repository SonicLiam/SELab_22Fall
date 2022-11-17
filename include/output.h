//
// Created by SonicLiam on 2022/11/17.
//

#ifndef SELAB_22FALL_OUTPUT_H
#define SELAB_22FALL_OUTPUT_H

#include "judge.h"

class Output {
private:
    Judge* judge;
public:
    explicit Output(Judge* judge);
    void output();
};

#endif //SELAB_22FALL_OUTPUT_H
