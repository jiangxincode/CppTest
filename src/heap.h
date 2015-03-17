class heap
{
private:
    int current_size;
    int max_size;
    int *heap_p;
    bool (*p_fun)(int, int); //接受一个二元谓词函数，来决定是建立最小堆还是最大堆

    void shift_down(int begin,int end);
    void shift_up(int begin);

public:
    heap(int size, bool (*comp)(int,int));
    heap(int arr[], int n, bool (*comp)(int,int));
    ~heap()
    {
        delete []heap_p;
    }

    bool push(int elem);
    int top();
    bool pop();
    void sort();
    bool is_empty();
    void print_heap();
    int at(int index);
    int size();
};
