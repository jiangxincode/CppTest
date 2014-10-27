#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

#include <iostream>
#include <vector>
#include <memory>

/*
class StrBlog
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlog();
    StrBlog(std::initializer_list<std::string> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    // 添加和删除元素
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    // 元素访问
    std::string& front();
    std::string& back();
    friend class StrBlogPtr;
    StrBlogPtr begin()
    {
        return StrBlogPtr(*this);
    }
    StrBlogPtr end()
    {
        StrBlogPtr ret = StrBlogPtr(*this,data->size());
        return ret;
    }

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i,const std::string &msg) const;
};


class StrBlogPtr
{
public:
    StrBlogPtr():curr(0){}
    StrBlogPtr(StrBlog &a,size_t sz = 0):wptr(a.data),curr(sz){}
    std::string& defef() const;
    StrBlogPtr& incr();
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

StrBlog::StrBlog():data(make_shared<vector<string>>()){}
StrBlog::StrBlog(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
void StrBlog::check(size_type i,const string &msg) const
{
    if(i >= data->size())
        throw out_of_range(msg);
}

void StrBlog::pop_back()
{
    check(0,"pop_back on empty StrBlog");
    data->pop_back();
}

string& StrBlog::front()
{
    check(0,"front on empty StrBlog");
    return data->front();
}

string& StrBlog::back()
{
    check(0,"back on empty StrBolg");
    return data->back();
}


std::shared_ptr<std::vector<std::string>> StrBlogPtr::check(std::size_t i,const std::string&) const
{
    auto ret = wptr.lock();
    if(!ret)
    {
        throw std::runtime_error("unbound StrBlogPtr");
    }
    if(i >= ret->size())
    {
        throw std::out_of_range(msg);
    }
    return ret;
}
std::string& StrBlogPtr::deref() const
{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}
StrBlogPtr& StrBlogPtr::incr()
{
    check(curr,"increment past end of StrBlogPtr");
    ++curr;
    return *this;
}

void test_Ex_12_1()
{
    StrBlog b1;
    {
        StrBlog b2 = {"a","an","the"};
        b1 = b2;
        b2.push_back("about");
        cout << b2.size() << endl;
    }
    cout << b1.size() << endl;
}

int main1620()
{
    test_Ex_12_1();
    return 0;
}
*/

