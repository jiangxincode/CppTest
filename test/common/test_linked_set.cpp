#include <stdlib.h>
#include "gtest/gtest.h"
#include "../../src/common/LinkedSet.h"


TEST(LinkedSetTest, search_test)
{
    LinkedSet<int> myset;

    for(int i=1; i<=100; i++)
    {
        myset.addMember(i);
    }

    myset.display();
    SetNode<int> *first = myset.getFirst();
    SetNode<int> *temp;
    temp = myset.Search(first,first,0);
    cout << temp;
}

