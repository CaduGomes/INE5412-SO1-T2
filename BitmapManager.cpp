#include "BitmapManager.hpp" // Inclui a definição da classe BitmapManager
#include <cmath>             // Inclui a biblioteca para operações matemáticas (ex. ceil)

// Método para processar um pedido de memória
void BitmapManager::request_memory(MemoryRequest *request)
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

// Método para alocar memória (chama request_memory)
void BitmapManager::allocate_memory(MemoryRequest *request)
{
    int request_size = request->request_size;
    if (request->request_size < min_block_size) // Ajusta o tamanho do pedido se for menor que o tamanho mínimo do bloco
    {
        request_size = min_block_size;
    }

    int blocks_needed = static_cast<int>(std::ceil(static_cast<double>(request_size) / min_block_size)); // Calcula o número de blocos necessários arredondando para cima

    if (allocation_algorithm == 1) // Verifica qual algoritmo de alocação usar
    {
        first_fit_algorithm(blocks_needed, request->request_id); // Usa o algoritmo First-Fit
    }
    else
    {
        next_fit_algorithm(blocks_needed, request->request_id); // Usa o algoritmo Next-Fit
    }
}

// Algoritmo First-Fit para alocação de memória
void BitmapManager::first_fit_algorithm(int blocks_needed, int request_id)
{
    int blocks_free_count = 0;
    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        if (bitmap[i] == 0) // Verifica se o bloco está livre
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed) // Verifica se encontrou blocos livres suficientes
            {
                for (size_t j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    total_allocated_bytes += min_block_size; // Atualiza o total de bytes alocados
                    request_id_map[j] = request_id;          // Registra o ID do pedido
                    bitmap[j] = 1;                           // Marca o bloco como ocupado
                }
                return;
            }
        }
        else
        {
            blocks_free_count = 0; // Reinicia o contador de blocos livres se encontrar um bloco ocupado
        }
    }
}

// Algoritmo Next-Fit para alocação de memória
void BitmapManager::next_fit_algorithm(int blocks_needed, int request_id)
{
    int blocks_free_count = 0;
    for (size_t i = last_fit_index; i < bitmap.size(); ++i)
    {
        if (bitmap[i] == 0) // Verifica se o bloco está livre
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed) // Verifica se encontrou blocos livres suficientes
            {
                for (size_t j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    total_allocated_bytes += min_block_size; // Atualiza o total de bytes alocados
                    allocations++;                           // Incrementa o contador de alocações
                    request_id_map[j] = request_id;          // Registra o ID do pedido
                    bitmap[j] = 1;                           // Marca o bloco como ocupado
                }
                last_fit_index = i + 1; // Atualiza a última posição de alocação
                return;
            }
        }
        else
        {
            blocks_free_count = 0; // Reinicia o contador de blocos livres se encontrar um bloco ocupado
        }
    }

    blocks_free_count = 0;

    for (int i = 0; i < last_fit_index + 1; ++i)
    {
        if (bitmap[i] == 0) // Verifica se o bloco está livre
        {
            ++blocks_free_count;
            if (blocks_free_count == blocks_needed) // Verifica se encontrou blocos livres suficientes
            {
                for (int j = i + 1 - blocks_needed; j <= i; ++j)
                {
                    total_allocated_bytes += min_block_size; // Atualiza o total de bytes alocados
                    allocations++;                           // Incrementa o contador de alocações
                    request_id_map[j] = request_id;          // Registra o ID do pedido
                    bitmap[j] = 1;                           // Marca o bloco como ocupado
                }

                last_fit_index = i + 1; // Atualiza a última posição de alocação
                return;
            }
        }
        else
        {
            blocks_free_count = 0; // Reinicia o contador de blocos livres se encontrar um bloco ocupado
        }
    }
}

// Método para desalocar memória
void BitmapManager::deallocate_memory(MemoryRequest *request)
{
    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        if (request_id_map[i] == request->request_id) // Verifica se o bloco corresponde ao ID do pedido de desalocação
        {
            total_deallocated_bytes += min_block_size; // Atualiza o total de bytes desalocados
            deallocations++;                           // Incrementa o contador de desalocações
            bitmap[i] = 0;                             // Marca o bloco como livre
            request_id_map[i] = -1;                    // Reseta o ID do bloco
        }
    }
}

// Método para imprimir o estado da memória
void BitmapManager::print_memory()
{
    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        cout << bitmap[i]; // Imprime o estado de cada bloco (0 para livre, 1 para ocupado)
    }
    cout << endl;

    cout << (total_allocated_bytes - total_deallocated_bytes) << " //quantidade de bytes em uso (ocupados)" << endl;
    cout << total_allocated_bytes << " //quantidade de bytes alocados" << endl;
    cout << total_deallocated_bytes << " //quantidade de bytes desalocados" << endl;
    cout << allocations << " //número de alocações" << endl;
    cout << deallocations << " //número de desalocações" << endl;
}
