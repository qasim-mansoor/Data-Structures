#include<iostream>
using namespace std;

struct leaf
{
	int data;
	leaf *right, *left;
};

class BST
{
	leaf *root;
	
public:
	BST()
	{
		root = NULL;
	}

	void Insertion(leaf* temp, int value)
	{
		if (root == NULL)
		{
			temp = new leaf;
			temp->data = value;
			temp->left = NULL;
			temp->right = NULL;
			root = temp;
			return;
		}

		if (value == temp->data)
		{
			cout << "Duplicate value found" << endl;
			return;
		}

		if (value > temp->data)
		{
			if (temp->right != NULL)
			{
				Insertion(temp->right, value);
				return;
			}

			temp->right = new leaf;
			temp->right->data = value;
			temp->right->right = NULL;
			temp->right->left = NULL;
			return;
		}

		if (value < temp->data)
		{
			if (temp->left != NULL)
			{
				Insertion(temp->left, value);
				return;
			}

			temp->left = new leaf;
			temp->left->data = value;
			temp->left->right = NULL;
			temp->left->left = NULL;
			return;
		}

	}

	void Insertion2(int value)
	{
		Insertion(root, value);
	}

	void p(leaf* temp)
	{
		if (temp == NULL)
		{
			cout << "Tree is empty";
			return;
		}

		if (temp->left != NULL)
			p(temp->left);

		cout << temp->data << " ";

		if (temp->right != NULL)
			p(temp->right);

	}

	void print()
	{
		p(root);
	}

	void d(leaf* temp1, int value)
	{
		leaf* temp2, *temp3, *temp4;

		if (value > temp1->data)
		{
			if (temp1->right == NULL)
			{
				cout << "Data not found" << endl;
				return;
			}

			if ((temp1->right->data == value && temp1->right->right != NULL) || (temp1->right->data == value && temp1->right->left != NULL))
			{
				if (temp1->right->right != NULL && temp1->right->left != NULL)
				{
					temp2 = temp1->right->right;
					if (temp2->left == NULL)
					{
						temp3 = temp1->right;
					}
					else
					{
						temp3 = temp1->right->right;
						while (temp3->left->data != temp2->data)
						{
							temp3 = temp3->left;
						}
					}

					while (temp2->left != NULL)
					{
						temp2 = temp2->left;
					}
					
					temp1->right->data = temp2->data;
					if (temp2->right != NULL)
					{
						temp4 = temp2->right;
						delete temp2;
						temp3->left = temp4;
						return;
					}
				}
				else
				{
					if (temp1->right->right != NULL)
					{
						temp2 = temp1->right->right;
						delete temp1->right;
						temp1->right = temp2;
						return;
					}

					if (temp1->right->left != NULL)
					{
						temp2 = temp1->right->left;
						delete temp1->right;
						temp1->right = temp2;
						return;
					}
				}
			}

			//if(temp1->right->data == value && temp1->right->left == NULL && temp1->right->left)

		}
	}

	void second_third(leaf* temp1, int count_max = 1, int count_current = 1)
	{
		leaf* temp2 = root;

		if (count_current == 2)
		{
			cout << "Third smallest: " << temp1->data << endl;
		}

		if (count_current == 3)
		{
			cout << "Second smallest: " << temp1->data << endl;
		}
		
		if (temp1->left != NULL)
			second_third(temp1->left, count_max + 1, count_current + 1);
		
		if (temp1->left == NULL && temp1->right == NULL)
		{
			count_max++;
			count_max++;
		}

		if (temp1->right != NULL)
			second_third(temp1->right, count_max + 1, count_current + 1);

		count_current--;

		while (temp2->right != NULL)
		{
			temp2 = temp2->right;
		}

		if (temp1 == temp2)
		{
			cout << count_max << endl;
		}
	}

	void s_t()
	{
		second_third(root);
	}

	void print_range(leaf* temp1, int range1, int range2)
	{
		if (temp1->left != NULL)
			print_range(temp1->left, range1, range2);
		if (temp1->data > range1 && temp1->data < range2)
			cout << temp1->data << " ";
		if (temp1->right != NULL)
			print_range(temp1->right, range1, range2);
	}

	void print_r(int range1, int range2)
	{
		print_range(root, range1, range2);
	}

	void print_missing(leaf* temp1, int prev)
	{
		if (temp1->left != NULL)
		{
			print_missing(temp1->left, temp1->data);
		}

		if (temp1->data != prev - 1)
		{
			cout << prev - 1 << endl;
			print_missing(temp1, prev - 1);
		}

		if (temp1->right != NULL)
		{
			print_missing(temp1->right, temp1->data);
		}

		if (temp1->data != prev + 1)
		{
			cout << prev + 1 << endl;
			print_missing(temp1, prev + 1);
		}
	}

	void print_m()
	{
		print_missing(root, root->data);
	}

	int height(leaf* temp1)
	{
		int left = 0, right = 0;
		if (temp1->left != NULL)
			left =  1 + height(temp1->left);

		if (temp1->right != NULL)
			right = 1 + height(temp1->right);

		if (left >= right)
			return left;
		else
			return right;
	}

	int h()
	{
		return height(root);
	}

	bool is_completeBST(leaf* temp1)
	{

		if (temp1->left != NULL)
		{
			if (!is_completeBST(temp1->left))
				return false;
		}

		if (temp1->right != NULL)
		{
			if (!is_completeBST(temp1->right))
				return false;
		}

		if (temp1->right != NULL && temp1->left == NULL)
			return false;
		else
			return true;

	}



	bool is_comp()
	{
		return is_completeBST(root);
	}

};

int main()
{
	BST a;
	a.Insertion2(10);
	a.Insertion2(8);
	a.Insertion2(12);
	a.Insertion2(7);
	a.Insertion2(9);
	a.Insertion2(11);
	a.Insertion2(13);
	/*a.Insertion2(12);
	a.Insertion2(13);
	a.Insertion2(14);
	a.Insertion2(16);
	a.Insertion2(15);*/

	//a.print();
	//a.print_r(1, 7);
	//a.print_m();
	//a.s_t();

	//cout<<a.h();
	if (a.is_comp())
		cout << "Is a complete tree" << endl;
	else
		cout << "Is not a complete tree" << endl;

	return 0;
}