#include <iostream>
#include <cstdlib>
#include "heap.h"

using namespace std;

static const int DEFAULT_SIZE = 10;

heap::heap(int size, bool (*comp)(int,int))
{
    p_fun = comp;
    max_size = (size>DEFAULT_SIZE)?size:DEFAULT_SIZE;
    heap_p = new int[max_size];

    if(heap_p == NULL)
    {
        cerr << "error:memory allocate";
        exit(1);
    }

    current_size = 0;
}

heap::heap(int arr[],int n, bool (*comp)(int,int))
{
    p_fun = comp;
    max_size = (n>DEFAULT_SIZE)?n:DEFAULT_SIZE;
    heap_p = new int[max_size];

    if(heap_p == NULL)
    {
        cerr << "error:memory allocate";
        exit(1);
    }

    current_size = n;

    for(int i=0; i<current_size; i++)
    {
        heap_p[i] = arr[i];
    }

    int current_pos = (current_size-2)/2; //important

    while(current_pos >= 0)
    {
        shift_down(current_pos,current_size-1);
        current_pos --;
    }
}

void heap::shift_down(int begin, int end)
{
    int i = begin;
    int j = 2*i+1;
    int temp = heap_p[i];

    while(j <= end)
    {
        if((j < end) && (p_fun(heap_p[j+1],heap_p[j]))) //找到左右子树的较小值，warning:j<m
        {
            j ++;
        }

        if(p_fun(heap_p[j],temp))
        {
            heap_p[i] = heap_p[j];
            i = j;
            j = 2*j+1;
        }
        else
        {
            break;
        }
    }

    heap_p[i] = temp;
}

void heap::shift_up(int begin)
{
    int j = begin;
    int i = (begin-1)/2;
    int temp = heap_p[j];

    while(j > 0)
    {
        if(p_fun(temp,heap_p[i]))
        {
            heap_p[j] = heap_p[i];
            j = i;
            i = (j-1)/2;
        }
        else
        {
            break;
        }
    }

    heap_p[j] = temp;
}

bool heap::push(int elem)
{
    if(max_size == current_size) //如果堆已满，则从新开辟对空间
    {
        max_size = 2*max_size;
        int *temp = new int[max_size];

        if(temp == NULL)
        {
            cerr << "error:allocate";
            exit(1);
        }

        for(int i=0; i<current_size; i++)
        {
            temp[i] = heap_p[i];
        }

        delete []heap_p;
        heap_p = temp;
    }

    heap_p[current_size] = elem;
    shift_up(current_size); //注意相对顺序
    current_size ++;
    return true;
}

int heap::top()
{
    if(!current_size)
    {
        cerr << "error:empty" << endl;
        return -1;
    }
    else
    {
        return heap_p[0];
    }
}
bool heap::pop()
{
    if(!current_size)
    {
        cerr << "error:empty" << endl;
        return false;
    }

    heap_p[0] = heap_p[current_size-1];
    current_size --;
    shift_down(0,current_size-1);
    return true;
}

void heap::sort()
{
    for(int i=current_size-1; i>=0; i--)
    {
        int temp = heap_p[i];
        heap_p[i] = heap_p[0];
        heap_p[0] = temp;
        shift_down(0,i-1);
    }
}

bool heap::is_empty()
{
    if(current_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void heap::print_heap()
{
    for(int i=0; i<current_size; i++)
    {
        cout << heap_p[i] << ",";
    }
}

int heap::at(int index)
{
    return heap_p[index];
}

int heap::size()
{
    return current_size;
}
