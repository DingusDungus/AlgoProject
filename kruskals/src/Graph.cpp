#include "Graph.hpp"

#include <iostream>

bool Comparator::operator()(const Edge& edge1, const Edge& edge2)
{
    if (edge1.weight > edge2.weight)
    {
        return true;
    }
    return false;
}

void MST::debugPrint()
{
    while (!pQueue.empty())
    {
        std::cout << pQueue.top().from->key << " ";
        std::cout << pQueue.top().to->key << " ";
        std::cout << pQueue.top().weight << std::endl;
        pQueue.pop();
    }
}

MST::MST(std::string fileName) { fromFile(fileName); }

MST::~MST()
{

}

Vert* MST::findVert(char value)
{
    for (int i = 0; i < verts.size(); i++)
    {
        if (verts[i]->key == value)
        {
            return verts[i];
        }
    }
    return nullptr;
}

int MST::getWeight(std::string line)
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

void MST::fromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    bool allVertsAdded = false;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line != "" && allVertsAdded == false)
            {
                Vert* newVert = new Vert(line[0]);
                verts.push_back(newVert);
            }
            else
            {
                allVertsAdded = true;
            }

            if (allVertsAdded && line != "")
            {
                Vert* from = findVert(line[0]);
                Vert* to = findVert(line[2]);

                if (from == nullptr || to == nullptr)
                {
                    throw std::invalid_argument(
                        "Invalid structure in textfile");
                }
                int weight = getWeight(line);
                Edge edge = Edge(from, to, weight);
                pQueue.push(edge);
            }
        }
    }
    else
    {
        throw std::invalid_argument("File could not be opened");
    }
}
