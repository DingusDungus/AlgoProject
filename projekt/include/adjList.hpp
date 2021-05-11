#ifndef ADJ_LIST
#define ADJ_LIST

#include <iostream>
#include <vector>
#include <fstream>

class adjList
{
private:
    struct edge;
    struct vertice;
    vertice *find(char value);
    int getWeight(std::string line);

    std::vector<vertice *> AdjList;

public:
    void createAdjList(std::string Filename);
    void printList();
};

#endif