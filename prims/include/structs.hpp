#ifndef STRUCTS
#define STRUCTS

struct verticeEdge;
struct vertice;
struct edge;

struct verticeEdge
{
    edge *vertice_edge;
    verticeEdge *next;
    verticeEdge()
    {
        vertice_edge = nullptr;
        next = nullptr;
    }
};
struct vertice
{
    char key;
    verticeEdge *edgeStart;
    bool used;
    vertice() { edgeStart = nullptr; used = false; }
};
struct edge
{
    vertice *node1;
    vertice *node2;
    int weight;
    bool used;
    edge()
    {
        weight = -1;
        used = false;
    }
};

#endif
