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
    MemoryManager(int free_memory_size, int min_block_size, AllocationAlgorithm *allocation_algorithm);
    virtual void request_memory(MemoryRequest *request) = 0;

protected:
    int free_memory_size; // Tamanho da memória livre em bytes
    int min_block_size;   // Tamanho mínimo de bloco em bytes
    AllocationAlgorithm *allocation_algorithm;
};

#endif