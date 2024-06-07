#include "ListManager.hpp" // Inclui a definição da classe ListManager
#include <cmath>           // Inclui a biblioteca para operações matemáticas (ex. ceil)

void ListManager::request_memory(MemoryRequest *request)
{
    if (request->is_allocation()) // Verifica se o pedido é de alocação
    {
        allocate_memory(request); // Aloca memória para o pedido
    }
    else
    {
        deallocate_memory(request); // Desaloca memória para o pedido
    }
}

void ListManager::allocate_memory(MemoryRequest *request)
{
    int request_size = request->request_size;
    if (request->request_size < min_block_size) // Verifica se o tamanho do pedido é menor que o tamanho mínimo do bloco
    {
        request_size = min_block_size; // Ajusta o tamanho do pedido para o tamanho mínimo do bloco
    }

    if (allocation_algorithm == 1) // Verifica qual algoritmo de alocação usar
    {
        first_fit_algorithm(request_size, request->request_id); // Usa o algoritmo First-Fit
    }
    else
    {
        next_fit_algorithm(request_size, request->request_id); // Usa o algoritmo Next-Fit
    }
}

void ListManager::next_fit_algorithm(int request_size, int request_id)
{
    MemoryBlock *current = last_alloc; // Inicia a busca a partir do último bloco alocado

    do
    {
        if (current != nullptr)
        {
            if (current->is_free && current->size >= request_size) // Verifica se o bloco atual está livre e é grande o suficiente
            {
                total_allocated_bytes += request_size; // Atualiza o total de bytes alocados
                allocations++;                         // Incrementa o contador de alocações

                if (current->size > request_size) // Se o bloco atual é maior que o pedido
                {
                    MemoryBlock *new_block = new MemoryBlock(current->size - request_size, true); // Cria um novo bloco com o espaço restante
                    new_block->next = current->next;                                              // Atualiza o ponteiro do próximo bloco
                    current->next = new_block;                                                    // Atualiza o ponteiro do próximo bloco do bloco atual
                }

                current->size = request_size; // Ajusta o tamanho do bloco atual
                current->is_free = false;     // Marca o bloco como ocupado
                current->id = request_id;     // Define o ID do bloco

                last_alloc = current; // Atualiza o último bloco alocado
                return;               // Retorna após a alocação bem-sucedida
            }

            if (current->next == nullptr)
            {
                current = head; // Reinicia a busca do início da lista se chegou ao final
            }
            else
            {
                current = current->next; // Move para o próximo bloco
            }
        }
    } while (current != last_alloc); // Continua até retornar ao ponto inicial da busca
}

void ListManager::first_fit_algorithm(int request_size, int request_id)
{
    MemoryBlock *current = head; // Inicia a busca do início da lista

    while (current != nullptr)
    {
        if (current->is_free && current->size >= request_size) // Verifica se o bloco atual está livre e é grande o suficiente
        {
            total_allocated_bytes += request_size; // Atualiza o total de bytes alocados
            allocations++;                         // Incrementa o contador de alocações

            if (current->size > request_size) // Se o bloco atual é maior que o pedido
            {
                MemoryBlock *new_block = new MemoryBlock(current->size - request_size, true); // Cria um novo bloco com o espaço restante
                new_block->next = current->next;                                              // Atualiza o ponteiro do próximo bloco
                current->next = new_block;                                                    // Atualiza o ponteiro do próximo bloco do bloco atual
            }

            current->size = request_size; // Ajusta o tamanho do bloco atual
            current->is_free = false;     // Marca o bloco como ocupado
            current->id = request_id;     // Define o ID do bloco

            return; // Retorna após a alocação bem-sucedida
        }
        current = current->next; // Move para o próximo bloco
    }
}

void ListManager::deallocate_memory(MemoryRequest *request)
{
    MemoryBlock *current = head; // Inicia a busca do início da lista
    MemoryBlock *last = nullptr; // Ponteiro para o bloco anterior

    while (current)
    {
        if (current->id == request->request_id) // Verifica se o bloco atual corresponde ao ID do pedido de desalocação
        {
            total_deallocated_bytes += current->size; // Atualiza o total de bytes desalocados
            deallocations++;                          // Incrementa o contador de desalocações

            if (last != nullptr && last->is_free) // Se o bloco anterior está livre, une com o bloco atual
            {
                last->size += current->size; // Atualiza o tamanho do bloco anterior
                last->next = current->next;  // Atualiza o ponteiro do próximo bloco do bloco anterior
                delete current;              // Libera a memória do bloco atual
                current = last;              // Define o bloco atual como o bloco anterior
            }

            if (current->next != nullptr && current->next->is_free) // Se o próximo bloco está livre, une com o bloco atual
            {
                current->size += current->next->size; // Atualiza o tamanho do bloco atual
                MemoryBlock *temp = current->next;    // Ponteiro temporário para o próximo bloco
                current->next = current->next->next;  // Atualiza o ponteiro do próximo bloco
                delete temp;                          // Libera a memória do próximo bloco
            }

            current->is_free = true; // Marca o bloco como livre
            current->id = -1;        // Reseta o ID do bloco
            break;                   // Sai do loop após desalocação bem-sucedida
        }
        last = current;          // Atualiza o bloco anterior
        current = current->next; // Move para o próximo bloco
    }
}

void ListManager::print_memory()
{
    MemoryBlock *current = head; // Inicia a partir do primeiro bloco

    while (current)
    {
        cout << current->size << " " << (current->is_free ? 0 : 1) << endl; // Imprime o tamanho do bloco e se está livre ou ocupado
        current = current->next;                                            // Move para o próximo bloco
    }

    cout << (total_allocated_bytes - total_deallocated_bytes) << " //quantidade de bytes em uso (ocupados)" << endl;
    cout << total_allocated_bytes << " //quantidade de bytes alocados" << endl;
    cout << total_deallocated_bytes << " //quantidade de bytes desalocados" << endl;
    cout << allocations << " //número de alocações" << endl;
    cout << deallocations << " //número de desalocações" << endl;
}
