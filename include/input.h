//
// Created by SonicLiam on 2022/11/10.
//

#ifndef SELAB_22FALL_INPUT_H
#define SELAB_22FALL_INPUT_H

#include <iostream>
#include <vector>
using namespace std;


class ProgramDir{
private:
    string dir;
    vector<string> fileNames;
    string formatFile;
    int programNum;

public:
    ProgramDir(string dir, string dirName);
    ~ProgramDir() = default;;
    string getDir() const;
    vector<string> getFileNames() const;
    string getFormatFile() const;
    int getProgramNum() const;
};

class InputDir {
private:
    string dir;
    vector<ProgramDir> programDirs;
    int dirNum;
public:
    explicit InputDir(char* dir);
    ~InputDir() = default;
    vector<ProgramDir> getProgramDirs() const;
};

#endif //SELAB_22FALL_INPUT_H
