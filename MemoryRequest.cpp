#include "MemoryRequest.hpp" // Inclui a definição da classe MemoryRequest

// Construtor da classe MemoryRequest que inicializa um objeto a partir de uma string de entrada
MemoryRequest::MemoryRequest(std::string input)
{
    request_type = input[0]; // O tipo de pedido (alocação 'A' ou desalocação 'D') é o primeiro caractere da string

    request_id = input[input.length() - 1] - '0'; // O ID do pedido é o último caractere da string, convertido de char para int

    if (request_type == 'A') // Se o tipo de pedido for alocação
    {
        // O tamanho do pedido é extraído da string, começando no terceiro caractere (índice 2)
        // até o penúltimo caractere (para excluir o ID)
        request_size = std::stoi(input.substr(2, input.length() - 3));
    }
}
