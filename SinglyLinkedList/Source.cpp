#include<iostream>
#include<assert.h>
using namespace std;

struct Node
{
	int data;
	Node* next{};

	Node(int data):data(data){}
	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}

};


class LinkedList {

private:
	Node* head{};
	Node* tail{};
	int length = 0;

public:
	~LinkedList() {		
		while (head) {
			Node* current = head->next;
			delete head;
			head = current;
		}
	}

	void print()
	{//time O(n) - Memory O(1)
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data<<" ";

		//if(length)
		//cout << head->data << " " << tail->data;  //print head and tail

		cout << endl;
		
	}

	void print1()
	{//time O(n) - Memory O(1)
		Node* temp_head = head;
		while (temp_head != nullptr)
		{
			cout << temp_head->data << " ";
			temp_head = temp_head->next;
		}
		cout << endl;
	}

	void insert_end(int value)
	{
		//time O(1) - Memory O(1)
		Node* node = new Node(value);

		if (!head)
			head = tail = node;

		else
		{
			tail->next = node;
			tail = node;
		}
		length++;
	}

	void insert_front(int value)
	{ //time O(1) - Memory O(1)
		Node* node = new Node{ value };
		if (!head)
		{
			head = tail = node;
		}
		else
		{
			Node* cur = head;
			head = node;
			head->next = cur;
		}
		length++;
	}

	void delete_front()
	{//time O(1) - Memory O(1)
		assert(head);
		if (length == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node* cur = head;
			head = head->next;
			delete cur;
		}
		length--;
	}

	void delete_last()
	{
		if (length <= 1)
		{
			delete_front();
			return;
		}
		Node* prev = get_nth(length - 1);
		delete tail;
		length--;
		tail = prev;
		tail->next = nullptr;
	}

	void delete_nth(int n)
	{
		assert(n > 1 && n <= length);
		if (n == 1)
			delete_front();
		else if (n == length)
			delete_last();
		else
		{
			Node* prev = get_nth(n - 1);
			Node* cur = prev->next;
			prev->next = cur->next;
			delete cur;
			length--;
		}
	}

	Node* get_nth(int n)
	{//time O(n) - Memory O(1)
		int counter = 1;
		for (Node* cur = head; cur; cur = cur->next,counter++)
			if (counter == n)
				return cur;
	
		return NULL;
	}

	Node* get_nth_back(int n)
	{//time O(n) - Memory O(1)
		if (length < n)
			return nullptr;

		return get_nth(length-1+1);
	}

	int search(int value)
	{//time O(n) - Memory O(1)
		int counter = 0;
		for (Node* cur = head; cur; cur = cur->next,counter++)
			if (cur->data == value)
				return counter;

		return -1;
	}

