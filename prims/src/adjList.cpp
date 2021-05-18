#include "adjList.hpp"
#include "structs.hpp"

vertice *adjList::find(std::string value)
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
                newNode->key = line;
                AdjList.push_back(newNode);
            }
            else
            {
                allNodesAdded = true;
            }

            if (allNodesAdded && line != "")
            {
                std::string vertice1Name = getName(0, line);
                std::string vertice2Name = getName(vertice1Name.length() + 1, line);
                vertice *vertice1 = find(vertice1Name);
                vertice *vertice2 = find(vertice2Name);

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

                Edge->weight = getWeight(line, (vertice1Name.length() + 1 + vertice2Name.length() + 1));
            }
        }
    }
    else
    {
        throw std::invalid_argument("File could not be opened");
    }
}

std::string adjList::getName(const int& startIndex, const std::string &line)
{
    std::string name;
    int iterator = startIndex;
    while(line[iterator] != '\t')
    {
        name += line[iterator];
        iterator++;
    }
    return name;
}

int adjList::getWeight(std::string line, const int& startIndex)
{
    std::string numberString = "";
    int iterator = startIndex;
    int number = 0;
    while (iterator < line.length())
    {
        numberString += line[iterator];
        iterator++;
    }
    number = std::stoi(numberString);
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

adjList::~adjList()
{
    verticeEdge *walker1;
    verticeEdge *walker2;
    edge *currentEdge;
    verticeEdge *oldEdgeHolder;
    for (int i = 0; i < AdjList.size(); i++)
    {
        walker1 = AdjList[i]->edgeStart;
        AdjList[i]->edgeStart = nullptr;
        while (walker1 != nullptr)
        {
            if (walker1->vertice_edge != nullptr)
            {
                currentEdge = walker1->vertice_edge;
                if (AdjList[i] == currentEdge->node1)
                {
                    walker2 = currentEdge->node2->edgeStart;
                }
                else
                {
                    walker2 = currentEdge->node1->edgeStart;
                }

                while (walker2->vertice_edge != currentEdge)
                {
                    walker2 = walker2->next;
                }
                walker2->vertice_edge = nullptr;

                delete currentEdge;
            }

            oldEdgeHolder = walker1;
            walker1 = walker1->next;
            delete oldEdgeHolder;
        }
        delete AdjList[i];
    }
}
