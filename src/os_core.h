#pragma once
using namespace std;

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "process.h"

#define OS_CORE_TICK_MS 1
#define OS_CORE_SCALING_TICKS 5

#define BLOCK_UNBLOCK_PROBABILITY 5

class OsCore
{
private:
    int execution_time;

    vector<Process> processes;
    void log();

public:
    void run();
    int getNewPID();
    void scale_process();
    Process* getProcessByPID(int pid);
    vector<Process*> getProcessesByState(PROCESS_STATE_ENUM state);

    OsCore(string processListFileName);
};
