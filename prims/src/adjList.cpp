#include "adjList.hpp"
#include "structs.hpp"

vertice *adjList::find(char value)
{
    for (int i = 0; i < AdjList.size(); i++)
    {
        if (AdjList[i]->key == value)
        {
            return AdjList[i];
        }
    }
    return nullptr;
}

void adjList::createAdjList(std::string Filename)
{
    std::ifstream file;
    file.open(Filename);
    bool allNodesAdded = false;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line != "" && allNodesAdded == false)
            {
                vertice *newNode = new vertice;
                newNode->key = line[0];
                AdjList.push_back(newNode);
            }
            else
            {
                allNodesAdded = true;
            }

            if (allNodesAdded && line != "")
            {
                vertice *vertice1 = find(line[0]);
                vertice *vertice2 = find(line[2]);

                if (vertice1 == nullptr || vertice2 == nullptr)
                {
                    throw std::invalid_argument(
                        "Invalid structure in textfile");
                }
                verticeEdge *verNode1 = new verticeEdge;
                verticeEdge *verNode2 = new verticeEdge;
                edge *Edge = new edge;
                verNode1->vertice_edge = Edge;
                verNode2->vertice_edge = Edge;

                Edge->node1 = vertice2;
                Edge->node2 = vertice1;

                verNode1->next = vertice1->edgeStart;
                vertice1->edgeStart = verNode1;
                verNode2->next = vertice2->edgeStart;
                vertice2->edgeStart = verNode2;

                Edge->weight = getWeight(line);
            }
        }
    }
    else
    {
        throw std::invalid_argument("File could not be opened");
    }
}

int adjList::getWeight(std::string line)
{
    std::string numberString;
    int iterator = 4;
    while (line[iterator] != ' ')
    {
        numberString += line[iterator];
        iterator++;
    }
    int number = std::stoi(numberString);
    return number;
}

void adjList::printList()
{
    for (int i = 0; i < AdjList.size(); i++)
    {
        std::cout << "Vertice: " << AdjList[i]->key << " ";
        verticeEdge *walker = AdjList[i]->edgeStart;
        while (walker->next != nullptr)
        {
            std::cout << "(" << walker->vertice_edge->node1->key << ", " << walker->vertice_edge->node2->key
                      << ", " << walker->vertice_edge->weight << "), ";
            walker = walker->next;
        }
        if (walker->next == nullptr)
        {
            std::cout << "(" << walker->vertice_edge->node1->key << ", " << walker->vertice_edge->node2->key
                      << ", " << walker->vertice_edge->weight << ")";
        }
        std::cout << "\n";
    }
}

vertice *adjList::operator[](const int &index)
{
    if (index >= AdjList.size() || index < 0)
    {
        throw std::invalid_argument("Index out of range! operator[]");
    }
    return AdjList[index];
}

int adjList::size() { return AdjList.size(); }

void adjList::push(vertice *newVertice)
{
    AdjList.push_back(newVertice);
}
