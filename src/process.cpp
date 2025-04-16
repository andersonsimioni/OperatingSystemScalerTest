#include "process.h"
#include "os_core.h"

void Process::Run()
{
    int rd_sum = 0;
    vector<int> aux_mem;
    //std::cout<<"Simulating process "<<PID<<std::endl;
    
    switch (type)
    {
    case CPU_BOUND:
        rd_sum = 0;
        for (int i = 0; i < rand()%100000; i++)
        {
            for (int j = 0; j < rand()%100000; j++)
            {
                rd_sum++;
            }
        }
        
        break;
        
    case MEMORY_BOUND:        
        aux_mem.clear();
        
        //ALLOC MEMORY
        for (int i = 0; i < rand()%100; i++)
        {
            for (int j = 0; j < rand()%100; j++)
            {
                aux_mem.push_back(rand());
            }
        }
        
        //FREE MEMORY
        aux_mem.clear();

        break;

    case IO_BOUND:
        if((rand() % 100) <= BLOCK_UNBLOCK_PROBABILITY) state = BLOCKED;
        break;
    
    default:
        break;
    }
}

Process::Process(ifstream* processListFileStream)
{
    getline(*processListFileStream, name);

    std::string priority_str;
    getline(*processListFileStream, priority_str);
    priority = std::stoi(priority_str);
    
    std::string type_str;
    getline(*processListFileStream, type_str);
    type = (PROCESS_TYPE_ENUM)std::stoi(type_str);

    std::string total_estimated_execution_time_str;
    getline(*processListFileStream, total_estimated_execution_time_str);
    total_estimated_execution_time = (PROCESS_TYPE_ENUM)std::stoi(total_estimated_execution_time_str);

    aging = 0;
    current_total_execution_time = 0;
    current_state_execution_time = 0;
    state = PROCESS_STATE_ENUM::STARTING;

    states_total_executed_time = (int*)malloc(sizeof(int)*PROCESS_STATE_ENUM_COUNT);
}