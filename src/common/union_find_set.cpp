#include "union_find_set.h"

union_find_set::union_find_set(int sz)
{
    size = sz;
    parent = new int[size];

    for(int i=0; i<size; i++)
    {
        parent[i] = -1;
    }
};

int union_find_set::Find(int x)
{
    while(parent[x] >= 0)
    {
        x = parent[x];
    }

    return x;
};

void union_find_set::Union(int Root1, int Root2)
{
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
};

void union_find_set::WeightedUnion(int Root1, int Root2)
{
    if(parent[Root1] > parent[Root2])
    {
        parent[Root1] += parent[Root2];
        parent[Root2] = Root1;
    }
    else
    {
        parent[Root2] += parent[Root1];
        parent[Root1] = Root2;
    }
}

void union_find_set::SequenceUnion(int Root1, int Root2)
{
    if(Root1 < Root2)
    {
        parent[Root1] += parent[Root2];
        parent[Root2] = Root1;
    }
    else
    {
        parent[Root2] += parent[Root1];
        parent[Root1] = Root2;
    }
}
