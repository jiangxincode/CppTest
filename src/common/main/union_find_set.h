#define DEFAULT_SIZE 10

class union_find_set
{
private:
    int *parent;
    int size;

public:
    union_find_set(int sz = DEFAULT_SIZE);
    ~union_find_set()
    {
        delete []parent;
    }
    void Union(int Root1, int Root2);
    void WeightedUnion(int Root1, int Root2);
    void SequenceUnion(int Root1, int Root2);
    int Find(int x);
    int GetParent(int x)
    {
        return parent[x];
    }
};
