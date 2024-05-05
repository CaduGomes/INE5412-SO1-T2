#ifndef MemoryManager_HPP
#define MemoryManager_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "MemoryRequest.hpp"
#include "AllocationAlgorithm.hpp"

using namespace std;

class MemoryManager
{

public:
    MemoryManager(int free_memory_size, int page_size, AllocationAlgorithm *allocation_algorithm);
    void request_memory(MemoryRequest *request);

private:
    int free_memory_size;
    int page_size;
    AllocationAlgorithm *allocation_algorithm;
};

#endif