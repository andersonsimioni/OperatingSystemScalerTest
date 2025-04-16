#pragma once
using namespace std;

#include <string>
#include <iostream>
#include <fstream>

#include "process_type_enum.h"
#include "process_state_enum.h"

#define PRIORITY_WEIGHT 1.0f
#define AGING_WEIGHT 1.0f

class Process
{
private:
public:
    int PID; //Process unique id, generate by OS
    string name; //Name of process
    int priority; //Scaling priority
    int aging; //Time of process out of running state
    int current_state_execution_time; //Relative execution time of current state, zero on new state
    int current_total_execution_time; //Current total execution time: (current time)/(total time) = %
    int total_estimated_execution_time; //Total time the process will run
    PROCESS_TYPE_ENUM type; //Type of process
    PROCESS_STATE_ENUM state; //Current state of process, all starts on starting

    int* states_total_executed_time; //Total executed time by state
    int requested_resource; //Simulate a resource request

    void run();
    float getFinalPriority(); //Calculate the priority total of process: priority*priority_weight + aging*aging_weight

    Process(ifstream* processListFileStream);
};
