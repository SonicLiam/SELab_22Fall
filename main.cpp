#include <iostream>
#include "include/input.h"
#include "include/execute.h"
#include "include/judge.h"
#include "include/output.h"
#define EXECUTE_TIMES 3

void red_print(string s){
    cout << "\033[31m" << s << "\033[0m" << endl;
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <input path>" << std::endl;
        return 1;
    }
    //Input and scan the input directory
    InputDir inputDir(argv[1]);
    //Output the scanned result
    auto programDirs = inputDir.getProgramDirs();
    red_print("Scanned " + to_string(programDirs.size()) + " program directories.");

    //Execute the programs
    red_print("Executing programs:");
    for(auto &programDir : programDirs){
        Execute execute(&programDir);
        execute.execute(EXECUTE_TIMES);
    }
    red_print("Executing completed. " + to_string(EXECUTE_TIMES) + " times for each program.");

    //Judge the programs
    Judge judge(&inputDir, EXECUTE_TIMES);
    judge.judge();
    auto judgeResults = judge.getJudgeResults();
    red_print("Judging completed. " + to_string(judgeResults.size()) + " pairs of programs are judged.");

    //Output the judge result
    Output output(&judge);
    output.output();
    red_print("Output completed. The result is in the output directory.");

}

