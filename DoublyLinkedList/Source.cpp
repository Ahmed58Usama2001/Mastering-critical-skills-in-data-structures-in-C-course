#include <iostream>
#include <cassert>

using namespace std;

struct Node {
	int data{};
	Node* next{};
	Node* prev{};

	Node(int data):data(data){}

	void set(Node* next, Node* prev)
	{
		this->next = next;
		this->prev = prev;
	}

	~Node()
	{
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node* head{};
	Node* tail{};
	int length = 0;

public:
	LinkedList() {
	}

	void print()
	{//O(n)time - O(1)memory
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		
		
		cout << endl;
	}

	void print_reversed()
	{//O(n)time - O(1)memory
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << endl;
	}

	Node* get_nth(int n)
	{
		if (n > length || n < 1)
			return nullptr;

		int counter = 1;
		for (Node* cur = head; cur; cur = cur->next,counter++)
			if (counter == n)
				return cur;

		return nullptr;
	}

	Node* get_nth_back(int n)
	{
		if (n > length || n < 1)
			return nullptr;

		int counter = 1;
		for (Node* cur = tail; cur; cur = cur->prev, counter++)
			if (counter == n)
				return cur;

		return nullptr;
		
	}

	void link(Node* first, Node* second)
	{//O(1)time - O(1)memory
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
	}

	void insert_end(int value)
	{//O(1)time - O(1)memory
		Node* item = new Node(value);
		length++;
		if (!head)
			head = tail = item;
		else
		{
			link(tail, item);
			tail = item;
		}
	}

	void insert_front(int value)
	{//O(1)time - O(1)memory
		Node* item = new Node(value);
		length++;
		if (!head)
			head = tail = item;
		else
		{
			link(item, head);
			head = item;
		}
	}

	void embed_after(Node* node_before, int value)
	{//O(1)time - O(1)memory
		Node* middle = new Node(value);
		length++;
		Node* node_after = node_before->next;
		link(node_before, middle);
		link(middle, node_after);
	}

	void insert_sorted(int value)
	{//O(n)time - O(1)memory
		if (!head || value <= head->data)
			insert_front(value);
		else if (value >= tail->data)
			insert_end(value);
		else
		{
			Node* item = new Node(value);
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (value <= cur->data) {
					embed_after(cur->prev, value);
					break;
				}
			}
		}
	}

	void delete_node(Node* node)
	{//O(1)time - O(1)memory
		length--;
		delete node;
	}

	void delete_front()
	{//O(1)time - O(1)memory
		if (!length)
			return;

		Node* cur = head->next;
		delete_node(head);
		head = cur;

		if (head)
			head->prev = nullptr;
		else if (!length)
			tail = nullptr;

		
	}

	void delete_end()
	{//O(1)time - O(1)memory
		if (!length)
			return;
		Node* cur = tail->prev;
		delete_node(tail);
		tail = cur;
		if (tail)
			tail->next = nullptr;
		else if (!length)
			head = nullptr;
	}

	Node* delete_and_link(Node* node)
	{//O(1)time - O(1)memory
		Node* ret = node->prev;
		link(node->prev, node->next);
		delete_node(node);
		return ret;
	}

