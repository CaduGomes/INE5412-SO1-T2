#ifndef MemoryManager_HPP
#define MemoryManager_HPP
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MemoryManager
{

public:
    MemoryManager(int free_memory_size, int page_size, int alocation_algorithm);

private:
    int free_memory_size;
    int page_size;
    int alocation_algorithm;
};

#endif