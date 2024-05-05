#include "BitmapManager.hpp"
#include "ListManager.hpp"
#include "FirstFitAlgorithm.hpp"
#include "NextFitAlgorithm.hpp"

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

	int allocation_algorithm = std::stoi(linha);

	vector<MemoryRequest *> requests;

	while (std::getline(std::cin, linha))
	{
		MemoryRequest *request = new MemoryRequest(linha);
		requests.push_back(request);
	}

	AllocationAlgorithm *algorithm = nullptr;

	switch (allocation_algorithm)
	{
	case 1:
		algorithm = new FirstFitAlgorithm();
		break;
	case 2:
		algorithm = new NextFitAlgorithm();
		break;
	}

	MemoryManager *manager = nullptr;

	switch (manager_type)
	{
	case Bitmap:
		manager = new BitmapManager(free_memory_size, page_size, algorithm);
		break;
	case List:
		manager = new ListManager(free_memory_size, page_size, algorithm);
		break;
	}

	for (MemoryRequest *request : requests)
	{
		manager->request_memory(request);
	}

	// std::cout << "Memory Manager: " << manager->getName() << std::endl;

	// std::cout << "Memory size: " << free_memory_size << std::endl;

	// std::cout << "Page size: " << page_size << std::endl;

	// std::cout << "allocation algorithm: " << manager->getallocationAlgorithm() << std::endl;

	// std::cout << "Memory usage: " << manager->getMemoryUsage() << std::endl;

	// std::cout << "Memory waste: " << manager->getMemoryWaste() << std::endl;

	return 0;
}
