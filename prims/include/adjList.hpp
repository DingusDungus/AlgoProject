#ifndef ADJ_LIST
#define ADJ_LIST

#include <fstream>
#include <iostream>
#include <vector>

#include "structs.hpp"

class adjList
{
private:
    vertice* find(std::string value);
    int getWeight(std::string line, const int& startIndex);
    std::string getName(const int& startIndex, const std::string &line);

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
