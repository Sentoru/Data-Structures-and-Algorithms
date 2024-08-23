#include <iostream>
#define M 7
using namespace std;

struct Item
{
    int value;
    int next;
};

struct hashTable
{
    Item h[M];
    int r;
};

void init(hashTable &t)
{
    for (int i = 0; i < M; i++)
    {
        t.h[i].value = -1;
        t.h[i].next = -1;
    }
    t.r = M - 1;
}

int hashFunc(int x)
{
    return x % M;
}

void insertHashItem(hashTable &t, int x)
{
    if (t.r >= 0)
    {
        int idx = hashFunc(x);
        if (t.h[idx].value == -1)
            t.h[idx].value = x;
        else
        {
            t.h[t.r].value = x;
            // Update next
            while (t.h[idx].next != -1)
                idx = t.h[idx].next;

            t.h[idx].next = t.r;
        }
        while (t.r >= 0 && t.h[t.r].value >= 0)
            t.r--;
    }
}

int search(hashTable t, int x)
{
    int idx = hashFunc(x);

    do
    {
        if (t.h[idx].value == x)
            return idx;
        idx = t.h[idx].next;
    } while (idx >= 0);
    
    return -1;
}

void display(hashTable t)
{
    for (int i = 0; i < M; i++)
        if (t.h[i].value >= 0)
            cout << i << ": " << t.h[i].value << " -> " << t.h[i].next << endl;
}

int main()
{
    hashTable t;
    init(t);

    insertHashItem(t, 4);
    insertHashItem(t, 54);
    insertHashItem(t, 12);
    insertHashItem(t, 876);
    insertHashItem(t, 13);
    insertHashItem(t, 5);
    insertHashItem(t, 100);
    
    display(t);
    return 0;
}