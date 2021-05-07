#ifndef ADJ_LIST
#define ADJ_LIST

#include <iostream>
#include <vector>
#include <fstream>

class adjList
{
private:
    struct edge
    {
        char from;
        char to;
        edge *next;
        int weight;
        edge()
        {
            weight = -1;
            next = nullptr;
        }
    };
    struct vertice
    {
        char key;
        edge *edgeStart;
        vertice() { edgeStart = nullptr; }
    };
    vertice *find(char value);
    int getWeight(std::string line);

    std::vector<vertice *> AdjList;

public:
    void createAdjList(std::string Filename);
    void printList();
};

#endif