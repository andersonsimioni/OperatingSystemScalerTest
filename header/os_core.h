#include <list>
#include <string>
#include "header/process.h"

class OsCore
{
private:
    list<Process> processes;
    void log();

public:
    void run();
    
    OsCore(string processListFileName);
    ~OsCore();
};
