#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <sstream>	
using namespace std;



class Binary_Tree {

private:
	struct Node {

		int data{};
		Node* left{};
		Node* right{};

		Node(int data) :data(data) {}
	};

	Node* root{};

	void print_inorder(Node* current)
	{
		if (!current)
			return;

		print_inorder(current->left);
		cout << current->data;
		print_inorder(current->right);
	}

public:
	Binary_Tree(int root_value):root(new Node(root_value)){}

	void print_inorder()
	{
		print_inorder(root);
		return;
	}

};

class BinaryTree //another approach to avoid using Node* as parameter and that 2 function style
{
private:
	int data{};
	BinaryTree * left{};
	BinaryTree* right{};

public:
	BinaryTree(int data) :data(data) {}

	BinaryTree(string postfix)
	{
		stack<BinaryTree*>tree;

		for (int i = 0; i < postfix.size(); i++)
		{
			BinaryTree* cur = new BinaryTree(postfix[i]);

			if (!isdigit(postfix[i]))
			{
				cur->right = tree.top();
				tree.pop();
				cur->left = tree.top();
				tree.pop();
			}
			tree.push(cur);
		}
		BinaryTree* root = tree.top();
		this->data = root->data;
		this->right = root->right;
		this->left = root->left;
	}

	BinaryTree(deque<int>& preorder, deque<int>& inorder, int inorder_start = 0, int inorder_end = -1)
	{
		if (inorder_end == -1)
			inorder_end = inorder.size() - 1;

		int data = preorder[0];
		preorder.pop_front();

		for (int split = 0; split <= inorder_end; split++)
		{
			if (inorder[split] == data)
			{
				if (inorder_start < split)
					left = new BinaryTree(preorder, inorder, inorder_start, split - 1);
				if (inorder_end > split)
					right = new BinaryTree(preorder, inorder, split + 1, inorder_end);
				break;
			}
		}

	}

	BinaryTree(queue<pair<int, int>>& preorder_queue)
	{
		pair<int, int>p = preorder_queue.front();
		preorder_queue.pop();

			data = p.first;

		if (!p.second)
		{
			left = new BinaryTree(preorder_queue);
			right = new BinaryTree(preorder_queue);
		}

	}

	~BinaryTree() {
		clear();
}

	void print_inorder()
	{
		if (left)
			left->print_inorder();
		cout << data<<" ";
		if (right)
			right->print_inorder();
	}

	void print_postorder()
	{
		if (left)
			left->print_postorder();
		if (right)
			right->print_postorder();
		cout << data << " ";
	}

	void print_preorder()
	{
		cout << data << " ";
		if (left)
			left->print_preorder();
		if (right)
			right->print_preorder();
		cout << data << " ";
	}

