#include<iostream>
#include<limits>
using namespace std;

void swap(int *x,int *y);

class MinHeap
{
    private:
        int *heap;
        int total;
        int heapsize;

    public:
        MinHeap(int cap)
        {
            this->total=cap;
            this->heapsize=0;
            heap=new int[cap];
        }

        int getParent(int i)
        {
            return (i-1)/2;
        }

        int getRight(int i)
        {
            return 2*i+1;
        }

        int getLeft(int i)
        {
            return 2*i+2;
        }

        int getMin()
        {
            return heap[0];
        }
        int ExtractMin();
        void DecreaseKey(int,int);
        void MinHeapify(int);
        void DeleteKey(int);
        void InsertKey(int);
        void print();
};

void MinHeap :: InsertKey(int k)
{
    if(heapsize==total)
    {
        cout<<"\nOverflow......";
        return;
    }
    int i=this->heapsize;

    heapsize++;
    heap[i]=k;
    while( i!=0 && heap[getParent(i)]>heap[i])
    {
        swap(&heap[i] , &heap[getParent(i)]);
        i=getParent(i);
    }

}

void MinHeap :: DecreaseKey(int i,int newval)
{
    heap[i]=newval;
    while(i!=0 && heap[getParent(i)] > heap[i] )
    {
        swap(&heap[i],&heap[getParent(i)]);
        i=getParent(i);
    }
}

int MinHeap :: ExtractMin()
{
    if(heapsize<=0)
        return -1;
    if(heapsize == 1)
    {
        heapsize--;
        return heap[0];
    }
    int root=heap[0];
    heap[0]=heap[heapsize-1];
    heapsize--;
    MinHeapify(0);

    return root;
}

void MinHeap :: DeleteKey(int i)
{
    DecreaseKey(i,-1);
    ExtractMin();
}



void MinHeap :: MinHeapify(int i)
{
    int left=getLeft(i);
    int right=getRight(i);
    int small=i;
    if(left<heapsize && heap[left]<heap[i])
        small=left;
    if(right<heapsize && heap[right]<heap[small])
        small=right;
    if(small != i)
    {
        swap(&heap[i],&heap[small]);
        this->MinHeapify(small);
    }
}

void MinHeap :: print()
{
    for(int i=0;i<heapsize;i++)
        cout<<heap[i]<<"   ";
}

void swap(int *x,int *y)
{
    int temp = *x;
    *x=*y;
    *y=temp;
}
/*int main()
{
    MinHeap m(10);
    m.InsertKey(5);
    m.InsertKey(7);
    m.InsertKey(1);
    m.InsertKey(6);
    m.print();
   int k= m.ExtractMin();
   cout<<endl<<k;
   cout<<endl;
   m.print();
}*/



