#include "MemoryManager.hpp"

MemoryManager::MemoryManager(int free_memory_size, int min_block_size, int allocation_algorithm)
{
    this->free_memory_size = free_memory_size;
    this->min_block_size = min_block_size;
    this->allocation_algorithm = allocation_algorithm;
    this->allocations = 0;
    this->deallocations = 0;
    this->total_allocated_bytes = 0;
    this->total_deallocated_bytes = 0;
}