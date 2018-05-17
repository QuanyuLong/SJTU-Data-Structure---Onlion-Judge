#include <iostream>
#include "binaryTree.h"
using namespace std;

int main()
{
    binaryTree<char> tree, tree1('M'), tree2;
    tree.createTree('@');
    cout << "�߶�Ϊ��" << tree.height() << endl;
    cout << "��ģΪ��" << tree.size() << endl;
    /*
    //tree.preOrder();
    tree.preOrder_nonrecursion_stack();
    cout<<endl;
    //tree.midOrder();
    //cout<<endl;
    tree.midOrder_nonrecursion_stack();
    cout<<endl;
    tree.postOrder();
    cout<<endl;
    tree.postOrder_nonrecursion_stack();
    cout<<endl;
    */
    tree.preOrder_Morris();
    cout<<endl;
    tree.midOrder_Morris();
    cout<<endl;
    tree.postOrder_Morris();
    cout<<endl;
    tree2.makeTree('Y', tree, tree1);
    cout << endl;
    cout << "�߶�Ϊ��" << tree2.height() << endl;
    cout << "��ģΪ��" << tree2.size() << endl;
    tree2.preOrder();
    tree2.midOrder();
    tree2.postOrder();
    return 0;
}
