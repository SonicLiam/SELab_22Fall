//
// Created by SonicLiam on 2022/11/10.
//

#include "../include/input.h"
#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include<fstream>
#include<string>
#include <cstring>
#include <cassert>
#include <utility>

using namespace std;

ProgramDir::ProgramDir(string Dir, string DirName) {
    this->dir = std::move(DirName);
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    int fileNum = 0;
    int formatNum = 0;
    if ((dirp = opendir(Dir.c_str())) == nullptr) {
        perror("opendir");
        exit(1);
    }
    while ((direntp = readdir(dirp)) != nullptr) {
        if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
            continue;
        string d = Dir + "/" + direntp->d_name;
        if (stat(d.c_str(), &stat_buf) == -1) {
            perror("stat");
            exit(1);
        }
        if (S_ISREG(stat_buf.st_mode)) {
            fileNum++;
            string fileName = direntp->d_name;
            if (fileName.find(".txt") != string::npos) {
                formatNum++;
                formatFile = d;
            }
            else{
                fileNames.push_back(d);
            }
        }
    }
    programNum = fileNum - formatNum;
    assert(programNum > 0 && formatNum == 1);
    closedir(dirp);
}

string ProgramDir::getDir() const {
    return dir;
}

vector<string> ProgramDir::getFileNames() const {
    return fileNames;
}

string ProgramDir::getFormatFile() const {
    return formatFile;
}

int ProgramDir::getProgramNum() const {
    return programNum;
}

InputDir::InputDir(char *Dir) {
    this->dir = Dir;
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    dirNum = 0;
    if ((dirp = opendir(Dir)) == NULL) {
        perror("opendir");
        exit(1);
    }
    while ((direntp = readdir(dirp)) != NULL) {
        if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
            continue;
        string d = dir + "/" + direntp->d_name;
        if (stat(d.c_str(), &stat_buf) == -1) {
            perror("stat");
            exit(1);
        }
        if (S_ISDIR(stat_buf.st_mode)) {
            dirNum++;
            programDirs.emplace_back(ProgramDir(d, d));
        }
    }
    assert(dirNum > 0);
    closedir(dirp);
}

vector<ProgramDir> InputDir::getProgramDirs() const {
    return programDirs;
}
