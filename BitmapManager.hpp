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
    BitmapManager(int free_memory_size, int min_block_size, int allocation_algorithm) : MemoryManager(free_memory_size, min_block_size, allocation_algorithm)
    {
        bitmap = vector<int>(free_memory_size / min_block_size, 0);
        request_id_map = vector<int>(free_memory_size / min_block_size, -1);
    };

    void request_memory(MemoryRequest *request) override;

    void allocate_memory(MemoryRequest *request) override;

    void first_fit_algorithm(int blocks_needed, int request_id);

    void next_fit_algorithm(int blocks_needed, int request_id);

    void deallocate_memory(MemoryRequest *request) override;

    void print_memory() override;

private:
    vector<int> bitmap;
    vector<int> request_id_map;

    int last_fit_index = 0;
};

#endif
