#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


template <class typeOfEdge>
class graph{
public:
    virtual bool insert(int u, int v, typeOfEdge w) = 0;
    virtual bool remove(int u, int v) = 0;
    virtual bool exist(int u, int v) const = 0;
    virtual int numOfVers() const {return Vers;}
    virtual int numOfEdges() const {return Edges;}

protected:
    int Vers, Edges;
};


#endif // GRAPH_H_INCLUDED
