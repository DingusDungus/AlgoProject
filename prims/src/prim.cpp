#include "prim.hpp"

bool Comparator::operator()(edge *edge1, edge *edge2)
{
    if ((!edge1->used && edge2->used) || (edge1->weight > edge2->weight))
    {
        return true;
    }
    return false;
}

Prim::Prim(std::string Filename)
{
    AdjList.createAdjList(Filename);
    for (int i = 0; i < AdjList.size(); i++)
    {
        MST += AdjList[i]->key;
        MST.push_back('\n');
    }
    MST.push_back('\n');
    std::cout << "Size: " << AdjList.size() << "\n";
}

std::string Prim::primMST()
{
    vertice *current = AdjList[0];
    vertice *ancestor = nullptr;
    int verticesAdded = 0;
    edge *chosenEdge;
    verticeEdge *walker;

    while (verticesAdded < AdjList.size() - 1)
    {
        if (current != ancestor)
        {
            current->used = true;
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
            MST += chosenEdge->node1->key;
            MST.push_back('\t');
            MST += chosenEdge->node2->key;
            MST.push_back('\t');
            MST += std::to_string(chosenEdge->weight);
            if (verticesAdded < AdjList.size() - 1)
            {
                MST.push_back('\n');
            }
            verticesAdded++;
        }
    }

    return MST;
}

void Prim::createMSTfile(std::string fileName) const
{
    std::ofstream mstFile;
    mstFile.open(fileName);
    mstFile.clear();

    mstFile << MST;

    mstFile.close();
}
