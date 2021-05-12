#include "prim.hpp"

bool Comparator::operator()(edge *edge1, edge *edge2)
{
    if (!edge1->used && edge1->weight > edge2->weight)
    {
        return true;
    }
    return false;
}

Prim::Prim(std::string Filename)
{
    AdjList.createAdjList(Filename);
}

std::string Prim::primMST()
{
    verticeEdge *walker = AdjList[0]->edgeStart;
    while (walker != nullptr)
    {
        priorityQueue.push(walker->vertice_edge);
        walker = walker->next;
    }

    for (int i = 0; i < priorityQueue.size(); i++)
    {
        edge *yes = priorityQueue.top();
        priorityQueue.pop();
        std::cout << yes->node2->key << yes->weight << "\n";
    }
    return "";
}
