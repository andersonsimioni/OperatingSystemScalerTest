#include "os_core.h"

OsCore::OsCore(string processListFileName)
{
    std:ifstream processListFile(processListFileName);
    if(!processListFile.is_open())
    {
        std::cout<<"Invalid process list file";
        exit(-1);
    }

    string processCount;
    getline (processListFile, processCount);
    for (int i = 0; i < std::stoi(processCount); i++) {
        Process newProcess(&processListFile);
        processes.push_front(newProcess);
    }
    

    processListFile.close();
}

void OsCore::run()
{
    
}