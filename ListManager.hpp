#ifndef ListManager_HPP
#define ListManager_HPP

#include <iostream>          // Inclui a biblioteca padrão de entrada/saída
#include <fstream>           // Inclui a biblioteca para manipulação de arquivos
#include <vector>            // Inclui a biblioteca de vetores
#include "MemoryManager.hpp" // Inclui a definição da classe base MemoryManager

using namespace std; // Utiliza o namespace padrão

// Classe MemoryBlock representa um bloco de memória
class MemoryBlock
{
public:
    int size;          // Tamanho do bloco de memória
    bool is_free;      // Indica se o bloco está livre
    int id;            // Identificador do bloco de memória
    MemoryBlock *next; // Ponteiro para o próximo bloco na lista

    // Construtor para inicializar os membros da classe MemoryBlock
    MemoryBlock(int size, bool is_free, int id = -1)
        : size(size), is_free(is_free), id(id), next(nullptr) {}
};

// Classe ListManager gerencia a memória usando uma lista encadeada de blocos de memória
class ListManager : public MemoryManager
{
public:
    // Construtor que inicializa o gerenciador de memória
    ListManager(int free_memory_size, int page_size, int allocation_algorithm)
        : MemoryManager(free_memory_size, page_size, allocation_algorithm)
    {
        head = new MemoryBlock(free_memory_size, true); // Inicializa o bloco de memória principal
        last_alloc = head;                              // Define o último bloco alocado como o bloco inicial
    };

    // Sobrescreve o método request_memory da classe base MemoryManager
    void request_memory(MemoryRequest *request) override;

    // Sobrescreve o método allocate_memory da classe base MemoryManager
    void allocate_memory(MemoryRequest *request) override;

    // Sobrescreve o método deallocate_memory da classe base MemoryManager
    void deallocate_memory(MemoryRequest *request) override;

    // Implementa o algoritmo First-Fit para alocação de memória
    void first_fit_algorithm(int request_size, int request_id);

    // Implementa o algoritmo Next-Fit para alocação de memória
    void next_fit_algorithm(int request_size, int request_id);

    // Sobrescreve o método print_memory da classe base MemoryManager para imprimir o estado da memória
    void print_memory() override;

private:
    MemoryBlock *head = nullptr;       // Ponteiro para o primeiro bloco na lista
    MemoryBlock *last_alloc = nullptr; // Ponteiro para o último bloco alocado
};

#endif
