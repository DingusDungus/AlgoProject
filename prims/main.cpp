#include "adjList.hpp"
#include "prim.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Wrong number of Command line arguments, expected 1 "
                     ":)\n>>> ./algo.app <inFile.txt> <outFile.txt>"
                  << std::endl;
        return 0;
    }


    Prim prim(argv[1]);
    std::string MST = prim.primMST();
    std::cout << MST;
    prim.createMSTfile(argv[2]);
    return 0;
}
