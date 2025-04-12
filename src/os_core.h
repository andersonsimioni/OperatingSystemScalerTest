using namespace std;

#include <list>
#include <string>
#include "process.h"

class OsCore
{
private:
    list<Process> processes;
    void log();

public:
    void run();

    Process* getProcessByPID(int pid);

    int getNewPID();
    
    OsCore(string processListFileName);
};
