#ifndef ADJ_LIST
#define ADJ_LIST

#include <fstream>
#include <iostream>
#include <vector>

#include "structs.hpp"

class adjList
{
private:
    vertice* find(char value);
    int getWeight(std::string line);

    std::vector<vertice*> AdjList;

public:
    ~adjList();

    void createAdjList(std::string Filename);
    void printList();
    void push(vertice* newVertice);
    int size();

    vertice* operator[](const int& index);
};

#endif
