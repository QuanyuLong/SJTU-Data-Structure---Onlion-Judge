#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class complete_binary_tree{
private:
    char * dataTree;
    int nodeNum;
    void preOrder(int root){
        cout<<dataTree[root];
        if(2 * root <= nodeNum) preOrder(2 * root);
        if(2 * root + 1 <= nodeNum) preOrder(2 * root + 1);
    }
    void midOrder(int root){
        if(2 * root <= nodeNum) midOrder(2 * root);
        cout<<dataTree[root];
        if(2 * root + 1 <= nodeNum) midOrder(2 * root + 1);
    }
    void postOrder(int root){
        if(2 * root <= nodeNum) postOrder(2 * root);
        if(2 * root + 1 <= nodeNum) postOrder(2 * root + 1);
        cout<<dataTree[root];
    }
    void preOrderTo(int root,int n, int * i, char * data, char * tree){
        tree[root] = data[*i];
        ++*i;
        if(2 * root <= n) preOrderTo(2 * root, n, i, data, tree);
        if(2 * root + 1 <= n) preOrderTo(2 * root + 1, n, i, data, tree);
    }
    void midOrderTo(int root, int n, int * i, char * data, char * tree){
        if(2 * root <= n) midOrderTo(2 * root, n, i, data, tree);
        tree[root] = data[*i];
        ++*i;
        if(2 * root + 1 <= n) midOrderTo(2 * root + 1, n, i, data, tree);
    }
    void postOrderTo(int root, int n, int * i, char * data, char * tree){
        if(2 * root <= n) postOrderTo(2 * root, n, i, data, tree);
        if(2 * root + 1 <= n) postOrderTo(2 * root + 1, n, i, data, tree);
        tree[root] = data[*i];
        ++*i;
    }
public:
    complete_binary_tree(int n, char * data){
        nodeNum = n;
        dataTree = new char [strlen(data) + 2];
        strcpy(dataTree+1, data);
    }
    complete_binary_tree(int n, char * data, int type){//0:in, 1:pre, 2:post
        nodeNum = n;
        dataTree = new char [strlen(data) + 2];
        int * i  = new int (0);
        if(type == 0){midOrderTo(1, n, i, data, dataTree);}
        else if(type == 1){preOrderTo(1, n, i, data, dataTree);}
        else if(type == 2){postOrderTo(1, n, i, data, dataTree);}
        delete i;
    }
    void preOrder(){preOrder(1);}
    void midOrder(){midOrder(1);}
    void postOrder(){postOrder(1);}
    void print() {
        for (int i = 1; i <= nodeNum; ++i) cout<<dataTree[i];
    }
};


int main()
{
    int num_of_instruction, num_of_node;
    char orderType [10], codeType[7], nodeString[1000000];

    cin>>num_of_instruction;
    for(int i = 0;i < num_of_instruction; ++i){
        cin>>num_of_node>>orderType>>codeType>>nodeString;
        //cout<<num_of_node<<' '<<orderType<<' '<<codeType<<' '<<nodeString<<endl;
        if(strcmp(codeType, "ENCODE")==0){
            complete_binary_tree CBTree(num_of_node, nodeString);
            if(strcmp(orderType, "INORDER")==0) {CBTree.midOrder();cout<<endl; continue;}
            if(strcmp(orderType, "PREORDER")==0) {CBTree.preOrder();cout<<endl; continue;}
            if(strcmp(orderType, "POSTORDER")==0) {CBTree.postOrder();cout<<endl; continue;}
        }
        else{
            if(strcmp(orderType, "INORDER")==0) {complete_binary_tree CBTree(num_of_node, nodeString, 0);CBTree.print();cout<<endl; continue;}
            if(strcmp(orderType, "PREORDER")==0) {complete_binary_tree CBTree(num_of_node, nodeString, 1);CBTree.print();cout<<endl; continue;}
            if(strcmp(orderType, "POSTORDER")==0) {complete_binary_tree CBTree(num_of_node, nodeString, 2);CBTree.print();cout<<endl; continue;}
        }
    }

    cin.get();
    cin.get();

    /*
    char str [100] = "VENSAYONNLAOHJ";
    complete_binary_tree tree(14, str, 2);
    tree.print();
    */
}
