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
    // std::cout << "Total number of vertices: " << nrOfVerts << std::endl;
    // while (!pQueue.empty())
    //{
    // std::cout << pQueue.top().from->key << " ";
    // std::cout << pQueue.top().to->key << " ";
    // std::cout << pQueue.top().weight << std::endl;
    // pQueue.pop();
    //}
}

void MST::toFile(std::string filename)
{
    std::ofstream mstFile;
    mstFile.open(filename);
    mstFile.clear();

    mstFile << toString();

    mstFile.close();
}

std::string MST::toString()
{
    std::string toReturn = "";
    for (int i = 0; i < verts.size(); i++) {
        toReturn += verts[i]->key + "\n";
    }
    toReturn += "\n";
    for (int i = 0; i < doneMST.size(); i++)
    {
        toReturn += doneMST[i].toString() + "\n";
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
    // path compression
    if (vert != walker)
    {
        vert->parent = walker;
    }
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
        pQueue.pop();
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

Vert* MST::findVert(std::string value)
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

std::string MST::getName(const int& startIndex, const std::string& line)
{
    std::string name;
    int iterator = startIndex;
    while (line[iterator] != '\t')
    {
        name += line[iterator];
        iterator++;
    }
    return name;
}

int MST::getWeight(std::string line, const int& startIndex)
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

void MST::fromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    bool allNodesAdded = false;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line != "" && allNodesAdded == false)
            {
                Vert* newNode = new Vert(line);
                verts.push_back(newNode);
            }
            else
            {
                allNodesAdded = true;
            }

            if (allNodesAdded && line != "")
            {
                std::string vertice1Name = getName(0, line);
                std::string vertice2Name =
                    getName(vertice1Name.length() + 1, line);
                Vert* from = findVert(vertice1Name);
                Vert* to = findVert(vertice2Name);

                if (from == nullptr || to == nullptr)
                {
                    throw std::invalid_argument(
                        "Invalid structure in textfile");
                }

                int weight = getWeight(line, (vertice1Name.length() + 1 +
                                              vertice2Name.length() + 1));
                Edge edge = Edge(from, to, weight);
                std::cout << "Adding edge: " << edge.toString() << std::endl;
                pQueue.push(edge);
            }
        }
    }
    else
    {
        throw std::invalid_argument("File could not be opened");
    }
}
