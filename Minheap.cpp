#include<iostream>
#include<math.h>
using namespace std;

struct leaf
{
	int data;
	leaf *right, *left;
};

class Minheap
{
	leaf *root;

public:
	Minheap()
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
			if (temp->left == NULL && temp->right == NULL)
			{
				temp->left = new leaf;
				temp->left->data = value;
				temp->left->left = NULL;
				temp->left->right = NULL;
			}
			else
				insertion(temp->left, value);

			if (temp->left->data < temp->data)
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
			if (temp->right->data < temp->data)
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
			if (temp->left->data < temp->data)
			{
				swap = temp->left->data;
				temp->left->data = temp->data;
				temp->data = swap;
			}
		}
		else
		{
			insertion(temp->right, value);
			if (temp->right->data < temp->data)
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

	void deletion(leaf* temp)
	{
		int height_L, height_R, node_count, swap;
		if (root == NULL)
		{
			return;
		}

		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}

		if (temp->left != NULL && temp->right == NULL)
		{
			root->data = temp->left->data;
			temp->left = NULL;
			return;
		}

		height_L = height(temp->left);
		height_R = height(temp->right);
		
		if (height_L == height_R)
		{
			if (temp->right->left == NULL && temp->right->right == NULL)
			{
				root->data = temp->right->data;
				temp->right = NULL;
			}
			else
				deletion(temp->right);
		}
		else if(height_L != height_R)
		{
			if (temp->left->left == NULL && temp->left->right == NULL)
			{
				root->data = temp->left->data;
				temp->left = NULL;
			}
			else
				deletion(temp->left);
		}
	}

	void fix(leaf* temp)
	{
		int swap;

		if (temp->left == NULL && temp->right == NULL)
		{
			return;
		}

		if (temp->right != NULL && temp->left != NULL)
		{
			if (temp->right->data > temp->left->data)
			{
				swap = temp->data;
				temp->data = temp->left->data;
				temp->left->data = swap;
				fix(temp->left);
			}
			else
			{
				swap = temp->data;
				temp->data = temp->right->data;
				temp->right->data = swap;
				fix(temp->right);
			}
			return;
		}
		else
		{
			if (temp->right == NULL)
			{
				swap = temp->data;
				temp->data = temp->left->data;
				temp->left->data = swap;
				fix(temp->left);
			}
			else
			{
				swap = temp->data;
				temp->data = temp->right->data;
				temp->right->data = swap;
				fix(temp->right);
			}
			return;
		}
	}

	void del()
	{
		deletion(root);
		fix(root);
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

	void pp()
	{
		//cout << root->data << endl;
		//cout << root->left->data << endl;// " " << root->right->data << endl;
		//cout << root->left->left->data << endl;// " " << root->left->right->data << endl;// " " << root->right->left->data << endl;// " " << root->right->right->data << endl;
		//cout << root->left->left->left->data << endl;// " " << root->left->left->right->data << endl;
	}

};

int main()
{
	Minheap minh;
	int arr[9] = {100,90,110,80,120,70,130,60,140};

	for (int i = 0; i < 9; i++)
	{
		minh.insert(arr[i]);
		minh.print();
		cout << endl;
	}

	//minh.pp();
	minh.del();
	minh.print();

	return 0;
}