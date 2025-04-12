#include "process.h"

Process::Process(ifstream* processListFileStream)
{
    /* int PID;
    string name;
    int priority;
    int execution_time;
    PROCESS_TYPE_ENUM type;
    PROCESS_STATE_ENUM state; */

    std::string pid_str;
    getline(*processListFileStream, pid_str);
    PID = std::stoi(pid_str);

    getline(*processListFileStream, name);

    std::string priority_str;
    getline(*processListFileStream, priority_str);
    priority = std::stoi(priority_str);

    std::string execution_time_str;
    getline(*processListFileStream, execution_time_str);
    execution_time = std::stoi(execution_time_str);
    
    std::string type_str;
    getline(*processListFileStream, type_str);
    type = (PROCESS_TYPE_ENUM)std::stoi(type_str);

    std::string state_str;
    getline(*processListFileStream, state_str);
    state = (PROCESS_STATE_ENUM)std::stoi(state_str);
}