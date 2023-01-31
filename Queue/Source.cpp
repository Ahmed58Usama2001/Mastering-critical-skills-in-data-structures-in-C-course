#include<iostream>
#include<assert.h>
using namespace std;

class Queue {

private:
	int size{};
	int added_elements{};
	int rear{ 0 };
	int front{0};
	int* array{};

public:

	Queue(int size) :size(size) {
		array = new int[size];
	}

	int next(int pos)
	{
		pos++;
		if (pos == size)
			pos = 0;

		return pos;
	}

	bool isEmpty()
	{
		return added_elements == 0;
	}

	bool isFull()
	{
		return added_elements == size;
	}

	void enqueue(int value)
	{
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	int dequeue()
	{
		assert(!isEmpty());
		int element = array[front];
		front = next(front);
		added_elements--;
		return element;
	}

	void display()
	{
		cout << "Front: " << front << " - Rear: " << rear << "\n";
		if (isFull())
			cout << "full\n";
		else if (isEmpty())
		{
			cout << "empty\n";
			return;
		}

		for (int cur = front, step = 0; step < added_elements; step++, cur = next(cur))
			cout << array[cur] << " ";

		cout << "\n\n";
	}


};

class Deque {
private:
	int size{};
	int added_elements{};
	int rear{ 0 };
	int front{ 0 };
	int* array{};

public:

	Deque(int size) :size(size) {
		array = new int[size];
	}


	int next(int pos)
	{
		pos++;
		if (pos == size)
			pos = 0;

		return pos;
	}

	int back(int pos)
	{
		pos--;
		if (pos == -1)
			pos = size - 1;

		return pos;
	}

	bool isEmpty()
	{
		return added_elements == 0;
	}

	bool isFull()
	{
		return added_elements == size;
	}

	void enqueue_rear(int value)
	{
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	void enqueue_front(int value)
	{
		assert(!isFull());
		front = back(front);
		array[front] = value;
		added_elements++;
	}

	int dequeue_front()
	{
		assert(!isEmpty());
		int element = array[front];
		front = next(front);
		added_elements--;
		return element;
	}

	int dequeue_rear()
	{
		assert(!isEmpty());
		int element = array[rear];
		rear = back(rear);
		added_elements--;
		return element;
	}

	void display()
	{
		cout << "Front: " << front << " - Rear: " << rear << "\n";
		if (isFull())
			cout << "full\n";
		else if (isEmpty())
		{
			cout << "empty\n";
			return;
		}

		for (int cur = front, step = 0; step < added_elements; step++, cur = next(cur))
			cout << array[cur] << " ";

		cout << "\n\n";
	}



};


class PriorityQueue {
private:
	int size{ };
	int added_elements{ };
	Queue q1, q2, q3;

public:
	PriorityQueue(int size) :
		size(size), q1(size), q2(size), q3(size) {
	}

	void enqueue(int value, int priority) {
		assert(!isFull());

		if (priority == 3)
			q3.enqueue(value);
		else if (priority == 2)
			q2.enqueue(value);
		else if (priority == 1)
			q1.enqueue(value);
		else
			assert(false);	// priority > 3
		++added_elements;
	}

	int dequeue() {
		assert(!isEmpty());
		--added_elements;

		if (!q3.isEmpty())
			return q3.dequeue();
		else if (!q2.isEmpty())
			return q2.dequeue();
		else
			return q1.dequeue();
	}

	void display() {
		if (!q3.isEmpty()) {
			cout << "Priority #3 tasks: ";
			q3.display();
		}
		if (!q2.isEmpty()) {
			cout << "Priority #2 tasks: ";
			q2.display();
		}
		if (!q1.isEmpty()) {
			cout << "Priority #1 tasks: ";
			q1.display();
		}
		cout << "******************\n";
	}

	int isEmpty() {
		return added_elements == 0;
	}

	bool isFull() {
		return added_elements == size;
	}
};


int main()
{
	Deque dq(6);

	dq.enqueue_front(3);
	dq.display();
	dq.enqueue_front(2);
	dq.enqueue_rear(4);
	dq.enqueue_front(1);
	dq.enqueue_front(5);
	dq.enqueue_front(6);
	dq.display();	// 1 2 3 4
	cout << dq.dequeue_rear() << "\n";	// 4
	dq.display();	// 1 2 3
	cout << dq.dequeue_front() << "\n";	// 1
	dq.display();	// 2 3
	cout << dq.dequeue_rear() << "\n";	// 3
	cout << dq.dequeue_front() << "\n";	// 2

	while (!dq.isEmpty())
		dq.dequeue_rear();
	dq.display();	//
	for (int i = 0; i < 6; ++i)
		dq.enqueue_rear(i + 10);
	dq.display();	//


	return 0;
}