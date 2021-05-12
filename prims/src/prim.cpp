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
    std::string MST;
    vertice *current = AdjList[0];
    vertice *ancestor = nullptr;
    int verticesAdded = 0;
    edge *chosenEdge;
    verticeEdge *walker;

    while (verticesAdded <= AdjList.size())
    {
        if (current != ancestor)
        {
            current->used = true;
            verticesAdded++;
            walker = current->edgeStart;
            while (walker != nullptr)
            {
                if (!walker->vertice_edge->used)
                {
                    priorityQueue.push(walker->vertice_edge);
                }
                walker = walker->next;
            }
        }
        
        chosenEdge = priorityQueue.top();
        priorityQueue.pop();
        chosenEdge->used = true;
        if (!chosenEdge->node1->used || !chosenEdge->node2->used)
        {

            ancestor = current;
            if (!chosenEdge->node1->used)
            {
                current = chosenEdge->node1;
            }
            else
            {
                current = chosenEdge->node2;
            }
            MST.push_back(chosenEdge->node1->key);
            MST.push_back(' ');
            MST.push_back(chosenEdge->node2->key);
            MST.push_back(' ');
            MST += std::to_string(chosenEdge->weight);
            MST.push_back('\n');
        }
    }

    return MST;
}
