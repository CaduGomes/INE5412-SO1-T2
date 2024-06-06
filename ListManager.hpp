#ifndef ListManager_HPP
#define ListManager_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "MemoryManager.hpp"

using namespace std;

class MemoryBlock
{
public:
    int size;
    bool is_free;
    int id;
    MemoryBlock *next;

    MemoryBlock(int size, bool is_free, int id = -1)
        : size(size), is_free(is_free), id(id), next(nullptr) {}
};

class ListManager : public MemoryManager
{

public:
    ListManager(int free_memory_size, int page_size, int allocation_algorithm) : MemoryManager(free_memory_size, page_size, allocation_algorithm){};

    void request_memory(MemoryRequest *request) override;

    void allocate_memory(MemoryRequest *request) override;

    void deallocate_memory(MemoryRequest *request) override;

    void first_fit_algorithm(int request_size, int request_id);

    void next_fit_algorithm(int request_size, int request_id);

    void print_memory() override;

private:
    MemoryBlock *head = nullptr;
    MemoryBlock *last_alloc = nullptr;
};

#endif