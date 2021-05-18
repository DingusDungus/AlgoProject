#ifndef STRUCTS
#define STRUCTS

#include <string>

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
    std::string key;
    verticeEdge *edgeStart;
    bool used;
    vertice() { edgeStart = nullptr; used = false; key = ' '; }
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
        node1 = nullptr;
        node2 = nullptr;
    }
};

#endif
