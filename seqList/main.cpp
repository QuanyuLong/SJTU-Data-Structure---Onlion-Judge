#include <iostream>
#include "seqList.h"
using namespace std;

int main()
{
/*
    seqList<char> chlist(21);
    char ctemp;
	int i, n;
    cout << "number of the elements:"<< endl;
    cin >> n;
    cin.get(ctemp);	//将 Enter 抛弃。
	cout << "input the elements:\n"<< endl;
	for ( i=0; i<=n-1; i++) { cin.get ( ctemp);  chlist.insert( i, ctemp); }

	ctemp = chlist.visit(0); //获得首结点.
	chlist.remove(0);
	chlist.insert(chlist.length( )/2, ctemp);
	cout << "output the elements:\n" << endl;
	for (i=0;i<chlist.length( );i++) cout.put(chlist.visit(i));
	cout << '\n';
	return 0;
*/
/*
    seqList<int> intlist(20);
    for (i = 0; i < 10; ++i) intlist.insert(i,i);
    intlist.traverse();
    cout<<intlist.length()<<endl;
    cout<<intlist.search(2)<<endl;
    cout<<intlist.visit(4)<<endl;
    intlist.insert(2,10);
    intlist.traverse();
    intlist.remove(2);
    intlist.traverse();
*/
    seqList<int> intlist1(20);
    for (int i = 0; i < 10; ++i) intlist1.insert(i,i);
    seqList<int> intlist2(intlist1);
    cout<<intlist2.length()<<endl;
    intlist1.remove(1);
    intlist2.traverse();
}
