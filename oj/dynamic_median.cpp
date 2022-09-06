#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX 300000

using namespace std;
typedef long long int ll ;

template<class E>
class MaxHeap
{
public:
	MaxHeap(int sz);
	MaxHeap(E arr[], int n);
	~MaxHeap() { delete[]heap; }
	bool Insert(const E& d);
	bool Remove(E& d);
	bool IsEmpty() const
	{
		return currentSize == 0;
	}
	bool IsFull() const
	{
		return currentSize == maxHeapSize;
	}
	void MakeEmpty() { currentSize = 0; };
	E getTop() { return heap[0]; };
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};


template<class E>
MaxHeap<E>::MaxHeap(int sz)
{
	maxHeapSize = sz;
	heap = new E[maxHeapSize];
	if (heap == NULL)
	{
		cerr << "¶Ñ´æ´¢·ÖÅäÊ§°Ü£¡" << endl; exit(1);
	}
	currentSize = 0;
}

template<class E>
MaxHeap<E>::MaxHeap(E arr[], int n)
{
	maxHeapSize = n;
	heap = new E[maxHeapSize];
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
void MaxHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j < m && heap[j] < heap[j + 1])j++;
		if (temp >= heap[j])
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
bool MaxHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)
	{
		cerr << "HeapFull!" << endl; return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<class E>
void MaxHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
	while (j > 0)
	{
		if (heap[i] >= temp)break;
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
bool MaxHeap<E>::Remove(E& x)
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

template<class E>
class MinHeap
{
public:
	MinHeap(int sz);
	MinHeap(E arr[], int n);
	~MinHeap() { delete[]heap; }
	bool Insert(const E& d);
	bool Remove(E& d);
	bool IsEmpty() const
	{
		return currentSize == 0;
	}
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

int main()
{
	MaxHeap<int> maxheap(MAX);
	MinHeap<int> minheap(MAX);
	int cnt = 0;

	int temp = 0;
	while (scanf_s("%d", &temp) != EOF)
	{
		if (maxheap.IsEmpty())
		{
			maxheap.Insert(temp);
		}
		else if (minheap.IsEmpty())
		{
			minheap.Insert(temp);
		}
		else
		{
			if (cnt % 2 == 1)
			{
				int top_maxheap = maxheap.getTop();
				if (temp >= top_maxheap)
					minheap.Insert(temp);
				else
				{
					maxheap.Remove(top_maxheap);
					maxheap.Insert(temp);
					minheap.Insert(top_maxheap);
				}
			}
			else
			{
				int top_minheap = minheap.getTop();
				if (temp <= top_minheap)
				{
					maxheap.Insert(temp);
				}
				else
				{
					minheap.Remove(top_minheap);
					minheap.Insert(temp);
					maxheap.Insert(top_minheap);
				}
			}
		}


		printf("%d ", maxheap.getTop());
		++cnt;
	}
}