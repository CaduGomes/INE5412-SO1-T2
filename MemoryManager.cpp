#include "MemoryManager.hpp"

MemoryManager::MemoryManager(int free_memory_size, int page_size, int alocation_algorithm)
{
    this->free_memory_size = free_memory_size;
    this->page_size = page_size;
    this->alocation_algorithm = alocation_algorithm;
}
