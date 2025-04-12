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
    
    OsCore(string processListFileName);
    ~OsCore();
};
