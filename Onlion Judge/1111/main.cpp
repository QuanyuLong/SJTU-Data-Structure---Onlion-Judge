#include <iostream>
#include <cstring>
using namespace std;

class binaryTree {
private:
    char * dataTree;
    char * preOrderStr;
    char * midOrderStr;
    int nodeNum;

public:
    binaryTree(){dataTree = new char [1001] {'\0'}; preOrderStr = new char [27]; midOrderStr = new char [27];nodeNum = 0;}
    void getNode();
    void creat(char * preOrderNodes, char * midOrderNodes, int n, int root_index);
    void printTree();
};

void binaryTree::getNode()
{
    cin>>preOrderStr >> midOrderStr;
    nodeNum = strlen(preOrderStr);
    //cout<<preOrderStr<<'\n'<<midOrderStr<<endl;
}

void binaryTree::creat(char * preOrder, char * midOrder, int n, int root_index)
{
    if (n <= 0) return;
    //cout<<*preOrder<<endl;
    dataTree[root_index] = *preOrder;
    int i = 0;
    while (true) {if (midOrder[i] == *preOrder) break; ++i;}
    creat(preOrder + 1, midOrder, i, 2 * root_index);
    creat(preOrder + i + 1, midOrder + i + 1, n - i - 1, 2 * root_index + 1);
}

void binaryTree::printTree()
{
    creat(preOrderStr, midOrderStr, nodeNum, 1);
    int i = 1, cnt = 0;
    while(true){
        if(dataTree[i] != '\0') {cout<<dataTree[i]; ++ cnt;}
        else cout<<"NULL ";
        cout<<' ';
        ++i;
        if (cnt == nodeNum) break;
    }
}

int main()
{
    binaryTree tree;
    tree.getNode();
    tree.printTree();
}
