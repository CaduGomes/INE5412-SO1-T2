#include "MemoryRequest.hpp"
#include "BitmapManager.hpp"
#include "ListManager.hpp"

#include <sstream>

enum ManagerType
{
	Bitmap = 1,
	List,
};

int main()
{

	std::string linha;

	std::getline(std::cin, linha);

	ManagerType manager_type = static_cast<ManagerType>(std::stoi(linha));

	std::getline(std::cin, linha);

	int free_memory_size = std::stoi(linha);

	std::getline(std::cin, linha);

	int page_size = std::stoi(linha);

	std::getline(std::cin, linha);

	int alocation_algorithm = std::stoi(linha);

	vector<MemoryRequest *> requests;

	while (std::getline(std::cin, linha))
	{
		MemoryRequest *request = new MemoryRequest(linha);
		requests.push_back(request);
	}

	MemoryManager *manager = nullptr;

	switch (manager_type)
	{
	case Bitmap:
		manager = new BitmapManager(free_memory_size, page_size, alocation_algorithm);
		break;
	case List:
		manager = new ListManager(free_memory_size, page_size, alocation_algorithm);
		break;
	}

	for (MemoryRequest *request : requests)
	{
		manager->requestMemory(request);
	}

	// std::cout << "Memory Manager: " << manager->getName() << std::endl;

	// std::cout << "Memory size: " << free_memory_size << std::endl;

	// std::cout << "Page size: " << page_size << std::endl;

	// std::cout << "Alocation algorithm: " << manager->getAlocationAlgorithm() << std::endl;

	// std::cout << "Memory usage: " << manager->getMemoryUsage() << std::endl;

	// std::cout << "Memory waste: " << manager->getMemoryWaste() << std::endl;

	return 0;
}
