#ifndef GRAPH_HPP
#define GRAPH_HPP

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
};

class MST
{
private:
public:
    MST();
    virtual ~MST();
};

#endif /* GRAPH_HPP */
