/**
 * 二叉树遍历
 * 描述:  二叉树的前序、中序、后序遍历的定义：
 * 前序遍历：对任一子树，先访问跟，然后遍历其左子树，最后遍历其右子树；
 * 中序遍历：对任一子树，先遍历其左子树，然后访问根，最后遍历其右子树；
 * 后序遍历：对任一子树，先遍历其左子树，然后遍历其右子树，最后访问根。
 * 给定一棵二叉树的前序遍历和中序遍历，求其后序遍历
 * （提示：给定前序遍历与中序遍历能够唯一确定后序遍历）。
 * 输入:
 * 两个字符串，其长度n均小于等于26。
 * 第一行为前序遍历，第二行为中序遍历。
 * 二叉树中的结点名称以大写字母表示：A，B，C....最多26个结点。
 * 输出:
 * 输入样例可能有多组，对于每组测试样例，
 * 输出一行，为后序遍历的字符串。
 * 样例输入:
 * ABC
 * BAC
 * FDXEAG
 * XDEFAG
 * 样例输出:
 * BCA
 * XEDGAF
 *
 */
#include <iostream>
#include <string>

using namespace std;

struct node
{

    char v;
    node *left;
    node *right;
    node(char c):v(c),left(NULL),right(NULL){}
};

/**根据先序遍历和中序遍历构造二叉树 */
void static genTree(node *t,string a,string b)
{
    string la,lb,ra,rb;

    if(a.length() > 0)
    {
        int mid = b.find(a[0]);

        lb = b.substr(0,mid);
        rb = b.substr(mid+1,b.length());
        la = a.substr(1,lb.length());
        ra = a.substr(lb.length()+1,a.length()-lb.length()-1);

        if(la.length() == 0)
        {
            t->left = NULL;
        }
        else
        {
            t->left = new node(la[0]);
            genTree(t->left,la,lb);
        }

        if(ra.length() == 0)
        {
            t->right = NULL;
        }
        else
        {
           t->right = new node(ra[0]);
            genTree(t->right,ra,rb);
        }
    }
}

/**后序遍历二叉树 */
void static postOrder(node *t)
{
    if(t != NULL)
    {
        postOrder(t->left);
        postOrder(t->right);
        cout << t->v;
    }
}

int main()
{
    string A,B;
    while(cin >> A >> B)
    {
        node *root = new node(A[0]);
        genTree(root,A,B);
        postOrder(root);
        cout << endl;
    }
    return 0;
}
