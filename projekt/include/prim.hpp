#ifndef PRIM
#define PRIM

#include <queue>

#include "adjList.hpp"

struct Comparator{
    bool operator()(edge *edge1, edge *edge2)
    {
        return edge1 < edge2;
    }
};

class Prim
{
private:
    adjList AdjList;
    std::priority_queue<edge *, std::vector<edge *>, Comparator> priorityQueue;
};

#endif