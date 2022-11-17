//
// Created by SonicLiam on 2022/11/10.
//

#ifndef SELAB_22FALL_EXECUTE_H
#define SELAB_22FALL_EXECUTE_H

#include "input.h"
#include <map>

struct programInput{
    enum type{
        intType,
        charType,
        stringType
    }type;
    int floor;
    int ceil;
};

class Execute {
private:
    ProgramDir* programDir;
    map<string, string> result;
    string generateRandomInput(int argNum, vector<programInput> programInputs);
public:
    explicit Execute(ProgramDir* programDir);
    void execute(int m);
};

#endif //SELAB_22FALL_EXECUTE_H
