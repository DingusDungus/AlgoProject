#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <queue>
#include <string>
#include <vector>

// Vertice Struct
// For kruskals algorithm
struct Vert
{
    std::string key;
    Vert* parent = nullptr;
    int rank = 0;
    Vert(std::string key) { this->key = key; }
};

// Edge Struct
// For kruskals algorithm
struct Edge
{
    Vert* from = nullptr;
    Vert* to = nullptr;
    int weight = -1;
    Edge(Vert* from, Vert* to, int weight)
    {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
    Edge(int weight) { this->weight = weight; }
    friend bool operator<(const Edge& l, const Edge& r)
    {
        return l.weight < r.weight;
    }
    std::string toString()
    {
        std::string toReturn = "";
        toReturn += from->key;
        toReturn += "\t";
        toReturn += to->key;
        toReturn += "\t";
        toReturn += std::to_string(weight);
        return toReturn;
    }
};

struct Comparator
{
    bool operator()(const Edge& edge1, const Edge& edge2);
};

class MST
{
private:
    // Kruskals
    int nrOfVerts = 0;
    std::vector<Vert*> verts;
    std::priority_queue<Edge, std::vector<Edge>, Comparator> pQueue;
    std::vector<Edge> doneMST;
    Vert* findAbsoluteParent(Vert* vert);
    void setUnion(Vert* fromParent, Vert* toParent);
    void kruskals();
    // file reading
    void fromFile(std::string filename);
    Vert* findVert(std::string value);
    int getWeight(std::string line);
    std::string getName(const int& startIndex, const std::string& line);
    int getWeight(std::string line, const int& startIndex);
    Vert* find(std::string value);

public:
    MST() = delete;
    MST(std::string fileName);
    virtual ~MST();
    std::string toString();
    // create file (fileName) containing MST
    void toFile(std::string fileName);
    void debugPrint();
};

#endif /* GRAPH_HPP */
