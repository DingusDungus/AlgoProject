#include "adjList.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Wrong number of Command line arguments, expected 2 "
                     ":)\n>>> ./algo.app <inFile.txt> <outFile.txt>"
                  << std::endl;
        return 0;
    }
    adjList adjList;
    adjList.createAdjList("graph.txt");
    adjList.printList();
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
