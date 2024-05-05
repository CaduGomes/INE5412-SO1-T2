#ifndef BitmapManager_HPP
#define BitmapManager_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "MemoryManager.hpp"

using namespace std;

class BitmapManager : public MemoryManager
{

public:
    BitmapManager(int free_memory_size, int page_size, AllocationAlgorithm *allocation_algorithm) : MemoryManager(free_memory_size, page_size, allocation_algorithm){};

private:
    int free_memory_size;
    int page_size;
    int allocation_algorithm;
};

#endif