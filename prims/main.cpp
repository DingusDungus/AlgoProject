#include "adjList.hpp"
#include "prim.hpp"

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

    Prim prim(argv[1]);
    std::string MST = prim.primMST();
    std::cout << MST;
    return 0;
}
