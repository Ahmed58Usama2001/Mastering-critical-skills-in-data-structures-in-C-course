#include<iostream>
#include<vector>
#include<queue>
#include<assert.h>
using namespace std;

class Vector {
private:
	int* arr = nullptr;
	int size{ 0 };
	int capacity{};
	void expand_capacity() {
		capacity = size * 2;
		int* arr2 = new int[capacity] {};

		for (int i = 0; i < size; i++)
			arr2[i] = arr[i];

		swap(arr, arr2);

		delete[] arr2;
	}

public:
	Vector(int size) :size(size) {
		if (size < 0)
			size = 1;

		capacity = size * 2;

		arr = new int[capacity] {};
	}

	~Vector()
	{
		delete[] arr;
		arr = nullptr;
	}

	int get(int idx)
	{
		assert(idx >= 0 && idx < size);
		return arr[idx];
	}

	void set(int idx, int val)
	{
		assert(idx >= 0 && idx < size);
		arr[idx] = val;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	int search(int val)
	{
		for (int i = 0; i < size; i++)
			if (arr[i] == val)
				return i;

		return -1;
	}

	int get_front()
	{
		return arr[0];
	}

	int get_back()
	{
		return arr[size - 1];
	}



	void push_back(int val)
	{
		if (size == capacity)
			expand_capacity();

		arr[size++] = val;
	}

	int get_size()
	{
		return size;
	}

	void insert(int idx, int val)
	{
		if (size == capacity)
			expand_capacity();

		for (int i = size - 1; i >= idx; i--)
			arr[i + 1] = arr[i];

		arr[idx] = val;
		size++;
	}

	void right_rotate()
	{
		int temp = arr[size - 1];
		for (int i = size - 1; i > 0; i--)
			arr[i] = arr[i - 1];

		arr[0] = temp;
	}

	void left_rotate()
	{
		int temp = arr[0];

		for (int i = 0; i <= size - 2; i++)
			arr[i] = arr[i + 1];

		arr[size - 1] = temp;
	}

	void right_rotate(int times)
	{
		times %= size;
		while (times--)
			right_rotate();
	}

	int pop(int idx)
	{
		assert(idx >= 0 && idx < size);
		int res = arr[idx];

		for (int i = idx; i < size - 1; i++)
			arr[i] = arr[i + 1];

		size--;
		return res;
	}

	int find_transposition(int val)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == val)
			{
				if (i == 0)
					return i;
				else
				{
					swap(arr[i], arr[i - 1]);
					return i - 1;
				}
			}
		}

		return -1;
	}

};



int main() {


	Vector v(5);

	for (int i = 0; i < 5; i++)
		v.set(i, i);

	v.pop(4);
	v.pop(3);
	v.pop(0);

	v.print();
	cout << v.get_size();

	return 0;
}
