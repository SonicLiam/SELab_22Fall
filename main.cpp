#include <iostream>
#include "include/input.h"
int main(int argc, char *argv[]) {
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <input path>" << std::endl;
        return 1;
    }
    InputDir inputDir(argv[1]);
}