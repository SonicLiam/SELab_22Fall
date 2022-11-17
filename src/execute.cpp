//
// Created by SonicLiam on 2022/11/10.
//

#include "../include/execute.h"
#include <fstream>
#include <sstream>
Execute::Execute(ProgramDir* programDir) {
    this->programDir = programDir;
}

void Execute::execute() {
    auto fileNames = programDir->getFileNames();
    auto formatFile = programDir->getFormatFile();
    ifstream format(formatFile);
    string line;
    getline(format, line);
    std::istringstream ss(line);
    vector<programInput> programInputs;
    int argNum = 0;
    string arg;
    while(ss >> arg){
        argNum++;
        programInput programInput1;
        if(arg.find("int") != string::npos){
            programInput1.type = programInput::intType;
            programInput1.floor = stoi(arg.substr(4, arg.find(",") - 4));
            programInput1.ceil = stoi(arg.substr(arg.find(",") + 1, arg.find(")") - arg.find(",") - 1));
        }
        else if(arg.find("char") != string::npos){
            programInput1.type = programInput::charType;
            programInput1.floor = 0;
            programInput1.ceil = 0;
        }
        else if(arg.find("string") != string::npos){
            programInput1.type = programInput::stringType;
            programInput1.floor = stoi(arg.substr(7, arg.find(",") - 7));
            programInput1.ceil = stoi(arg.substr(arg.find(",") + 1, arg.find(")") - arg.find(",") - 1));
        }
        programInputs.push_back(programInput1);
    }
    string command = "mkdir -p " + programDir->getDir() + "/result";
    system(command.c_str());
    for(auto &fileName : fileNames){
        string input = generateRandomInput(argNum, programInputs);
        string command = "gcc " + fileName + " -o " + fileName.substr(0, fileName.find(".cpp")) + ".out";
        system(command.c_str());
        cout << command << endl;
        command = fileName.substr(0, fileName.find(".cpp")) + ".out " + input + " > " + programDir->getDir() + "/result/" + fileName.substr(fileName.find_last_of("/") + 1, fileName.find(".cpp") - fileName.find_last_of("/") - 1) + ".txt";
        system(command.c_str());
        cout << command << endl;
        ifstream out(fileName.substr(0, fileName.find(".cpp")) + ".out");
        string output;
        getline(out, output);
        cout << output << endl;
        result[fileName] = output;
    }
}

string Execute::generateRandomInput(int argNum, vector <programInput> programInputs) {
    string input;
    for(int i = 0; i < argNum; i++){
        if(programInputs[i].type == programInput::intType){
            int num = rand() % (programInputs[i].ceil - programInputs[i].floor + 1) + programInputs[i].floor;
            input += to_string(num);
        }
        else if(programInputs[i].type == programInput::charType){
            char c = rand() % 26 + 'a';
            input += c;
        }
        else if(programInputs[i].type == programInput::stringType){
            int len = rand() % (programInputs[i].ceil - programInputs[i].floor + 1) + programInputs[i].floor;
            for(int j = 0; j < len; j++){
                char c = rand() % 26 + 'a';
                input += c;
            }
        }
        if(i != argNum - 1){
            input += " ";
        }
    }
    return input;
}