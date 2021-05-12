#include "Graph.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        return -1;
    }

    Edge edge('A', 'B', 2);
    Edge edge2('C', 'D', 4);
    std::cout << (edge < edge2) << std::endl;
    std::cout << (edge2 < edge) << std::endl;

    return 0;
}
