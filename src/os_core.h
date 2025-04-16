#pragma once
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "process.h"


#define OS_CORE_TICK_MS 1 //Looping clock ms
#define OS_CORE_PROCESS_SCALING_TICKS 5 //Ticks to scale processes
#define OS_CORE_TIME_SCALE 1 //Scale to visualize better on run simulation, set 1 to real time
#define BLOCK_PROBABILITY 1 //0-100% chance to request an IO resource
#define UNBLOCK_PROBABILITY 5 //0-100% chance to receive an IO resource
#define MAX_RUNNING_PROCESSES 1 //Max processes on running state simultaneous

class OsCore
{
private:
    int execution_time; //Current OS execution time
    int ticks_count; //Current OS ticks count

    vector<Process> processes; //All processes on system
    void log();

public:
    void run(); //Loop function
    void endTick(); //Run o end of each tick and check if all processes finish, if yes, print report and exit
    int getNewPID(); //Generate new process id
    void scaleProcess(); //Scale in or out processes of running state
    Process* getProcessByPID(int pid); //Find process by PID, if nor, return nullptr
    vector<Process*> getProcessesByState(PROCESS_STATE_ENUM state); //Return a list of processes with the state

    OsCore(string processListFileName);
};
