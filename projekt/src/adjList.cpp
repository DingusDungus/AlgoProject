#include "adjList.hpp"

struct edge
{
    vertice *from;
    vertice * to;
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
                    throw std::invalid_argument("Invalid structure in textfile");
                }

                edge *ver1Edge = new edge;
                ver1Edge->to = vertice2;
                ver1Edge->from = vertice1;
                ver1Edge->next = vertice1->edgeStart;
                vertice1->edgeStart = ver1Edge;
                ver1Edge->weight = getWeight(line);

                edge *ver2Edge = new edge;
                ver2Edge->from = vertice2;
                ver2Edge->to = vertice1;
                ver2Edge->next = vertice2->edgeStart;
                vertice2->edgeStart = ver1Edge;
                ver2Edge->weight = ver1Edge->weight;
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
        edge *walker = AdjList[i]->edgeStart;
        while (walker->next != nullptr)
        {
            std::cout << "(" << walker->from->key << ", " << walker->to->key << ", " << walker->weight << "), ";
            walker = walker->next;
        }
        if (walker->next == nullptr)
        {
            std::cout << "(" << walker->from->key << ", " << walker->to->key << ", " << walker->weight << ")";
        }
        std::cout << "\n";
    }
}

vertice *adjList::operator[](const int& index)
{
    if (index >= AdjList.size() || index < 0)
    {
        throw std::invalid_argument("Index out of range! operator[]");
    }
    return AdjList[index];
}
