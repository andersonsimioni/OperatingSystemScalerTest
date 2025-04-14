#include "os_core.h"

Process* OsCore::getProcessByPID(int pid)
{
    for (int i = 0; i < processes.size(); i++)
    {
        if(processes[i].PID == pid) return &processes[i];
    }
    
    return nullptr;
}

int OsCore::getNewPID()
{
    int newPID = rand() % 100000;
    while (getProcessByPID(newPID) != nullptr) newPID = rand() % 100000;

    return newPID;
}

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
    for (int i = 0; i < std::stoi(processCount); i++) 
    {
        Process newProcess(&processListFile);
        newProcess.PID = getNewPID();
        processes.push_back(newProcess);
    }
    

    processListFile.close();
}

void OsCore::run()
{
    while (true)
    {
        usleep(100);
        for (int i = 0; i < processes.size(); i++)
        {
            switch (processes[i].state)
            {
            case STARTING:
                break;
            case READY:
                break;
            case RUNNING:
                break;
            case BLOCKED:
                break;
            case FINISH:
                break;
            
            default:
                break;
            }
        }
    }
    
}