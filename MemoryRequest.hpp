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

public:
    char request_type; // A ou D
    int request_id;
    int request_size = -1; // Utilizado para alocação em bytes
};

#endif