//
// Created by SonicLiam on 2022/11/10.
//

#include "../include/execute.h"
#include <fstream>
#include <sstream>
Execute::Execute(ProgramDir* programDir) {
    this->programDir = programDir;
}

void Execute::execute(int m) {
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
    string command = "rm -rf " + programDir->getDir() + "/result";
    system(command.c_str());
    command = "mkdir -p " + programDir->getDir() + "/result";
    system(command.c_str());
    for(int i = 0; i < m; i++){
        command = "mkdir -p " + programDir->getDir() + "/result/" + to_string(i);
        system(command.c_str());
    }
    for(int i = 0; i < m; i++) {
        string input = generateRandomInput(argNum, programInputs);
        string input_file = programDir->getDir() + "/result/input" + to_string(i) + ".txt";
        for(auto &fileName : fileNames){
            ofstream inf(input_file);
            inf << input;
            inf.close();
            string command = "g++ " + fileName + " -o " + fileName.substr(0, fileName.find_last_of(".")) + ".out";
            system(command.c_str());
            cout << "Executing: " << command << endl;
            command =
                    fileName.substr(0, fileName.find(".cpp")) + ".out < " + input_file + " > " + programDir->getDir() +
                    "/result/" + to_string(i) + "/" + fileName.substr(fileName.find_last_of("/") + 1,
                                                 fileName.find(".cpp") - fileName.find_last_of("/") - 1) + ".txt";
            system(command.c_str());
            cout << "Executing: " << command << endl;
            ifstream out(fileName.substr(0, fileName.find(".cpp")) + ".out");
            string output;
            getline(out, output);
            result[fileName] = output;
        }
    }
    command = "rm -rf " + programDir->getDir() + "/*.out";
    system(command.c_str());
    cout << "Executing: " << command << endl;
    command = "rm -rf " + programDir->getDir() + "/result/input*.txt";
    system(command.c_str());
    cout << "Executing: " << command << endl;
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