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
    adjList MST;
    vertice *current = AdjList[0];
    vertice *ancestor = nullptr;
    int verticesAdded = 0;
    while (verticesAdded <= AdjList.size())
    {
        if (current != ancestor)
        {
            current->used = true;
            verticesAdded++;
            verticeEdge *walker = current->edgeStart;
            while (walker != nullptr)
            {
                if (!walker->vertice_edge->used)
                {
                    priorityQueue.push(walker->vertice_edge);
                }
                walker = walker->next;
            }
        }
        edge *chosenEdge = priorityQueue.top();
        chosenEdge->used = true;
        priorityQueue.pop();
        if (!chosenEdge->node1->used || !chosenEdge->node2->used)
        {
            vertice *newVertice = new vertice;
            verticeEdge *newVerticeEdge = new verticeEdge;
            newVerticeEdge->next = newVertice->edgeStart;
            newVertice->edgeStart = newVerticeEdge;
            newVerticeEdge->vertice_edge = chosenEdge;

            ancestor = current;
            if (!chosenEdge->node1->used)
            {
                current = chosenEdge->node1;
                newVertice->key = current->key;
            }
            else
            {
                current = chosenEdge->node2;
                newVertice->key = current->key;
            }
            MST.push(newVertice);
        }
    }

    MST.printList();

    return "";
}
