#include "ListManager.hpp"
#include <cmath>

void ListManager::request_memory(MemoryRequest *request)
{

    if (request->is_allocation())
    {
        allocate_memory(request);
    }
    else
    {
        deallocate_memory(request);
    }
}

void ListManager::allocate_memory(MemoryRequest *request)
{
    int request_size = request->request_size;
    if (request->request_size < min_block_size)
    {
        request_size = min_block_size;
        // cout << "Memory request " << request->request_id << " size adjusted to " << min_block_size << endl;
    }

    if (allocation_algorithm == 1)
    {
        first_fit_algorithm(request_size, request->request_id);
    }
    else
    {
        next_fit_algorithm(request_size, request->request_id);
    }
}

void ListManager::next_fit_algorithm(int request_size, int request_id)
{
    MemoryBlock *current = last_alloc;

    do
    {
        if (current != nullptr)
        {
            if (current->is_free && current->size >= request_size)
            {
                if (current->size > request_size)
                {
                    MemoryBlock *new_block = new MemoryBlock(current->size - request_size, true);
                    new_block->next = current->next;
                    current->next = new_block;
                }
                current->size = request_size;
                current->is_free = false;
                current->id = request_id;

                last_alloc = current;

                // cout << "Memory request " << request_id << " allocated in block " << current->id << endl;
                return;
            }

            if (current->next == nullptr)
            {
                current = head;
            }
            else
            {
                current = current->next;
            }
        }
    } while (current != last_alloc);

    if (free_memory_size >= request_size)
    {
        MemoryBlock *new_block = new MemoryBlock(request_size, false, request_id);

        if (current == nullptr)
        {
            head = new_block;
            free_memory_size -= request_size;
            last_alloc = new_block;
            // cout << "Memory request " << request_id << " allocated in a new block " << new_block->id << endl;
            return;
        }

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new_block;
        last_alloc = new_block;

        free_memory_size -= request_size;
        // cout << "Memory request " << request_id << " allocated in a new block " << new_block->id << endl;
        return;
    }
}

void ListManager::first_fit_algorithm(int request_size, int request_id)
{
    MemoryBlock *current = head;

    while (current != nullptr)
    {
        if (current->is_free && current->size >= request_size)
        {
            // Cria um novo bloco com o espaço restante
            if (current->size > request_size)
            {
                MemoryBlock *new_block = new MemoryBlock(current->size - request_size, true);
                new_block->next = current->next;
                current->next = new_block;
            }

            current->size = request_size;
            current->is_free = false;
            current->id = request_id;

            // cout << "Memory request " << request_id << " allocated in block " << current->id << endl;
            return;
        }
        current = current->next;
    }

    if (request_size > free_memory_size)
    {
        free_memory_size -= request_size;
        // cout << "Memory request " << request_id << " failed. Not enough free memory." << endl;
        return;
    }

    // Se não encontrou um bloco livre, cria um novo bloco no final da lista se houver espaço
    if (current == nullptr && free_memory_size >= request_size)
    {
        MemoryBlock *new_block = new MemoryBlock(request_size, false, request_id);

        current = head;

        if (current == nullptr)
        {
            head = new_block;
            free_memory_size -= request_size;
            // cout << "Memory request " << request_id << " allocated in a new block " << new_block->id << endl;
            return;
        }

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new_block;

        free_memory_size -= request_size;
        // cout << "Memory request " << request_id << " allocated in a new block " << new_block->id << endl;
        return;
    }

    // cout << "Memory request " << request_id << " failed. Not enough memory." << endl;
}

void ListManager::deallocate_memory(MemoryRequest *request)
{
    MemoryBlock *current = head;
    MemoryBlock *last = nullptr;
    while (current)
    {
        if (current->id == request->request_id)
        {
            if (last != nullptr && last->is_free)
            {
                last->size += current->size;
                last->next = current->next;
                delete current;
                current = last;
            }

            if (current->next != nullptr && current->next->is_free)
            {
                current->size += current->next->size;
                MemoryBlock *temp = current->next;
                current->next = current->next->next;
                delete temp;
            }

            current->is_free = true;
            current->id = -1;

            // cout << "Memory request " << request->request_id << " deallocated" << endl;
            break;
        }
        last = current;
        current = current->next;
    }
}

void ListManager::print_memory()
{
    MemoryBlock *current = head;
    int used_memory = 0;
    int total_allocated_bytes = 0;
    while (current)
    {
        cout << current->size << " " << (current->is_free ? 0 : 1) << endl;

        if (!current->is_free)
        {
            used_memory += current->size;
        }
        total_allocated_bytes += current->size;
        current = current->next;
    }

    cout << used_memory << " //quantidade de bytes em uso (ocupados)" << endl;
    cout << total_allocated_bytes << " //quantidade de bytes alocados" << endl;
    cout << (total_allocated_bytes - used_memory) << " //quantidade de bytes desalocados" << endl;
    cout << allocations << " //número de alocações" << endl;
    cout << deallocations << " //número de desalocações" << endl;
}