	void delete_node_with_key(int key)
	{//O(n)time - O(1)memory
		if (!length)
			return;

		 if (head->data == key)
			delete_front();
		else
		{
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (cur->data == key)
				{
					cur = delete_and_link(cur);
					if (!cur->next)
						tail = cur;
					break;
				}
		}

		}
}

	void delete_all_nodes_with_key(int key)
	{//O(n)time - O(1)memory
		if (!length)
			return;

		while (head&&head->data == key)
			delete_front();
	
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (cur->data == key)
				{
					cur = delete_and_link(cur);
					if (!cur->next)
						tail = cur;
				}
			}
	}

	void delete_even_positions()
	{//O(n)time - O(1)memory
		if (length <= 1)
			return;

		int cnt = 1;
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (cnt % 2 == 0)
				cur = delete_and_link(cur);

			cnt++;
		}
	}

	void delete_odd_positions()
	{//O(n)time - O(1)memory
		insert_front(-5555);
		delete_even_positions();
		delete_front();
	}

	bool is_palindrome()
	{
		if (length <= 1)
			return true;

		for (Node* curh = head, *curt = tail; curh != curt; curh = curh->next, curt = curt->prev)
			if (curh->data != curt->data)
				return false;

		return true;
	}

	Node* find_the_middle1()
	{//O(n)time - O(1)memory
		
		for (Node* cur1 = head, *cur2 = tail; cur1 && cur2; cur1 = cur1->next, cur2 = cur2->prev)
		{
			
			if (cur1 == cur2 || cur1->prev == cur2)
				return cur1;
		}
		return nullptr;
	}

	Node* find_the_middle2() {
		//O(n)time - O(1)memory
		Node* cur1 = head;
		Node* cur2 = head;
		while (cur2 && cur2 != tail)
		{
			cur1 = cur1->next;
			cur2 = cur2->next->next;
		}
		return cur1;
	}

	void swap_kth1(int k)
	{//O(n)time - O(1)memory
		if (k > length)
			return;

		int kth_back = length - k + 1;
		if (k > kth_back)
			swap(k, kth_back);
		if (k == kth_back)
			return;



		Node* first = get_nth(k);
		Node* last = get_nth(kth_back);

		Node* first_prev = first->prev;
		Node* first_next = first->next;
		Node* last_prev = last->prev;
		Node* last_next = last->next;

		if (k + 1 == kth_back)
		{
			link(first_prev, last);
			link(last, first);
			link(first, last_next);
		}
		else
		{
			link(first_prev, last);
			link(last, first_next);
			link(last_prev, first);
			link(first, last_next);
		}

		if (k == 1)
			swap(head, tail);
	}

	void swap_kth2(int k) {
		//O(n)time - O(1)memory
		Node* first = get_nth(k);
		Node* last = get_nth_back(k);

		if (first == last)
			return;	
		if (first->prev == last)	
			swap(first, last);	

		Node* first_prev = first->prev;
		Node* first_next = first->next;

		Node* last_prev = last->prev;
		Node* last_next = last->next;

		if (first->next == last) {	
			link(first_prev, last);
			link(last, first);
			link(first, last_next);
		}
		else {
			link(first_prev, last);
			link(last, first_next);

			link(last_prev, first);
			link(first, last_next);
		}
		if (k == 1)
			swap(head, tail);
	}

	void reverse()
	{
		if (length <= 1)
			return;

		Node* first = head, * second = head->next;
		while (second)
		{
			Node* first_ = second, * second_ = second->next;
			link(second, first);
			first = first_;
			second = second_;
		}
		swap(head, tail);
		head->prev = tail->next = nullptr;
	}

	void merge_2sorted_lists(LinkedList& other)
	{
		if (!other.length)
			return;

		if (head)
		{
			Node* cur1 = head;
			Node* cur2 = other.head;
			Node* last{};
			head = nullptr;

			while (cur1 && cur2)
			{
				Node* next{};
				if (cur1->data < cur2->data)
				{
					next = cur1;
					cur1 = cur1->next;
				}
				else
				{
					next = cur2;
					cur2 = cur2->next;
				}

				link(last, next);
				last = next;

				if (!head)
					head = last;

			}

			if (cur1)
				link(last, cur1);
			else if (cur2)
			{
				tail = other.tail;
				link(last, cur2);
			}
		}
		else
		{
			head = other.head;
			tail = other.tail;
		}

		length += other.length;

	}

};


int main() {
	LinkedList ll1;
	for (int i = 1; i <=10; i++)
   {
		ll1.insert_end(i);	
	}

	//ll1.insert_end(0);
		//ll1.insert_end(2);
		//ll1.insert_end(3);
		//ll1.insert_end(1);


	ll1.print();

	ll1.reverse() ;

	ll1.print();

	cout << "NO RTE\n";

	return 0;
}