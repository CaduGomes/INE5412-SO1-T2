#include "MemoryRequest.hpp"

MemoryRequest::MemoryRequest(string input)
{
    request_type = input[0];
    request_id = input[input.length() - 1] - '0';

    if (request_type == 'A')
    {
        request_size = stoi(input.substr(2, input.length() - 3));
    }
}