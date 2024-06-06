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
    BitmapManager(int free_memory_size, int page_size, int allocation_algorithm) : MemoryManager(free_memory_size, page_size, allocation_algorithm)
    {
        bitmap = vector<int>(free_memory_size / page_size, 0);
        operation_id = vector<int>(free_memory_size / page_size, -1);
    };

    void request_memory(MemoryRequest *request) override;

    void allocate_memory(MemoryRequest *request) override;

    void first_fit_algorithm(int request_size, int request_id);

    void next_fit_algorithm(int request_size, int request_id);

    void deallocate_memory(MemoryRequest *request) override;

    void print_memory() override;

private:
    vector<int> bitmap;
    vector<int> operation_id;

    int last_fit_index = 0;
};

#endif
