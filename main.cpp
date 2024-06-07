#include "BitmapManager.hpp" // Inclui a definição da classe BitmapManager
#include "ListManager.hpp"	 // Inclui a definição da classe ListManager

#include <sstream> // Inclui a biblioteca para manipulação de strings

enum ManagerType
{
	Bitmap = 1, // Enumeração para representar o tipo de gerenciador de memória Bitmap
	List = 2,	// Enumeração para representar o tipo de gerenciador de memória Lista
};

int main()
{
	std::string linha;

	std::getline(std::cin, linha); // Lê a primeira linha da entrada padrão (stdin)

	ManagerType manager_type = static_cast<ManagerType>(std::stoi(linha)); // Converte a linha lida para um número inteiro e depois para o tipo ManagerType

	std::getline(std::cin, linha); // Lê a segunda linha da entrada padrão

	int free_memory_size = std::stoi(linha); // Converte a linha lida para um número inteiro, representando o tamanho total da memória livre

	std::getline(std::cin, linha); // Lê a terceira linha da entrada padrão

	int min_block_size = std::stoi(linha); // Converte a linha lida para um número inteiro, representando o tamanho da página ou bloco de alocação mínima

	std::getline(std::cin, linha); // Lê a quarta linha da entrada padrão

	int allocation_algorithm = std::stoi(linha); // Converte a linha lida para um número inteiro, representando o algoritmo de alocação

	if (allocation_algorithm < 1 || allocation_algorithm > 2)
	{
		cout << "Invalid allocation algorithm" << endl; // Imprime uma mensagem de erro se o algoritmo de alocação for inválido
		return 1;										// Sai do programa com código de erro 1
	}

	std::vector<MemoryRequest *> requests; // Cria um vetor para armazenar os pedidos de memória

	while (std::getline(std::cin, linha))
	{
		MemoryRequest *request = new MemoryRequest(linha); // Cria um novo pedido de memória a partir da linha lida
		requests.push_back(request);					   // Adiciona o pedido de memória ao vetor
	}

	MemoryManager *manager = nullptr; // Declara um ponteiro para o gerenciador de memória

	switch (manager_type)
	{
	case Bitmap:
		manager = new BitmapManager(free_memory_size, min_block_size, allocation_algorithm); // Cria uma instância do gerenciador BitmapManager se o tipo for Bitmap
		break;
	case List:
		manager = new ListManager(free_memory_size, min_block_size, allocation_algorithm); // Cria uma instância do gerenciador ListManager se o tipo for Lista
		break;
	}

	for (MemoryRequest *request : requests)
	{
		manager->request_memory(request); // Processa cada pedido de memória usando o gerenciador de memória
	}

	manager->print_memory(); // Imprime o estado atual da memória gerenciada
	return 0;
}
