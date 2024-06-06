#ifndef MemoryManager_HPP
#define MemoryManager_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "MemoryRequest.hpp"

using namespace std;

class MemoryManager
{

public:
    MemoryManager(int free_memory_size, int min_block_size, int allocation_algorithm);
    virtual void request_memory(MemoryRequest *request) = 0;

    virtual void allocate_memory(MemoryRequest *request) = 0;
    virtual void deallocate_memory(MemoryRequest *request) = 0;

    virtual void print_memory() = 0;

protected:
    int free_memory_size;     // Tamanho da memória livre em bytes
    int min_block_size;       // Tamanho mínimo de bloco em bytes
    int allocation_algorithm; // Algoritmo de alocação

    int allocations;   // Número de alocações
    int deallocations; // Número de desalocações
};

#endif