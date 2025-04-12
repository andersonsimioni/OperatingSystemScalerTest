using namespace std;

#include <iostream>
#include <vector>
#include "os_core.h"

int main(int argc, char* argv[]) {
    std::cout<<"starting OS.."<<std::endl;

    if(argc < 1)
    {
        std::cout<<"Process list file not inserted!";
        return -1;
    }

    std::string processListFile = argv[1];
    std::cout<<"Process list file: "<<processListFile<<std::endl;

    OsCore osCore(processListFile);
    osCore.run();

    return 0;
}
