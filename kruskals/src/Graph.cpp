#include "Graph.hpp"

#include <iostream>
#include <string>

bool Comparator::operator()(const Edge& edge1, const Edge& edge2)
{
    if (edge1.weight > edge2.weight)
    {
        return true;
    }
    return false;
}

MST::MST(std::string fileName)
{
    // read vertices and edges from file
    fromFile(fileName);
    nrOfVerts = verts.size();
    // run kruskals
    kruskals();
}

void MST::debugPrint()
{
    std::cout << "Total number of vertices: " << nrOfVerts << std::endl;
    while (!pQueue.empty())
    {
        std::cout << pQueue.top().from->key << " ";
        std::cout << pQueue.top().to->key << " ";
        std::cout << pQueue.top().weight << std::endl;
        pQueue.pop();
    }
}

std::string MST::toString()
{
    std::string toReturn = "";
    for (int i = 0; i < doneMST.size(); i++) {
        toReturn += doneMST[i].toString();
    }
    return toReturn;
}

Vert* MST::findAbsoluteParent(Vert* vert)
{
    Vert* walker = vert;
    while (walker->parent != nullptr)
    {
        walker = walker->parent;
    }
    vert->parent = walker;  // path compression
    return walker;
}

void MST::setUnion(Vert* fromParent, Vert* toParent)
{
    if (fromParent->rank > toParent->rank)
    {
        toParent->parent = fromParent;
    }
    else if (fromParent->rank < toParent->rank)
    {
        fromParent->parent = toParent;
    }
    else  // they have the same rank
    {
        fromParent->parent = toParent;
        toParent->rank += 1;
    }
}

void MST::kruskals()
{
    int addedEdges = 0;
    while (addedEdges < nrOfVerts - 1 && !pQueue.empty())
    {
        Edge currentEdge = pQueue.top();
        Vert* fromParent = findAbsoluteParent(currentEdge.from);
        Vert* toParent = findAbsoluteParent(currentEdge.to);

        if (fromParent != toParent)
        {
            setUnion(fromParent, toParent);
            doneMST.push_back(currentEdge);
            addedEdges++;
        }
    }
}

MST::~MST()
{
    // delete all vertice pointers
    for (int i = 0; i < verts.size(); i++)
    {
        delete verts[i];
    }
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
