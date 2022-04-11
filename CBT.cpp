#include<iostream>
#include<math.h>
using namespace std;

struct leaf
{
	int data;
	leaf *right, *left;
};

class CBT
{
	leaf *root;

public:
	CBT()
	{
		root = NULL;
	}

	int count_nodes(leaf* iter, int val, int count = 0) {
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

	int find_height(leaf *temp)
	{
		int count = 0;

		if (temp->left != NULL)
		{
			count = 1 + find_height(temp->left);

		}

		return count;
	}

	void insertion(leaf *temp, int value)
	{
		int height_node, node_count;

		if (root == NULL)
		{
			root = new leaf;
			root->data = value;
			root->right = NULL;
			root->left = NULL;
			return;
		}

		height_node = find_height(temp);
		node_count = count_nodes(root,temp->data);

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

			return;
		}

		if (temp->left != NULL && temp->right == NULL)
		{
			temp->right = new leaf;
			temp->right->data = value;
			temp->right->left = NULL;
			temp->right->right = NULL;
			return;
		}

		if (pow(2, (height_node)) - 1 != count_nodes(root, temp->left->data))
			insertion(temp->left, value);
		else
			insertion(temp->right, value);

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

	/*void Del(leaf *temp)		//Incomplete
	{
		if (temp->right != NULL)
		{
			Del(temp->right);
		}
		else
		{
			delete temp->left;

		}
	}*/

};

int main()
{
	CBT cbt;
	cbt.insert(100);
	cbt.insert(14);
	cbt.insert(17);
	cbt.insert(22);
	cbt.insert(45);
	cbt.insert(16);
	cbt.print();

	return 0;
}