	int search_improved(int value)
	{
		//time O(n) - Memory O(1)
		int idx = 0;
		for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next, idx++)
		{
			if (cur->data == value)
			{
				if (!prv)
					return idx;
				swap(prv->data, cur->data);
				return idx - 1;
	       	}

		}
		return -1;
	}

	bool is_same1(const LinkedList& other)
	{//time O(n) - Memory O(1)
		Node* h1 = head, *h2 = other.head;

		while (h1 && h2)
		{
			if (h1->data != h2->data)
				return false;
			h1 = h1->next;
			h2 = h2->next;
		}
		return (!h1 && !h2);
	}

	bool is_same2(const LinkedList& other)  // length variable is maintainable
	{//time O(n) - Memory O(1)
		if (length != other.length)
			return false;
		Node* cur_h2 = other.head;
		for (Node* cur_h1 = head; cur_h1; cur_h1 = cur_h1->next)
		{
			if (cur_h1->data != cur_h2->data)
				return false;

			cur_h2 = cur_h2->next;
		}
		return true;
	}

	void delete_next_node(Node* node) {
		Node* to_delete = node->next;
		bool is_tail = to_delete == tail;
		node->next = node->next->next;
		delete to_delete;
		length--;
		if (is_tail)
			tail = node;
	}
	void embed_after(Node* node, int value) {
		// Add a node with value between node and its next
		Node* item = new Node(value);
		++length;
		item->next = node->next;
		node->next = item;
	}

	void delete_node_with_k(int value)
	{ //O(n)time - O(1)Memory
		assert(head);
		Node* prev = nullptr;
		for (Node* cur = head; cur;prev=cur, cur = cur->next)
		{
			if (cur->data == value)
			{
				if (cur == head)
					delete_front();
				
				else
					delete_next_node(prev);
				
				return;
			}
		}
	}

	void swap_pairs()
	{//O(n)time - O(1)Memory
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (cur->next)
			{
				swap(cur->data, cur->next->data);
				cur = cur->next;
			}
		}
	}

	void reverse()
	{// O(n) time - O(1) memory
		if (length <= 1)
			return;

		tail = head;
		Node* prev = head;
		head = head->next;
		while (head)
		{
			Node* next = head->next;
			head->next = prev;

			prev = head;
			head = next;
		}

		head = prev;
		tail->next = nullptr;
	}

	void delete_even_pos()
	{
	//	O(n) time - O(1) memory
		Node* cur = head;
		while (cur->next)
		{
			delete_next_node(cur);

			if(cur->next)
			cur = cur->next;
		}
	}

	void insert_sorted(int value)
	{// O(n) time - O(1) memory
		if (!length || value >= tail->data)
			insert_end(value);
		else if (value <= head->data)
			insert_front(value);
		else
		{
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (value > cur->data&&value<=cur->next->data)
				{
					embed_after(cur, value);
					break;
				}
			}
			
		}
		
	}

	Node* get_previous(Node* target)
	{//O(1) memory - O(n)Time
		for (Node* cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next)
		{
			if (cur == target)
				return prev;
		}

		return nullptr;
	}

	void swap_head_and_tail()
	{//O(1) memory - O(n)Time
		if (!head || !head->next)
			return;

		Node* prev = get_previous(tail);
		tail->next = head->next;
		head->next = nullptr;
		prev->next = head;
		swap(tail, head);
	}

	void left_rotate(int k)
	{//O(1)memory - O(n)time
		k = k % length;
		if (k == 0||length<=1)
			return;

		Node* kth = get_nth(k);
		tail->next = head;
		head = kth->next;
		kth->next = nullptr;
		tail = kth;
	}

	void remove_dublicates()
	{//O(n^2)time - O(1)memory
		for (Node* cur1 = head; cur1; cur1 = cur1->next)
		{
			for (Node* cur2 = cur1->next, *prev = cur1; cur2;)
			{
				if (cur1->data == cur2->data)
				{
					delete_next_node(prev);
					cur2 = prev->next;
				}
				else
				{
					prev = cur2;
					cur2 = cur2->next;
				}
			}
		}
	}

	void remove_last_occurance(int k)
	{//O(1) memory - O(n)Time
		if (!length)
			return;

		Node* n=nullptr;
		for (Node* cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next)
		{
			if (cur->data == k)
			{
				n = prev;
			}
		}

		if (n)
		{
			delete_next_node(n);
			return;
		}

		if (head->data == k)
			delete_front();
	}

	void move_to_back(int k)
	{//O(1) memory - O(n)Time
		int cnt = 0;
		for (Node* cur = head, *prev = nullptr; cnt!=length;cnt++)
		{
			if (cur->data == k)
			{
			
				if (prev == nullptr)
				{
					
					head = cur->next;
					tail->next = cur;
					tail = cur;
					cur = cur->next;
					tail->next = nullptr;
				}
				else
				{
					prev->next = cur->next;
					tail->next = cur;
					tail = cur;
					cur = cur->next;
					tail->next = nullptr;
				}
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
			
		}
	}

	int max(Node* head=nullptr , bool is_first_call = true)
	{// O(n) time - O(n) memory
		if (is_first_call)
			return this->max(this->head, false);

		if (head == nullptr)
			return INT_MIN;

		return std::max(head->data, this->max(head->next, false));
		
	}

	void arrange_odd_and_even_nodes()
	{//O(n)time - O(1)memory
		if (length <= 2)
			return;

		int cnt = 0, target=length/2 ;

		for (Node* cur = head; cnt != target; cnt++, cur = cur->next)
		{
			Node* move_back = cur->next;
			cur->next = move_back->next;
			tail->next = move_back;
			move_back->next = nullptr;
			tail = move_back;
		}
		
	}

	void insert_alternate(LinkedList& another) {//O(n+m) time - O(m) memory
		Node* cur1 = this->head, * cur2 = another.head;

		while (cur1 && cur2)
		{
			embed_after(cur1, cur2->data);
			cur1 = cur1->next->next;
			cur2=cur2->next;
			if (tail->next)
				tail = tail->next;
		}

		while (cur2)
		{
			insert_end(cur2->data);
			cur2 = cur2->next;
		}
	}

	void adding_2_huge_numbers(LinkedList& another)
	{// let X = max(length, another.length)
		// let Y = max(length, another.length) - min(length, another.length)
		// O(X) time - O(Y) memory
		if (!length)
		{
			head = another.head;
			tail = another.tail;
			length = another.length;
			return;
		}
		if (!another.length)
			return;

		Node* cur1 = head, * cur2 = another.head;
		int carry = 0, my_value, his_value;

		while (cur1 || cur2)
		{
			my_value = 0, his_value = 0;
			if (cur1)
				my_value = cur1->data;

			if (cur2)
			{
				his_value = cur2->data;
				cur2 = cur2->next;
			}

			my_value += his_value + carry;
			carry = my_value / 10;
			my_value %= 10;

			if (cur1)
			{
				cur1->data = my_value;
				cur1 = cur1->next;
			}
			else
			{
				insert_end(my_value);
			}

		}
		if (carry)
			insert_end(carry);

	}

	void reverse_chain(int k)
	{//O(n)time - O(1)memory
		if (length <= 1)
			return;

		int cnt, n = 1,ending=length/k;
		Node* cur = head,*prv=nullptr;
		while (cur&&ending--)
		{
			
			cnt = k;
			Node* to_insert_after = get_nth(k * n);
			while (cnt-- && cur)
			{
				
				embed_after(to_insert_after, cur->data);
				if (!prv)
				{
					cur = cur->next;
					delete_front();
				}
				else
				{
					cur = cur->next;
					delete_next_node(prv);

				}
			}

			cnt = k;
			while (cnt-- && cur)
			{
				
				prv = cur;
				cur = cur->next;

			}
			n++;
		}
		
    }

};








