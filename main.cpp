#include "BitmapManager.hpp"
#include "ListManager.hpp"

#include <sstream>

enum ManagerType
{
	Bitmap = 1,
	List = 2,
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

	if (allocation_algorithm < 1 || allocation_algorithm > 2)
	{
		std::cerr << "Invalid allocation algorithm" << std::endl;
		return 1;
	}

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
		manager = new BitmapManager(free_memory_size, page_size, allocation_algorithm);
		break;
	case List:
		manager = new ListManager(free_memory_size, page_size, allocation_algorithm);
		break;
	}

	for (MemoryRequest *request : requests)
	{
		manager->request_memory(request);
	}

	manager->print_memory();
	return 0;
}
