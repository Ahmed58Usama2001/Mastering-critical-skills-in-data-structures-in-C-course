#include <iostream>
#include <cassert>
#include<vector>
#include<algorithm>
using namespace std;


typedef int type;

class Stack {
private:
	int top{};
	int size{};
	type* array{};
public:

	Stack(int size) :size(size), top(-1)
	{//O(n) time - O(n)memory
		array = new type[size];
	}

	~Stack()
	{//O(n) time - O(1)memory
		delete[]array;
		array = nullptr;
	}

	bool isFull()
	{//O(1)time - O(1)memory
		return top == size - 1;
	}

	bool isEmpty()
	{//O(1)time - O(1)memory
		return top == -1;
	}

	void push(type value)
	{//O(1)time - O(1)memory
		assert(!isFull());
		array[++top] = value;
	}

	type pop()
	{//O(1)time - O(1)memory
		assert(!isEmpty());
		return array[top--];
	}

	type peek()
	{//O(1)time - O(1)memory
		assert(!isEmpty());
		return array[top];
	}

	void Display()
	{//o(n)time - o(1)memory
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << endl;
	}

	void display_reversed() {
		//o(n)time - o(1)memory
		for (int i = 0; i <= top; i++)
			cout << array[i] << " ";
		cout << "\n";
	}

	void insert_at_bottom(int x)
	{//o(n)time - o(n)memory
		if (isEmpty())
			push(x);
		else
		{
			int cur = pop();

			insert_at_bottom(x);

			push(cur);
		}
	}

	void reverse_stack()
	{//o(n^2)time - o(n^2)memory
		if (isEmpty())
			return;
		else
		{
			int cur = pop();

			reverse_stack();

			insert_at_bottom(cur);
		}
	}

};

string reverse_subwords(string line)
{//O(n)time - O(n)memory
	string res{};
	line += ' ';
	Stack s((int)line.size());
	
	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] != ' ')
			s.push(line[i]);

		else
		{
			while (!s.isEmpty())
				res +=s.pop();
			res += ' ';
		}

	}
	return res;
}

int reverse_number(int num)
{//O(n)time - O(n)memory
	Stack s(20);
	while (num)
	{
		s.push(num % 10);
		num /= 10;
	}

	int n = 1;

	while (!s.isEmpty())
	{
		num += s.pop() * n;
		n *= 10;
	}

	
	return num;
}

bool check(char open,char close)
{
	if (open == '[' && close == ']')
		return true;

	else if (open == '{' && close == '}')
		return true;

	else if (open == '(' && close == ')')
		return true;

	return false;
}
bool isValid(string str)
{//O(n)time - O(n)memory
	Stack s(str.size());

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '[' || str[i] == '{' || str[i] == '(')
			s.push(str[i]);
		else
		{
			if (s.isEmpty())
				return false;

			else
			{
				if (check(s.peek(),str[i]))
					s.pop();
					
				else
					return false;
			}

		}
	}
	return s.isEmpty();
}

string removeDuplicates(string str)
{//O(n)time - O(n)memory
	Stack s1(str.size()), s2(str.size());
	for (int i = 0; i < (int)str.size(); i++)
	{
		if (s1.isEmpty() || s1.peek() != str[i])
			s1.push(str[i]);
		else
			s1.pop();
	}
	str = {};

	while (!s1.isEmpty())
		s2.push(s1.pop());
	
	while (!s2.isEmpty())
		str += s2.pop();
	
	return str;
}

void asteroidCollision(int arr[], int len) {
	Stack result(len);

	for (int i = 0; i < len; ++i) {
		int asteroid = arr[i];
		// For every new asteroid, remove all what will explode
		// Only may happens when asteroid going backword and something coming forward
			// asteroid < 0 && 0 < result.peek()
		bool is_exploded = false;
		while (!result.isEmpty() && asteroid < 0 && 0 <= result.peek()) {
			// last will explode.
			if (result.peek() < -asteroid) {
				result.pop();
				continue;	// See if more explode
			}
			else if (result.peek() == -asteroid)	// both exploded
				result.pop();
			is_exploded = true;		// only asteroid explode
			break;
		}
		if (!is_exploded)
			result.push(asteroid);
	}
	result.display_reversed();
}

