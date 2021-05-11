#ifndef ADJ_LIST
#define ADJ_LIST

#include <fstream>
#include <iostream>
#include <vector>

struct edge;
struct vertice;

class adjList
{
private:
    vertice* find(char value);
    int getWeight(std::string line);

    std::vector<vertice*> AdjList;

public:
    void createAdjList(std::string Filename);
    void printList();

    vertice* operator[](const int& index);
};

#endif
