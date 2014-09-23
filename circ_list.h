using namespace std;
template <class T>
struct CircLinkNode
{
	T data;
	CircLinkNode<T> *link;
	CircLinkNode(CircLinkNode<T> *next=NULL):link(next){}
	CircLinkNode(const T& item,CircLinkNode<T> *next=NULL):data(item),link(next){}
};

template<class T>
class CircList
{
	public:
		CircList(){first = new CircLinkNode<T>(first);}
		CircList(const T& x){first = new CircLinkNode<T>(x,first);}
		CircLinkNode<T> *getHead()const{return first;};
		void inputRear(T i);
		void output();
	private:
		CircLinkNode<T> *first;
};

template <class T>
void CircList<T>::inputRear(T i)
{
	CircLinkNode<T> *newNode,*last;
	last = first;
	newNode = new CircLinkNode<T>(i);
	if(newNode == NULL)
	{
		cerr << "存储分配错误" <<endl;
		exit(1);
	}
	last->link = newNode;
	last= newNode;
	last->link = first;
};

template<class T>
void CircList<T>::output() //单链表的输出函数，将单链表的所用数据按逻辑顺序输出到屏幕上
{
	CircLinkNode<T> *current = first->link;
	while(current != first)
	{
		cout<<current->data<<" ";
		current = current->link;
	}
	cout<<endl;
};

