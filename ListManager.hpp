#ifndef ListManager_HPP
#define ListManager_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "MemoryManager.hpp"

using namespace std;

class ListManager : public MemoryManager
{

public:
    ListManager(int free_memory_size, int page_size, int alocation_algorithm) : MemoryManager(free_memory_size, page_size, alocation_algorithm){};

private:
    int free_memory_size;
    int page_size;
    int alocation_algorithm;
};

#endif