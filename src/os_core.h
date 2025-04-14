#pragma once
using namespace std;

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "process.h"

class OsCore
{
private:
    vector<Process> processes;
    void log();

public:
    void run();

    int getNewPID();

    Process* getProcessByPID(int pid);

    OsCore(string processListFileName);
};
