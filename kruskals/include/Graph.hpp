#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iterator>
#include <string>
struct Edge
{
    char vert1;
    char vert2;
    int weight;
    Edge(char vert1, char vert2, int weight)
    {
        this->vert1 = vert1;
        this->vert2 = vert2;
        this->weight = weight;
    }
    friend bool operator<(const Edge& l, const Edge& r)
    {
        return l.weight < r.weight;
    }
};

class MST
{
private:
public:
    MST();
    virtual ~MST();
    // create file (fileName) containing MST
    void toFile(std::string fileName);
};

#endif /* GRAPH_HPP */
