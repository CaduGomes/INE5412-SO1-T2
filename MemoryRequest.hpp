#ifndef MemoryRequest_HPP
#define MemoryRequest_HPP
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MemoryRequest
{

public:
    MemoryRequest(string input);
    bool is_allocation() { return request_type == 'A'; }

public:
    int request_id;
    int request_size = -1; // Utilizado para alocação em bytes

private:
    char request_type; // A ou D
};

#endif