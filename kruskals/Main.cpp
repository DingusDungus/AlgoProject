#include <iostream>

#include "Graph.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        return -1;
    }


    MST mst(argv[1]);
    mst.debugPrint();

    return 0;
}
