#include <iostream>

using namespace std;

class DisjointSet{
private:
	int size;
	int *parent;

public:
	DisjointSet(int n)
	{
		size = n;
		parent = new int[size];
		for (int i = 0; i < size; ++i)
			parent[i] = -1;
	}
	~DisjointSet() { delete[] parent; }
	void Union(int root1, int root2)
	{
		if (root1 == root2)
			return;
		if (parent[root1] > parent[root2]){
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else{
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
	int Find(int x)
	{
		if (parent[x] < 0)
			return x;
		return parent[x] = Find(parent[x]);
	}
};

struct edge
{
	int start, end;
	int weight;

	edge(int s = 0, int e = 0, int w = 0) :start(s), end(e), weight(w) {}
};

struct ver
{
	int val;
	edge * head;
};

int partition(edge *edgeList, int left, int right)
{
	int i = left, j = right;
	int tmp = edgeList[left].weight;
	edge t = edgeList[left];
	while (i < j)
	{
		while (i < j && edgeList[j].weight > tmp)
			j--;
		if (i < j){
			edgeList[i] = edgeList[j];
			i++;
		}
		while (i < j && edgeList[i].weight < tmp)
			i++;
		if (i < j){
			edgeList[j] = edgeList[i];
			j--;
		}
	}
	edgeList[i] = t;
	return i;
}

void quick_sort(edge *edgeList, int left, int right)
{
	if (left > right)
		return;
	int j = partition(edgeList, left, right);
	quick_sort(edgeList, left, j - 1);
	quick_sort(edgeList, j + 1, right);
}

int main()
{
	int n, m, x, y, z, cnt = 0, result = 0, e = 1;
	cin>>n>>m;
	edge *edgeList = new edge[m + 1];
	DisjointSet ds(n + 1);

	for (int i = 1; i < m + 1; ++i){
		cin>>x>>y>>z;
		edgeList[i].start = x;
		edgeList[i].end = y;
		edgeList[i].weight = z;
	}
	quick_sort(edgeList, 1, m);
	while (cnt < n - 1){
		int u, v;
		u = ds.Find(edgeList[e].start);
		v = ds.Find(edgeList[e].end);
		if (u != v){
			ds.Union(u, v);
			result += edgeList[e].weight;
			cnt++;
		}
		++e;
	}

	cout << result;
}
