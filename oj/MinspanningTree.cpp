#include<iostream>
using namespace std;

typedef long long ll;
#define M 400000

ll n;

class UFSets
{
public:
	UFSets(int sz);
	//~UFSets() { /*delete[]parent*/; };
	//UFSets& operator = (UFSets& R);
	void Union(int Root1, int Root2);
	int Find(int x);
	void WeightedUnion(int Root1, int Root2);
private:
	
	int* parent;
	int size;
};

UFSets::UFSets(int sz)
{
	size = sz;
	parent = new int[size];
	for (int i = 0; i < size; i++)
		parent[i] = -1;
}

int UFSets::Find(int x)
{
	if (parent[x] < 0)
		return x;
	else
	{
		parent[x] = Find(parent[x]);
		return parent[x];
	}
}

void UFSets::Union(int Root1, int Root2)
{
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;
}

void UFSets::WeightedUnion(int Root1, int Root2)
{
	if (Root1 != Root2)
	{
		int temp = parent[Root1] + parent[Root2];
		if (parent[Root2] < parent[Root1])
		{
			parent[Root1] = Root2;
			parent[Root2] = temp;
		}
		else
		{
			parent[Root2] = Root1;
			parent[Root1] = temp;
		}
	}
}

template<class E>
class MinHeap
{
public:
	MinHeap(int sz);
	MinHeap(E arr[], int n);
	
	bool Insert(const E& d);
	bool Remove(E& d);
	bool IsEmpty() const
	{
		return currentSize == 0;
	}
	//~MinHeap() { ; }
	bool IsFull() const
	{
		return currentSize == minHeapSize;
	}
	void MakeEmpty() { currentSize = 0; };
	E getTop() { return heap[0]; };
private:
	E* heap;
	int currentSize;
	int minHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};


template<class E>
MinHeap<E>::MinHeap(int sz)
{
	minHeapSize = sz;
	heap = new E[minHeapSize];
	if (heap == NULL)
	{
		cerr << "¶Ñ´æ´¢·ÖÅäÊ§°Ü£¡" << endl; exit(1);
	}
	currentSize = 0;
}

template<class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
	minHeapSize = n;
	heap = new E[minHeapSize];
	if (heap == NULL)
	{
		cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << endl; exit(-1);
	}
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template<class E>
void MinHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j < m && heap[j] > heap[j + 1])j++;
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template<class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == minHeapSize)
	{
		cerr << "HeapFull!" << endl; return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<class E>
void MinHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class E>
bool MinHeap<E>::Remove(E& x)
{
	if (!currentSize)
	{
		cout << "Heap empty!" << endl; return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

struct edge {
	int u, v;
	int val;
	edge() :u(0), v(0), val(0) {};
	edge(int a, int b, int value) :u(a), v(b), val(value) {};
	bool operator > (edge& e) const
	{
		if (val > e.val)
			return true;
		else return false;
	}
	bool operator <= (edge& e) const
	{
		if (val <= e.val)
			return true;
		else return false;
	}
};

edge e[M];
int m = 0;

void initgra()
{
	int u, v, val;
	while (cin >> u >> v >> val)
	{
		edge t = edge(u, v, val);
		e[m] = t;
		++m;
	}
}

ll MST(MinHeap<edge> fringe, UFSets vset)
{
	ll ecnt = 0;
	ll sum = 0;

	while (!fringe.IsEmpty() && ecnt < n - 1)
	{
		edge t = fringe.getTop();
		int u = t.u; int v = t.v;
		int root1 = vset.Find(u); int root2 = vset.Find(v);
		if (root1 != root2)
		{
			++ecnt;
			sum += t.val;
			vset.Union(root1, root2);
		}
		fringe.Remove(t);
	}
	cout << sum;
	return sum;
}

int main()
{
	cin >> n;
	initgra();

	MinHeap<edge> fringe(e,m);
	UFSets vset(n+1);

	ll pow = MST(fringe, vset);



	return 0;
}