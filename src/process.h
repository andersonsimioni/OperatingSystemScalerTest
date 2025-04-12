using namespace std;

#include "process_type_enum.h"
#include "process_state_enum.h"
#include <string>
#include <iostream>
#include <fstream>


class Process
{
private:
public:
    int PID;
    string name;
    int priority;
    int execution_time;
    PROCESS_TYPE_ENUM type;
    PROCESS_STATE_ENUM state;

    void RunSimulation();

    Process(ifstream* processListFileStream);
};
