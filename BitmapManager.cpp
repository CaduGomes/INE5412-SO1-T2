#include "BitmapManager.hpp"
#include <cmath>

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
            // cout << "Memory request " << request->request_id << " failed. Not enough memory." << endl;
            return;
        }

        int blocks_needed = static_cast<int>(std::ceil(static_cast<double>(request_size) / min_block_size)); // Arredondar para cima

        if (allocation_algorithm == 1)
        {
            first_fit_algorithm(blocks_needed, request->request_id);
        }
        else
        {
            next_fit_algorithm(blocks_needed, request->request_id);
        }
        // cout << "Memory request " << request->request_id << " failed. Not enough contiguous memory." << endl;
    }
    else
    {
        deallocate_memory(request);
    }
}

void BitmapManager::allocate_memory(MemoryRequest *request)
{
    request_memory(request);
}

void BitmapManager::first_fit_algorithm(int blocks_needed, int request_id)
{
    int blocks_free_count = 0;
    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        if (bitmap[i] == 0)
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed)
            {
                for (size_t j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    operation_id[j] = request_id;
                    bitmap[j] = true;
                }
                // cout << "Memory request " << request_id << " allocated in blocks " << i + 1 - blocks_needed << " to " << i << endl;
                return;
            }
        }
        else
        {
            blocks_free_count = 0;
        }
    }
}

void BitmapManager::next_fit_algorithm(int blocks_needed, int request_id)
{
    int blocks_free_count = 0;
    for (size_t i = last_fit_index; i < bitmap.size(); ++i)
    {
        if (bitmap[i] == 0)
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed)
            {
                for (size_t j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    operation_id[j] = request_id;
                    bitmap[j] = true;
                }
                // cout << "Memory request " << request_id << " allocated in blocks " << i + 1 - blocks_needed << " to " << i << endl;
                last_fit_index = i + 1;
                return;
            }
        }
        else
        {
            blocks_free_count = 0;
        }
    }

    blocks_free_count = 0;

    for (int i = 0; i < last_fit_index; ++i)
    {
        if (bitmap[i] == 0)
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed)
            {
                for (int j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    operation_id[j] = request_id;
                    bitmap[j] = true;
                }

                // cout << "Memory request " << request_id << " allocated in blocks " << i + 1 - blocks_needed << " to " << i << endl;

                last_fit_index = i + 1; // Atualizar a última posição de alocação
                return;
            }
        }
        else
        {
            blocks_free_count = 0;
        }
    }
}

void BitmapManager::deallocate_memory(MemoryRequest *request)
{

    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        if (operation_id[i] == request->request_id)
        {
            bitmap[i] = 0;
            operation_id[i] = -1;
        }
    }
}

void BitmapManager::print_memory()
{
    int used_memory = 0;
    int total_allocated_bytes = bitmap.size() * min_block_size;

    for (size_t i = 0; i < bitmap.size(); ++i)
    {

        if (bitmap[i] == 1)
        {
            used_memory += min_block_size;
        }

        cout << bitmap[i];
    }
    cout << endl;

    cout << used_memory << " //quantidade de bytes em uso (ocupados)" << endl;
    cout << total_allocated_bytes << " //quantidade de bytes alocados" << endl;
    cout << (total_allocated_bytes - used_memory) << " //quantidade de bytes desalocados" << endl;
    cout << allocations << " //número de alocações" << endl;
    cout << deallocations << " //número de desalocações" << endl;
}
