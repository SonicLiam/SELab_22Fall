#include <iostream>
#include "include/input.h"
#include "include/execute.h"
int main(int argc, char *argv[]) {
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <input path>" << std::endl;
        return 1;
    }
    //Input and scan the input directory
    InputDir inputDir(argv[1]);
    //Output the scanned result
    auto programDirs = inputDir.getProgramDirs();
    for(auto &programDir : programDirs){
        int programNum = programDir.getProgramNum();
        std::cout << "ProgramDir: " << programDir.getDir() << std::endl;
        auto fileNames = programDir.getFileNames();
        std::cout << "Got " << programNum << " programs:" << std::endl;
        for(auto &fileName : fileNames){
            std::cout  << fileName << std::endl;
        }
        std::cout << "Got format file:" << std::endl;
        std::cout << programDir.getFormatFile() << std::endl;
    }

    for(auto &programDir : programDirs){
        Execute execute(&programDir);
        execute.execute();
    }
}