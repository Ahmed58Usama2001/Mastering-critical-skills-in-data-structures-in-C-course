#include<vector>
#include<iostream>
#include<cassert>
#include<queue>
using namespace std;


class MinHeap {
private:
	int* array{};
	int size{};
	int capacity{ 1000 };

	int left(int node)
	{
		int p = 2 * node + 1;
		return	p >= size ? -1 : p;
	}

	int right(int node)
	{
		int p = 2 * node + 2;
		return	p >= size ? -1 : p;
	}

	int parent(int node)
	{
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos)
	{
		int parent_pos = parent(child_pos);
		if (child_pos == 0 || array[child_pos] >= array[parent_pos])
			return;

		swap(array[child_pos], array[parent_pos]);
		heapify_up(parent_pos);
	}


	void heapify_down(int parent_pos)
	{
		int child_pos = left(parent_pos);
		int right_pos = right(parent_pos);

		if (child_pos == -1)
			return;

		if (right_pos != -1 && array[right_pos] < array[child_pos])
			child_pos = right_pos;

		if (array[parent_pos] > array[child_pos])
		{
			swap(array[child_pos], array[parent_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify()
	{
		for (int i = size/2-1; i >= 0; i--)
		{
			heapify_down(i);
		}
	}


	bool is_heap(int parent_pos)
	{
		if (parent_pos == -1)
			return true;

		int left_pos = left(parent_pos);
		int right_pos = right(parent_pos);

		if (left_pos != -1 && array[parent_pos] > array[left_pos])
			return false;

		if (right_pos != -1 && array[parent_pos] > array[right_pos])
			return false;

		return is_heap(left_pos) && is_heap(right_pos);
	}

public:
	MinHeap() {
		array = new int[capacity]{};
		size = 0;
	}

	


	MinHeap(const vector<int>v)
	{
		assert(v.size() <= capacity);
		array = new int[capacity];
		size = v.size();

		for (int i = 0; i < size; i++)
			array[i] = v[i];

		heapify();
	}

	
	~MinHeap()
	{
		delete[] array;
		array = nullptr;
	}

	bool isempty()
	{
		return size == 0;
	}

	void push(int key)
	{
		assert(size + 1 <= capacity);
		array[size++] = key;
		heapify_up(size - 1);
	}

	int top()
	{
		assert(!isempty());
		return array[0];
	}


	void pop()
	{
		assert(!isempty());
		array[0] = array[--size];
		heapify_down(0);
	}


	bool is_heap_array(int* p, int n)
	{
		int* old_array = array;
		int old_size = size;

		array = p;
		size = n;

		bool result = is_heap(0);

		array = old_array;
		size = old_size;;

		return result;
	}

	void heap_sort(int* p, int n)
	{
		if (n <= 1)
			return;

		int* old_array = array;
		int old_size = size;

		array = p;
		size = n;

		heapify();

		while (size--)
		{
			swap(array[0], array[size]);
			heapify_down(0);
		}

		for (int i = 0; i < n / 2; i++)
			swap(array[i], array[n - 1 - i]);
		
		

		array = old_array;
		size = old_size;;
	}

	void print_less_than(int val, int parent_pos = 0)
	{
		if (parent_pos == -1 || array[parent_pos] >= val)
			return;

		cout << array[parent_pos] << " ";

		print_less_than(val, left(parent_pos));
		print_less_than(val, right(parent_pos));
	}

};


class MaxHeap {
private:
	int* array{};
	int size{};
	int capacity{ 1000 };

	int left(int node)
	{
		int p = 2 * node + 1;
		return	p >= size ? -1 : p;
	}

	int right(int node)
	{
		int p = 2 * node + 2;
		return	p >= size ? -1 : p;
	}

	int parent(int node)
	{
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos)
	{
		int parent_pos = parent(child_pos);
		if (child_pos == 0 || array[child_pos] <= array[parent_pos])
			return;

		swap(array[child_pos], array[parent_pos]);
		heapify_up(parent_pos);
	}


	void heapify_down(int parent_pos)
	{
		int child_pos = left(parent_pos);
		int right_pos = right(parent_pos);

		if (child_pos == -1)
			return;

		if (right_pos != -1 && array[right_pos] > array[child_pos])
			child_pos = right_pos;

		if (array[parent_pos] < array[child_pos])
		{
			swap(array[child_pos], array[parent_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify()
	{
		for (int i = size / 2 - 1; i >= 0; i--)
		{
			heapify_down(i);
		}
	}

public:
	MaxHeap() {
		array = new int[capacity] {};
		size = 0;
	}




	MaxHeap(const vector<int>v)
	{
		assert(v.size() <= capacity);
		array = new int[capacity];
		size = v.size();

		for (int i = 0; i < size; i++)
			array[i] = v[i];

		heapify();
	}


	~MaxHeap()
	{
		delete[] array;
		array = nullptr;
	}

	bool isempty()
	{
		return size == 0;
	}

	void push(int key)
	{
		assert(size + 1 <= capacity);
		array[size++] = key;
		heapify_up(size - 1);
	}

	int top()
	{
		assert(!isempty());
		return array[0];
	}


	void pop()
	{
		assert(!isempty());
		array[0] = array[--size];
		heapify_down(0);
	}

	int sz()
	{
		return size;
	}

};

class KthNumberProcessor {
private:
	int k;
	MaxHeap q;

public:
	KthNumberProcessor(int k) :k(k) {
	}

	int next(int new_num)
	{
		if (q.sz() < 4)
			q.push(new_num);
		else if (new_num < q.top())
		{
			q.pop();
			q.push(new_num);
		}

		return q.top();
	}

};

void creat_heap_nlogn() {
	MinHeap heap;

	vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };

	for (int i = 0; i < (int)v.size(); ++i)
		heap.push(v[i]);

	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}



void creat_heap_n() {
	vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap heap(v);

	
	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}



int main()
{
	vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap heap(v);

	heap.print_less_than(10);

	cout << " \nBye\n";

	return 0;
}