	void add(vector<int>values, vector<char>directions)
	{
		assert(values.size() == directions.size());
		BinaryTree* current = this;

		for (int i = 0; i < (int)values.size(); i++)
		{
			if (directions[i] == 'L')
			{
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			}
			else if (directions[i] == 'R')
			{
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}

	void level_order_traversal1()
	{
		queue<BinaryTree*>nodes_queue;
		nodes_queue.push(this);

		while (!nodes_queue.empty())
		{
			BinaryTree* cur = nodes_queue.front();
			nodes_queue.pop();

			cout << cur->data<<" ";

			if (cur->left)
				nodes_queue.push(cur->left);
			if (cur->right)
				nodes_queue.push(cur->right);
		}
		cout << "\n";
    }

	void level_order_traversal2()
	{
		queue<BinaryTree*>nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty())
		{
			int sz = nodes_queue.size();
			cout << "Level " << level<<" :";
			while (sz--)
			{
				BinaryTree* cur = nodes_queue.front();
				nodes_queue.pop();
				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << endl;
		}
	}

	int tree_max()
	{
		int res = data;

		if (left)
			res = max(res, left->tree_max());
		if (right)
			res = max(res, right->tree_max());

		return res;
	}

	int tree_height() {
		int res = 0;

		if (left)
			res = 1 + left->tree_height();
		if (right)
			res = max(res, right->tree_height());

		return res;
	}


	int total_nodes()
	{
		int res = 1;
		if (left)
			res += left->total_nodes();
		if(right)
			res+= right->total_nodes();

		return res;
	}

	int leaf_count()
	{
		int res = !left && !right;

		if(left)
			res+=left->leaf_count();
		if(right)
			res+=right->leaf_count();
		

		return res;
	}

	bool is_exists(int value)
	{
		bool res = value == data;

		if(!res&&left)
			res = left->is_exists(value);
		if (!res && right)
			res = right->is_exists(value);
		
		return res;
		
	}

	bool is_perfect1(int h = -1)
	{
		if (h == -1)
			h = tree_height();

		if (!left && !right)
			return h == 0;

		if (left && !right || right && !left)
			return false;

		return left->is_perfect1(h - 1) && right->is_perfect1(h - 1);
	
	}

	bool is_perfect2()
	{
		int h = tree_height();
		int n = total_nodes();
		return n == pow(2, h + 1) - 1;
	}

	void clear()
	{
		if (left)
		{
			delete left;
			left = nullptr;
		}
		if (right)
		{
			delete right;
			right = nullptr;
		}
	}

	void print_inorder_iterative()
	{
		stack<pair<BinaryTree*, bool>>nodes;

		nodes.push(make_pair(this, false));


		while (!nodes.empty())
		{
			BinaryTree* current = nodes.top().first;
			bool is_done = nodes.top().second;
			nodes.pop();

			if (is_done)
				cout << current->data<<" ";
			else
			{
				if (current->right)
					nodes.push(make_pair(current->right, false));

				nodes.push(make_pair(current, true));

				if(current->left)
					nodes.push(make_pair(current->left, false));
			}
		}
	}

	void traverse_left_boundry()
	{
		cout << data << " ";
		if (left)
			left->traverse_left_boundry();
		else if (right)
			right->traverse_left_boundry();
	}

	pair<int, int>tree_diameter()
	{
		pair<int, int>res = make_pair(0, 0);

		if (!left && !right)
			return res;

		pair<int, int>left_diam = make_pair(0, 0);
		pair<int, int>right_diam = make_pair(0, 0);

		if (left)
		{
			left_diam=left->tree_diameter();
			res.first += 1 + left_diam.second;
		}
		if (right)
		{
			right_diam = right->tree_diameter();
			res.first += 1 + right_diam.second;
		}

		res.first = max(res.first, max(right_diam.first, left_diam.first));

		res.second = 1 + max(left_diam.second, right_diam.second);


		return res;


	}

	bool is_num()
	{
		return (!left && !right);
	}

	void print_inorder_expression()
	{
		if (left)
		{
			if (!left->is_num())
				cout << "(";
			left->print_inorder_expression();
			if (!left->is_num())
				cout << ")";
		}

		cout << data;

		if (right)
		{
			if (!right->is_num())
				cout << "(";
			right->print_inorder_expression();
			if (!right->is_num())
				cout << ")";
		}
	}


	void print_level_nodes(int level)
	{
		if (level == 0)
			cout << data << " ";
		else if (level)
		{
			if (left)
				print_level_nodes(level - 1);
			if (right)
				print_level_nodes(level - 1);
		}
	}

	void level_order_traversal_recursive()
	{
		int h = tree_height();
		for (int level = 0; level <= h; level++)
			print_level_nodes(level);
	}

	void level_order_traversal_spiral()
	{
		stack<BinaryTree*>nodes_stack;
		queue<BinaryTree*>nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty())
		{
			int sz = nodes_queue.size();
			cout << "Level " << level << " :";
			while (sz--)
			{
				BinaryTree* cur = nodes_queue.front();
				nodes_queue.pop();
				cout << cur->data << " ";
				
				if (level % 2 == 0)
				{
					if (cur->left)
						nodes_stack.push(cur->left);
					if (cur->right)
						nodes_stack.push(cur->right);
				}
				else
				{
					if (cur->right)
						nodes_stack.push(cur->right);
					if (cur->left)
						nodes_stack.push(cur->left);
				}

			}
			while (!nodes_stack.empty())
			{
				nodes_queue.push(nodes_stack.top());
				nodes_stack.pop();
			}
			level++;
			cout << endl;
		}
	}

	bool is_complete()
	{
		queue<BinaryTree*>nodes_queue;
		nodes_queue.push(this);

		int h = tree_height();
		int level = 0;

		while (!nodes_queue.empty())
		{
			int sz = nodes_queue.size();
			
			if (level < h && sz != pow(2, level))
				return false;

			while (sz--)
			{
				BinaryTree* cur = nodes_queue.front();
				nodes_queue.pop();
				
				if (level == h - 1 && cur->right && !cur->left)
					return false;

				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}

			level++;
			cout << endl;
		}

		return true;
	}

	void print_preorder_complete()
	{
		cout << data << " ";

		if (left)
			left->print_preorder_complete();
		else
			cout << -1 << " ";

		if (right)
			right->print_preorder_complete();
		else
			cout << -1 << " ";
	}
	
	bool is_mirror(BinaryTree* first, BinaryTree* second) {
		if (!first && !second)
			return true;

		if (first->data != second->data || first && !second || second && !first)
			return false;


		return is_mirror(first->left, second->right) && is_mirror(first->right, second->left);
	}

	bool is_symmetric() {
	return	is_mirror(left, right);
	}

	string toStr(int n) {
		// Convert integer to string
		ostringstream oss;
		oss << n;
		return oss.str();
	}

	string paranthesize()
	{
		string rep = '(' + toStr(data);

		if (left)
			rep += left->paranthesize();
		else
			rep += "()";

		if (right)
			rep += right->paranthesize();
		else
			rep += "()";

		rep += ')';

		return rep;
	}

	string paranthesize_canonical()
	{
		string rep = '(' + toStr(data);

		vector<string>v;

		if (left)
			v.push_back(left->paranthesize_canonical());
		else
			v.push_back("()");

		if (right)
			v.push_back(right->paranthesize_canonical());
		else
			v.push_back("()");

		sort(v.begin(), v.end());

		for (int i = 0; i < v.size(); i++)
			rep += v[i];

		rep += ')';

		return rep;
	}

	bool is_flip_equivalent(BinaryTree* other)
	{
		return this->paranthesize_canonical() == other->paranthesize_canonical();
	}


};




int main()
{
	BinaryTree tree(1);
	

	cout<<tree.is_complete()<<endl<<"bye";

	return 0;
}