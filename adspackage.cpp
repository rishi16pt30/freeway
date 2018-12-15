#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;


struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
struct AdjList
{
    struct AdjListNode* head;
};

int assign_color[10]={0};

class Graph
{
    private:
        int V;
        struct AdjList* array;
        bool adjmat[10][10];
    public:
        Graph(int V)
        {
                //bool adjmat[V][V];
                for(int i=0;i<V;i++)
                {
                    for(int j=0;j<V;j++)
                        adjmat[i][j]=0;
                }
                //Graph* graph = new Graph;
                this->V = V;
                this->array =  new AdjList[V];
                int i;
                for (i = 0; i < V; ++i)
                this->array[i].head = NULL;
        }
        AdjListNode* newAdjListNode(int);
        void addEdge(int,int);
        bool isSafe(int,int*,int);
        bool graphColoringUtil(int,int*,int);
        bool graphColoring(int);
        void printGraph();
        void printSolution(int*);
        int mincolor();
        void AssignColour(int*);
        bool isAdjacent(int,int);
};
 AdjListNode* Graph :: newAdjListNode(int dest)
{
    struct AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}


void Graph :: addEdge(int src, int dest)
{
    this->adjmat[src][dest]=1;
    this->adjmat[dest][src]=1;
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = this->array[src].head;
    this->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = this->array[dest].head;
    this->array[dest].head = newNode;
}


void Graph :: printGraph()
{
    int v;
    for (v = 0; v < this->V; ++v)
    {
        struct AdjListNode* p = this->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (p)
        {
            printf("-> %d", p->dest);
            p = p->next;
        }
        printf("\n");
    }

    cout<<"\n Adjacency matrix is"<<endl;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
            cout<<adjmat[i][j]<<"   ";
        cout<<endl;
    }
    cout<<endl;
}

bool Graph::isSafe(int ver,int color[],int c)
{
    for(int i=0;i<this->V;i++)
        if(this->adjmat[ver][i] && c==color[i])
            return false;
    return true;
}

bool Graph :: graphColoringUtil(int m, int color[], int ver)
{
    if(ver==this->V)
        return true;
    for(int c=1;c<=m;c++)
    {
        if(this->isSafe(ver,color,c))
        {
            color[ver]=c;
            if (this->graphColoringUtil(m, color, ver+1) == true)
             return true;

            color[ver]=0;
        }
    }
    return false;
}



bool Graph :: graphColoring(int m)
{
    int *color=new int[this->V];

    for(int i=0;i<this->V;i++)
        color[i]=0;

    if (this->graphColoringUtil(m, color, 0) == false)
    {
      //printf("Solution does not exist");
      return false;
    }

    printSolution(color);
    this->AssignColour(color);
    return true;
}

void Graph::printSolution(int color[])
{
    printf("Solution Exists:"
            " Following are the assigned runways \n");
    for (int i = 0; i < V; i++)
      printf(" %d ", color[i]);
    printf("\n");
}

void Graph::AssignColour(int color[])
{
    for(int i=0;i<V;i++)
        assign_color[i]=color[i];
}

int Graph::mincolor()
{
    for(int i=1;i<=V;i++)
    {
        if(this->graphColoring(i)==1)
            return i;
    }
}

bool Graph::isAdjacent(int v1,int v2)
{
    v1=v1-1;
    v2=v2-1;
    if(adjmat[v1][v2]==1)
        return true;
    else
        return false;
}



/*int main()
{
    int V = 5;
    Graph s(5);
    s.addEdge(0, 1);
    s.addEdge(0, 4);
    s.addEdge(1, 2);
    s.addEdge(1, 3);
    s.addEdge(1, 4);
    s.addEdge(2, 3);
    s.addEdge(3, 4);
    s.printGraph();
    cout<<endl;
    int k=s.mincolor();
    cout<<endl;
    cout<<"min colour"<<k;
    s.graphColoring(k);
    for(int i=0;i<5;i++)
        cout<<assign_color[i]<<endl;
    return 0;
}*/
