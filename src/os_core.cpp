#include "os_core.h"

long getSystemTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

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

void OsCore::scaleProcess()
{
    if(processes.size() <= 0) return;

    Process* bp = nullptr; //best process to scale in
    vector<Process*> ready = getProcessesByState(READY);
    vector<Process*> running = getProcessesByState(RUNNING);
    
    bp = ready.size() > 0 ? ready[0] : (running.size() > 0 ? running[0] : nullptr);
    if(bp == nullptr) return;

    for (int i = 0; i < ready.size(); i++) if(ready[i]->getFinalPriority() > bp->getFinalPriority()) bp = ready[i];
    for (int i = 0; i < running.size(); i++) if(running[i]->getFinalPriority() > bp->getFinalPriority()) bp = running[i];

    //TODO: Work only on 1 process running by time, on multi running process have to change..
    if(bp->state == RUNNING) return;

    for (int i = 0; i < running.size(); i++) running[i]->state = READY;

    cout<<"Scaling "<<bp->name<<endl<<bp->current_total_execution_time<<"/"<<bp->total_estimated_execution_time<<endl;
    bp->state = RUNNING;
    
    //free(&running);
}

void OsCore::endTick()
{
    if(getProcessesByState(FINISH).size() == processes.size())
    {
        cout<<"Simulation end, all processes FINISH!"<<endl;
        //Print report code...
        exit(0);
    }
}

void OsCore::run()
{
    while (true)
    {
        usleep(OS_CORE_TICK_MS * OS_CORE_TIME_SCALE);
        execution_time += OS_CORE_TICK_MS;
        ticks_count++;

        for (int i = 0; i < processes.size(); i++)
        {
            processes[i].current_state_execution_time++;
            processes[i].states_total_executed_time[processes[i].state]++;
            if(processes[i].state != RUNNING) processes[i].aging++;
            if(processes[i].current_total_execution_time >= processes[i].total_estimated_execution_time && processes[i].state != FINISH)
            {
                processes[i].state = FINISH;
                processes[i].system_end_time = getSystemTimeMs();
                cout<<"Process "<<processes[i].name<<" FINISH"<<endl<<"system time duration "<<(processes[i].system_end_time-processes[i].system_start_time)<<endl;
            }
            
            switch (processes[i].state)
            {
            case STARTING:
                processes[i].state = READY;
                processes[i].system_start_time = getSystemTimeMs();
                cout<<"Starting process "<<processes[i].name<<endl;
                break;

            case READY:
                break;

            case RUNNING:
                processes[i].current_total_execution_time++;
                processes[i].run();

                if(processes[i].requested_resource)
                {
                    processes[i].state = BLOCKED;
                    std:cout<<"Process "<<processes[i].name<<" waiting for resource"<<endl;
                }
                break;

            case BLOCKED:
                if((rand() % 100) <= UNBLOCK_PROBABILITY) 
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
        
        if((ticks_count % OS_CORE_PROCESS_SCALING_TICKS) == 0) scaleProcess();
        endTick();
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