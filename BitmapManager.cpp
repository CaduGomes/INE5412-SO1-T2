#include "BitmapManager.hpp"

void BitmapManager::request_memory(MemoryRequest *request)
{

    if (request->is_allocation())
    {
        int request_size = request->request_size;
        if (request->request_size < min_block_size)
        {
            request_size = min_block_size;
        }

        if (request_size > free_memory_size)
        {
            cout << "Memory request " << request->request_id << " failed. Not enough memory." << endl;
            return;
        }

        int free_blocks = 0;
        int first_block = -1;
        }

    allocation_algorithm->allocate_memory(request);
}