#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include<deque>
using namespace std;

class BinarySearchTree {
private:
	int data{ };
	BinarySearchTree* left{ };
	BinarySearchTree* right{ };

	bool find_chain(vector<BinarySearchTree*>& ancestors, int target)
	{
		ancestors.push_back(this);

		if (target == data)
			return true;


		if (target < data)
			return left && left->find_chain(ancestors, target);

		return right && right->find_chain(ancestors, target);
	}

public:

	BinarySearchTree(int data,BinarySearchTree*left=nullptr,BinarySearchTree*right=nullptr) :
		data(data),left(left), right(right) {
	}

	BinarySearchTree(deque<int>& preorder, int start = 0, int end = -1)
	{
		if (end == -1)
			int end = preorder.size() - 1;

		int data = preorder[start];

		for (int split = start + 1; split <= end + 1; split++)
		{
			if (split == end + 1 && preorder[split] > data)
			{
				if (start + 1 <= split - 1)
					left = new BinarySearchTree(preorder, start + 1, split - 1);

				if (split <= end)
					right = new BinarySearchTree(preorder, split, end);

				break;
			}
		}

	}

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}



	bool search(int target) {	
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}

	void insert(int target)
	{
		if (target < data)
		{
			if (!left)
				left = new BinarySearchTree(target);
			else
				left->insert(target);
		}
		else if (target > data)
		{
			if (!right)
				right = new BinarySearchTree(data);
			else
				right->insert(target);
		}
	}

	bool search_iterative(int target)
	{
		BinarySearchTree* node = this;

		while (node)
		{
			if (target == node->data)
				return true;
			else if (target > node->data)
				node = node->right;
			else
				node = node->left;
		}
		return false;
	}

	void get_inorder(vector<int>& values)
	{
		if (left)
			left->get_inorder(values);
		values.push_back(data);
		if (right)
			right->get_inorder(values);
	}

	bool is_BST1()
	{
		vector<int>nodes;
		get_inorder(nodes);

		for (int i = 1; i < nodes.size(); i++)
		{
			if (nodes[i] < nodes[i - 1])
				return false;
		}
		return true;

	}

	bool is_BST2(int mn = INT_MIN, int mx = INT_MAX)
	{
		bool status = mn < data&& data < mx;

		if (!status)
			return false;

		bool left_BST = !left || left->is_BST2(mn, data);

		if (!left_BST)
			return false;

		bool right_BST = !right || right->is_BST2(data, mx);

		return right_BST;


	}

	int kth_smallest(int& k)
	{
		if (k == 0)
			return -1234;

		if (left)
		{
			int res = left->kth_smallest(k);
			if (k == 0)
				return res;
		}
		k--;
		if (k == 0)
			return data;

		return right->kth_smallest(k);

		return -1234;
	}

	int lca(int x, int y)
	{
		if (x > data && y > data)
			return right->lca(x, y);

		if (x < data && y < data)
			return left->lca(x, y);

		return data;
	}

	int min_value()
	{
		BinarySearchTree* cur = this;
		while (cur && cur->left)
			cur = cur->left;
		return cur->data;
	}

	BinarySearchTree* get_next(vector<BinarySearchTree*>& ancestors)
	{
		if (ancestors.size() == 0)
			return nullptr;

		BinarySearchTree* parent = ancestors.back();
		ancestors.pop_back();

		return parent;
	}

	pair<bool, int>successor(int target)
	{
		vector<BinarySearchTree*>ancestors;

		if(!find_chain(ancestors,target))
			return make_pair(false,-1);

		BinarySearchTree* child = get_next(ancestors);

		if (child->right)
			return make_pair(true, child->right->min_value());

		BinarySearchTree* parent = get_next(ancestors);

		while (parent && parent->right == child)
		{
			child = parent;
			parent = get_next(ancestors);
		}

		if(parent)
		return make_pair(true, parent->data);

		return make_pair(false, -1);
	}


	void successor_queries(deque<int>& queries, vector<int>& answers, vector<int>& traversal)
	{
		if (queries.empty())
			return;

		if (left && data < queries.front())
		{
			left->successor_queries(queries, answers, traversal);
			if (queries.empty())
				return;
		}

		if (!traversal.empty() && traversal.back() == queries.front())
		{
			answers.push_back(data);
			queries.pop_front();
			if (queries.empty())
				return;
		}

		traversal.push_back(data);

	
		if (right && data >= queries.front())
			right->successor_queries(queries, answers, traversal);

	}

	bool is_degenerate(vector<int>& preorder)
	{
		if (preorder.size() <= 2)
			return true;

		int mn = 0, mx = 1000;

		for (int i = 1; i < preorder.size(); i++)
		{
			if (preorder[i]<mn || preorder[i]>mx)
				return false;

			if (preorder[i] > preorder[i - 1])
				mn = preorder[i - 1] + 1;
			else
				mx = preorder[i - 1] - 1;
		}
	
		return true;
	}


	BinarySearchTree* min_node()
	{
		BinarySearchTree* cur = this;
		while (cur && cur->left)
			cur = cur->left;

		return cur;
	}

	BinarySearchTree* delete_node(int target, BinarySearchTree* node)
	{
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else
		{
			BinarySearchTree* tmp = node;
			if (!node->left && !node->right)
				node = nullptr;
			else if (!node->left)
				node = node->right;
			else if (!node->right)
				node = node->left;
			else
			{
				BinarySearchTree* mn = node->right->min_node();
				node->data = mn->data;
				node->right = delete_node(mn->data, node->right);
				tmp = nullptr;
			}
			if (tmp)
				delete node;

		}
		return node;
	}

	BinarySearchTree* delete_node_p(int target, BinarySearchTree* node)
	{
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node_p(target, node->left);
		else if (target > node->data)
			node->right = delete_node_p(target, node->right);
		else
		{
			BinarySearchTree* tmp = node;
			if (!node->left && !node->right)
				node = nullptr;
			else if (!node->left)
				node = node->right;
			else if (!node->right)
				node = node->left;
			else
			{
				BinarySearchTree* mx = node->left->max_node();
				node->data = mx->data;
				node->left = delete_node(mx->data, node->left);
				tmp = nullptr;
			}
			if (tmp)
				delete node;

		}
		return node;
	}

	BinarySearchTree* max_node()
	{
		BinarySearchTree* cur = this;
		while (cur && cur->right)
			cur = cur->right;

		return cur;
	}


	void delete_value(int target)
	{
		if (target == data && !left && !right)
			return;

		delete_node(target, this);
	}


};


BinarySearchTree* build_balanced_bst(vector<int>& values, int start = 0, int end = -10)
{
	if (end == -10)
		end = values.size() - 1;

	int mid = (start + end) / 2;

	BinarySearchTree* left = build_balanced_bst(values, start, mid - 1);
	BinarySearchTree* right = build_balanced_bst(values, mid + 1, end);
	BinarySearchTree* root = new BinarySearchTree(values[mid], left, right);

	return root;
}


int main() {

	cout << "bye\n";

	return 0;
}

