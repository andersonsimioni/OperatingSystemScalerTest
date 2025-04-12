#include "process_type_enum.h"
#include "process_state_enum.h"
#include <string>

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

    Process();
    ~Process();
};
