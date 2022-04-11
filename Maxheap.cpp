#include<iostream>
#include<math.h>
using namespace std;

struct leaf
{
	int data;
	leaf *right, *left;
};

class Maxheap
{
	leaf *root;

public:
	Maxheap()
	{
		root = NULL;
	}

	int count_nodes(leaf* iter, int val, int count = 0) {
		//   YOUR CODE HERE /////

		int left = 0, right = 0;

		if (iter->data == val)
		{
			if (iter->left != NULL)
				left = 1 + count_nodes(iter->left, iter->left->data, count + 1);

			if (iter->right != NULL)
				right = 1 + count_nodes(iter->right, iter->right->data, count + 1);

			if (count == 0)
				return left + right + 1;
			else
				return left + right;
		}

		if (iter->left != NULL)
			left = count_nodes(iter->left, val, count);

		if (iter->right != NULL)
			right = count_nodes(iter->right, val, count);

		return left + right;
	}

	int height(leaf *temp)
	{
		int count = 0;

		if (temp->left != NULL)
		{
			count = 1 + height(temp->left);

		}

		return count;
	}

	void insertion(leaf *temp, int value)
	{
		int height_node, node_count, swap;

		if (root == NULL)
		{
			root = new leaf;
			root->data = value;
			root->right = NULL;
			root->left = NULL;
			return;
		}

		height_node = height(temp);
		node_count = count_nodes(root, temp->data);

		if (pow(2, (height_node + 1)) - 1 == node_count)
		{
			while (temp->left != NULL)
			{
				temp = temp->left;
			}

			temp->left = new leaf;
			temp->left->data = value;
			temp->left->left = NULL;
			temp->left->right = NULL;
			if (temp->left->data > temp->data)
			{
				swap = temp->left->data;
				temp->left->data = temp->data;
				temp->data = swap;
			}

			return;
		}

		if (temp->left != NULL && temp->left->left == NULL)
		{
			temp->right = new leaf;
			temp->right->data = value;
			temp->right->left = NULL;
			temp->right->right = NULL;
			if (temp->right->data > temp->data)
			{
				swap = temp->right->data;
				temp->right->data = temp->data;
				temp->data = swap;
			}
			return;
		}

		if (pow(2, (height_node)) - 1 != count_nodes(root, temp->left->data))
		{
			insertion(temp->left, value);
			if (temp->left->data > temp->data)
			{
				swap = temp->left->data;
				temp->left->data = temp->data;
				temp->data = swap;
			}
		}
		else
		{
			insertion(temp->right, value);
			if (temp->right->data > temp->data)
			{
				swap = temp->right->data;
				temp->right->data = temp->data;
				temp->data = swap;
			}
		}

	}

	void insert(int value)
	{
		insertion(root, value);
	}

	void p(leaf *temp) {
		if (temp == NULL)
			return;
		p(temp->left);
		cout << temp->data << " ";
		p(temp->right);
	}

	void print()
	{
		p(root);
	}

};

int main()
{
	Maxheap maxh;
	maxh.insert(100);
	maxh.insert(14);
	maxh.insert(17);
	maxh.insert(22);
	maxh.insert(45);
	maxh.insert(16);
	maxh.print();

	return 0;
}