#include "process.h"

void Process::RunSimulation()
{
    std::cout<<"Simulating process "<<PID<<std::endl;
}

Process::Process(ifstream* processListFileStream)
{
    /* int PID;
    string name;
    int priority;
    int execution_time;
    PROCESS_TYPE_ENUM type;
    PROCESS_STATE_ENUM state; */

    getline(*processListFileStream, name);

    std::string priority_str;
    getline(*processListFileStream, priority_str);
    priority = std::stoi(priority_str);
    
    std::string type_str;
    getline(*processListFileStream, type_str);
    type = (PROCESS_TYPE_ENUM)std::stoi(type_str);

    execution_time = 0;
    state = PROCESS_STATE_ENUM::STARTING;
}