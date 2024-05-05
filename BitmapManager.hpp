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
    BitmapManager(int free_memory_size, int page_size, AllocationAlgorithm *allocation_algorithm) : MemoryManager(free_memory_size, page_size, allocation_algorithm)
    {
        bitmap = vector<int>(free_memory_size / page_size, 0);
    };

    void request_memory(MemoryRequest *request) override;

private:
    vector<int> bitmap;
};

#endif