void print1(Node* head)
{
	while (head != nullptr)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void print2(Node* head)
{
	if (head == nullptr)
	{
		cout << endl;
		return;
	}
	
	cout << head->data;
	print2(head->next);
}

void print3_reversed(Node* head)
{
	if (head == nullptr)
	{
		cout << endl;
		return;
	}
	print3_reversed(head->next);
	cout << head->data << " ";
}

Node* find(int value,Node*head)
{
	while (head != nullptr)
	{
		if (head->data == value)
		{
			return head;
		}

		else
		head = head->next;
	}
	return NULL;
}


int main()
{
	LinkedList ll1,ll2;

	for (int i = 1; i <=6 ; i++)
	{
	ll1.insert_end(i);
	}

	//for (int i = 1; i <=3; i++)
		//ll2.insert_end(i);

	//ll1.insert_end(1);
	//ll1.insert_end(1);
//	ll1.insert_end(2);
	//ll1.insert_end(2);
	//ll1.insert_end(2);
  //  ll1.insert_end(3);
//	ll1.insert_end(5);
//	ll1.insert_end(3);
	//ll1.insert_end(8);
//	ll1.insert_end(8);
	//ll1.insert_end(1);
	

	ll1.print();
	
	//ll1.reverse_chain(14);

	ll1.print();
	
	cout << "\nNO RTE\n";

	return 0;
}