#include "os_core.h"

Process* OsCore::getProcessByPID(int pid)
{
    for (int i = 0; i < processes.size(); i++)
    {
        if(processes[i].PID == pid) return &processes[i];
    }
    
    return nullptr;
}

/// @brief 
/// @return 
int OsCore::getNewPID()
{
    int newPID = rand() % 100000;
    while (getProcessByPID(newPID) != nullptr) newPID = rand() % 100000;

    return newPID;
}

vector<Process*> OsCore::getProcessesByState(PROCESS_STATE_ENUM state)
{
    vector<Process*> process_vector;
    for (int i = 0; i < processes.size(); i++) if(processes[i].state == state) process_vector.push_back(&processes[i]);
    return process_vector;
}

void OsCore::scale_process()
{
    Process* bp = &processes[0]; //best process to scale in
    for (int i = 1; i < processes.size(); i++) if(processes[i].getFinalPriority() > bp->getFinalPriority()) bp = &processes[i];

    vector<Process*> running = getProcessesByState(RUNNING);
    for (int i = 0; i < running.size(); i++) if(running[i]->PID!=bp->PID) running[i]->state = READY;

    bp->state = RUNNING;

    free(&running);
}

void OsCore::run()
{
    while (true)
    {
        usleep(OS_CORE_TICK_MS * OS_CORE_TIME_SCALE);
        execution_time += OS_CORE_TICK_MS;

        for (int i = 0; i < processes.size(); i++)
        {
            processes[i].current_state_execution_time++;
            processes[i].states_total_executed_time[processes[i].state]++;
            if(processes[i].state != RUNNING) processes[i].aging++;

            switch (processes[i].state)
            {
            case STARTING:
                processes[i].state = READY;
                cout<<"Starting process "<<processes[i].name<<endl;
                break;

            case READY:
                break;

            case RUNNING:
                processes[i].current_total_execution_time++;
                processes[i].run();
                break;

            case BLOCKED:
                if(processes[i].requested_resource)
                {
                    processes[i].state = BLOCKED;
                    std:cout<<"Process "<<processes[i].name<<" waiting for resource"<<endl;
                }

                if((rand() % 100) <= BLOCK_UNBLOCK_PROBABILITY) 
                {
                    processes[i].state = READY;
                    processes[i].requested_resource = 0;
                    cout<<"Process "<<processes[i].name<<" resource arrived"<<endl;
                }
                break;

            case FINISH:
                break;
            
            default:
                break;
            }
        }
        
        scale_process();
    }
}



OsCore::OsCore(string processListFileName)
{
    std:ifstream processListFile(processListFileName);
    if(!processListFile.is_open())
    {
        std::cout<<"Invalid process list file";
        exit(-1);
    }

    string processCount;
    getline (processListFile, processCount);
    for (int i = 0; i < std::stoi(processCount); i++) 
    {
        Process newProcess(&processListFile);
        newProcess.PID = getNewPID();
        processes.push_back(newProcess);
    }

    processListFile.close();
    execution_time = 0;
}