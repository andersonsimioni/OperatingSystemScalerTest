#include "os_core.h"

Process* OsCore::getProcessByPID(int pid)
{
    for (int i = 0; i < processes.size(); i++)
    {
        if(processes[i].PID == pid) return &processes[i];
    }
    
    return nullptr;
}

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
    vector<Process*> running = getProcessesByState(RUNNING);
    vector<Process*> ready = getProcessesByState(READY);

    //Preempt out of running state
    for (int i = 0; i < running.size(); i++)
    {
        if(running[i]->current_state_execution_time > OS_CORE_SCALING_TICKS)
        {
            running[i]->state = READY;
            running[i]->current_state_execution_time = 0;
        }
    }

    //Select the oldest and higher priority ready process to preempt in running state
    Process* bestProcessToPreempt;
    for (int i = 0; i < ready.size(); i++)
    {
        //Preempt logic code...
    }
    bestProcessToPreempt->state = RUNNING;
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
                processes[i].Run();
                break;

            case BLOCKED:
                if((rand() % 100) <= BLOCK_UNBLOCK_PROBABILITY) 
                {
                    processes[i].state = READY;
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