#include <iostream>

#include "Graph.hpp"

int main(int argc, char* argv[])
{
    /*
     if (argc < 3)
     {
         return -1;
     }
     */

    MST mst("graph.txt");
    //mst.debugPrint();
    std::cout << "\nKruskals MST:" << std::endl;
    std::cout << mst.toString() << std::endl;

    return 0;
}