int scoreOfParentheses(string str)
{//o(n)time - o(n)memory
	Stack s(str.size());
	for (int i = 0; i < (int)str.size(); i++)
	{
		if (str[i] == '(')
			s.push(str[i]);
		else
		{
			int n;
			if (s.peek() == '(')
			{
				s.pop();
				n = 1;
			}
			else
			{
				n = 2 * s.pop();
				s.pop();
			}

			if (s.isEmpty() || s.peek()=='(')
				s.push(n);
			else
				s.push(n + s.pop());
		}
	}

	return s.peek();

}

vector<int> next_greater_element(int size,vector<int>&v)
{//o(n)time - o(n)memory
	Stack pos(size);
	for (int i = 0; i < size; i++)
	{
		while (!pos.isEmpty() && v[i] > v[pos.peek()])
			v[pos.pop()] = v[i];
		pos.push(i);
	}

	while (!pos.isEmpty())
		v[pos.pop()] = -1;

	return v;

}


class ll_Stack
{
private:
	struct Node {
		int data{};
		Node* next{};

		Node(int value):data(value){}
	};
	Node* head{};

public:
	void push(int value)
	{
		Node* item = new Node(value);
		item->next = head;
		head = item;
	}

	bool isEmpty()
	{
		return !head;
	}

	int peek()
	{
		assert(!isEmpty());
		int element = head->data;
		return element;
	}

	int pop()
	{
		assert(!isEmpty());
		int element = head->data;
		Node* temp = head;
		head = head->next;
		delete temp;
		return element;
	}


};

int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	
	if (op == '*' || op == '/')
		return 2;

	if (op == '^')
		return 3;

	return 0;
}
string infixTopostfix(string& infix)
{
	string postfix;
	ll_Stack operators;

	for (int i = 0; i < (int)infix.size(); i++)
	{
		if (isdigit(infix[i])||isalpha(infix[i]))
			postfix += infix[i];

		else if (infix[i] == '(')
			operators.push(infix[i]);

		else if (infix[i] == ')')
		{
			while (operators.peek() != '(')
				postfix += operators.pop();
			operators.pop();
		}

		else if (infix[i] == '^')
			operators.push(infix[i]);

		else
		{
			while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(infix[i]))
				postfix += operators.pop();

			operators.push(infix[i]);
			
		}
	}

	while (!operators.isEmpty())
		postfix += operators.pop();

	return postfix;
}

double math(double operand1, char operation ,double operand2)
{
	if (operation == '+')
		return operand1 + operand2;

	 if (operation == '-')
		return operand1 - operand2;

	 if (operation == '*')
		return operand1 * operand2;

	 if (operation == '/')
		return operand1 / operand2;

		return pow(operand1,operand2);
}
double evalaute_postfix(string postfix)
{
	ll_Stack evaluation;

	for (int i = 0; i < (int)postfix.size(); i++)
	{
		
		if (isdigit(postfix[i]))
			evaluation.push(postfix[i]-'0');

		else
		{
			double op2=evaluation.pop();
			double op1 = evaluation.pop();
			
			evaluation.push(math(op1, postfix[i], op2));
		}
	}
	return evaluation.pop();
}

string infixToprefix(string infix)
{
	string rev = string(infix.rbegin(), infix.rend());
	string prefix{};
	ll_Stack operators;
	char temp;
	for (int i = 0; i < (int)rev.size(); i++)
	{
		if (isdigit(rev[i]))
			prefix = rev[i] + prefix;

		else if (rev[i] == '(')
			operators.push(rev[i]);

		else if (rev[i] == ')')
		{

			while (operators.peek() != '(')
			{
				temp = operators.pop();
				prefix = temp + prefix;
			}
			operators.pop();
		}

		else
		{
			while (!operators.isEmpty() && precedence(operators.peek()) > precedence(rev[i]))
			{
				temp = operators.pop();
				prefix = temp + prefix;
			}

			operators.push(rev[i]);

		}
	}

	while (!operators.isEmpty())
	{
		temp = operators.pop();
		prefix = temp + prefix;
	}

	return prefix;
}



int main()
{
	string infix = "2*3+4";

	cout << infixToprefix(infix);

	
	cout << "\nNo RTE\n";

}