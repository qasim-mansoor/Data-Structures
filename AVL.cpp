#include<iostream>
using namespace std;

struct leaf
{
	int value;
	int BF;
	leaf* right;
	leaf* left;
};

class AVL
{
	leaf* root, *temp_root;
	int flag;

public:

	AVL()
	{
		root = NULL;
		flag = 0;
	}

	int Height(leaf* temp, int start = 0)
	{
		
		int left = 0, right = 0;

		if (temp == NULL)
		{
			return 0;
		}

		if (temp->left != NULL)
		{
			left = 1 + Height(temp->left, 1);
		}

		if (temp->right != NULL)
		{
			right = 1 + Height(temp->right, 1);
		}

		if (left >= right && start == 0)
			return left + 1;
		else if (right >= left && start == 0)
			return right + 1;
		else if (left > right)
			return left;
		else
			return right;
	}

	int BalanceFactor(leaf* temp)
	{
		return (Height(temp->left) - Height(temp->right));
	}

	void insertion(leaf* temp, int data)
	{
		if (temp == NULL)
		{
			temp = new leaf;
			temp->value = data;
			temp->left = NULL;
			temp->right = NULL;
			temp->BF = 0;
			root = temp;

			return;
		}

		if (data < temp->value)
		{
			if (temp->left != NULL)
			{
				insertion(temp->left, data); //from here
				temp->left->BF = BalanceFactor(temp->left);
			}
			else
			{
				temp->left = new leaf;
				temp->left->value = data;
				temp->left->left = NULL;
				temp->left->right = NULL;
				temp->left->BF = 0;
			}

			if (temp->left->BF < -1 || temp->left->BF > 1)
			{
				temp->left = rotationFinder(temp->left);
			}
		}

		if (data > temp->value)
		{
			if (temp->right != NULL)
			{
				insertion(temp->right, data);
				temp->right->BF = BalanceFactor(temp->right);
			}
			else
			{
				temp->right = new leaf;
				temp->right->value = data;
				temp->right->left = NULL;
				temp->right->right = NULL;
				temp->right->BF = 0;
			}

			if (temp->right->BF < -1 || temp->right->BF > 1)
			{
				temp->right = rotationFinder(temp->right);
			}
		}

		if (temp == root)
		{
			root->BF = BalanceFactor(root);

			if (root->BF < -1 || root->BF > 1)
			{
				root = rotationFinder(root);
			}
		}
	}

	void add_node(int value)
	{
		insertion(root, value);
	}

	leaf* successorFinder(leaf* temp)
	{
		temp = temp->right;

		while (temp->left->left != NULL)
		{
			temp = temp->left;
		}

		return temp;
	}

	void deletion(leaf* temp, int data)
	{
		if (root->value == data)
		{
			int swapper;
			if (root->left == NULL && root->right == NULL)
			{
				delete root;
				root = NULL;
			}
			else if ((root->right != NULL && root->left == NULL) || (root->left != NULL && root->right == NULL))
			{
				if (root->right != NULL)
				{
					leaf* temp1 = root;
					root = root->right;

					delete temp1;
				}
				else
				{
					leaf* temp1 = root;
					root = root->left;

					delete temp1;
				}
			}
			else
			{
				leaf* temp1 = root->right;

				while (temp1->left != NULL)
				{
					temp1 = temp1->left;
				}

				swapper = temp1->value;
				temp1->value = root->value;
				root->value = swapper;


				deletion(root->right, data);
				if (flag == 0)
				{
					root->right->BF = BalanceFactor(root->right);
					if (root->right->BF < -1 || root->right->BF > 1)
					{
						root->right = rotationFinder(root->right);
					}
				}
				else if (flag == 3)
				{
					root->right = RightRotate(root->right);
					flag = 1;
				}
			}
		}
		else
		{
			if (temp->value > data)
			{
				if (temp->left != NULL)
				{
					if (temp->left->value != data)
					{
						deletion(temp->left, data);
						cout << "flag = " << flag << " " << temp->value << endl;
						if (flag == 0)
						{
							temp->left->BF = BalanceFactor(temp->left);
							if (temp->left->BF < -1 || temp->left->BF > 1)
							{
								temp->left = rotationFinder(temp->left);
							}
						}
						else if (flag == 3)
						{
							temp->left = RightRotate(temp->left);
							flag = 1;
						}
					}
					else
					{
						if (temp->left->left == NULL && temp->left->right == NULL)
						{
							delete temp->left;
							temp->left = NULL;

							if (temp->BF == 0)
							{
								cout << "hello" << endl;
								temp->BF = BalanceFactor(temp);
								cout << "ok" << endl;
								flag = 1;
							}
							else if (temp->BF == -1)
							{
								flag = 3;
							}
						}
						else if ((temp->left->left != NULL && temp->left->right == NULL) || (temp->left->right != NULL && temp->left->left == NULL))
						{
							if (temp->left->left != NULL)
							{
								leaf* temp1 = temp->left->left;
								delete temp->left;

								temp->left = temp1;

							}
							else
							{
								leaf* temp1 = temp->left->right;
								delete temp->left;

								temp->left = temp1;

							}

							if (temp->BF == 0)
							{
								temp->BF = BalanceFactor(temp);
								flag = 1;
							}
							else if (temp->BF == -1)
							{
								flag = 3;
							}
						}
						else
						{
							leaf* temp1 = temp->left->right;
							int swapper;

							if (temp1->left == NULL)
							{
								swapper = temp1->value;
								temp1->value = temp->left->value;
								temp->left->value = swapper;
							}
							else
							{
								while (temp1->left != NULL)
								{
									temp1 = temp1->left;
								}

								swapper = temp1->value;
								temp1->value = temp->left->value;
								temp->left->value = swapper;
							}

							deletion(temp->left, data);

							if (flag == 0)
							{
								temp->left->BF = BalanceFactor(temp->left);
								if (temp->left->BF < -1 || temp->left->BF > 1)
								{
									temp->left = rotationFinder(temp->left);
								}
							}
							else if (flag == 3)
							{
								temp->left = RightRotate(temp->left);
								flag = 1;
							}
						}
					}
				}
			}

			if (temp->value < data)
			{
				if (temp->right != NULL)
				{
					if (temp->right->value != data)
					{
						deletion(temp->right, data);
						if (flag == 0)
						{
							temp->right->BF = BalanceFactor(temp->right);
							if (temp->right->BF < -1 || temp->right->BF > 1)
							{
								temp->right = rotationFinder(temp->right);
							}
						}
						else if (flag == 3)
						{
							temp->right = RightRotate(temp->right);
							flag = 1;
						}
					}
					else
					{
						if (temp->right->left == NULL && temp->right->right == NULL)
						{
							delete temp->right;
							temp->right = NULL;

							if (temp->BF == 0)
							{
								temp->BF = BalanceFactor(temp);
								flag = 1;
							}
							else if (temp->BF == 1)
							{
								flag = 3;
							}
						}
						else if ((temp->right->left != NULL && temp->right->right == NULL) || (temp->right->right != NULL && temp->right->left == NULL))
						{
							if (temp->right->left != NULL)
							{
								leaf* temp1 = temp->right->left;
								delete temp->right;

								temp->right = temp1;

							}
							else
							{
								leaf* temp1 = temp->right->right;
								delete temp->right;

								temp->right = temp1;
							}

							if (temp->BF == 0)
							{
								temp->BF = BalanceFactor(temp);
								flag = 1;
							}
							else if (temp->BF == 1)
							{
								flag = 3;
							}
						}
						else
						{
							leaf* temp1 = temp->right->right;
							int swapper;

							while (temp1->left != NULL)
							{
								temp1 = temp1->left;
							}

							swapper = temp1->value;
							temp1->value = temp->right->value;
							temp->right->value = swapper;

							deletion(temp->right, data);

							if (flag == 0)
							{
								temp->right->BF = BalanceFactor(temp->right);
								if (temp->right->BF < -1 || temp->right->BF > 1)
								{
									temp->right = rotationFinder(temp->right);
								}
							}
							else if (flag == 3)
							{
								temp->right = RightRotate(temp->right);
								flag = 1;
							}
						}
					}
				}
			}
		}

		if (temp == root)
		{
			if (flag == 0)
			{
				root->BF = BalanceFactor(root);
				if (root->BF < -1 || root->BF > 1)
				{
					root = rotationFinder(root);
				}
			}
			else if (flag == 3)
			{
				root = RightRotate(root);
				flag = 1;
			}
			return;
		}

		cout << "Number not found" << endl;
		return;

	}

	void delete_node(int data)
	{
		deletion(root, data);
	}

	leaf* rotationFinder(leaf* temp)
	{
		if (temp->BF == 2 && temp->left->BF == 1)
			return RightRotate(temp);
		if (temp->BF == -2 && temp->right->BF == -1)
			return LeftRotate(temp);
		if (temp->BF == 2 && temp->left->BF == -1)
			return LeftRightRotate(temp);
		return RightLeftRotate(temp);
	}

	leaf* LeftRotate(leaf* temp)
	{
		cout << "L" << endl;
		leaf* B = temp->right;
		leaf* D = temp->right->left;

		B->left = temp;
		temp->right = D;

		B->BF = BalanceFactor(B);
		temp->BF = BalanceFactor(temp);

		return B;
	}

	leaf* RightRotate(leaf* temp)
	{
		cout << "R" << endl;
		leaf* B = temp->left;
		leaf* D = temp->left->right;

		B->right = temp;
		temp->left = D;

		B->BF = BalanceFactor(B);
		temp->BF = BalanceFactor(temp);

		return B;
	}

	leaf* RightLeftRotate(leaf* temp)
	{
		cout << "RL" << endl;
		temp->right = RightRotate(temp->right);

		leaf* B = temp->right;
		leaf* D = temp->right->left;

		B->left = temp;
		temp->right = D;

		B->BF = BalanceFactor(B);
		temp->BF = BalanceFactor(temp);

		return B;
	}

	leaf* LeftRightRotate(leaf* temp)
	{
		cout << "LR" << endl;
		temp->left = LeftRotate(temp->left);

		leaf* B = temp->left;
		leaf* D = temp->left->right;

		B->right = temp;
		temp->left = D;

		B->BF = BalanceFactor(B);
		temp->BF = BalanceFactor(temp);

		return B;
	}

	void printdummy()
	{
		cout << root->value << "(" << root->BF << ")" << endl;
		cout << root->left->value << "(" << root->left->BF << ")" << " " << root->right->value << "(" << root->right->BF << ")" << endl;
		cout << root->left->left->value << "(" << root->left->left->BF << ")" << " " << root->left->right->value << "(" << root->left->right->BF << ")" << " " << root->right->right->value << "(" << root->right->right->BF << ")" << endl;
	}

	void p(leaf* temp)
	{
		if (temp->left != NULL)
			p(temp->left);
		cout << temp->value << " ";
		if (temp->right != NULL)
			p(temp->right);
	}

	void print()
	{
		p(root);
	}

};

int main()
{
	AVL a;
	a.add_node(100);
	a.add_node(95);
	a.add_node(120);
	a.add_node(115);
	a.add_node(130);
	a.add_node(110);
	a.add_node(118);
	a.delete_node(115);
	a.printdummy();
	

	/*a.add_node(10);
	a.add_node(5);
	

	a.print();
	cout << endl;
	a.delete_node(10);
	a.print();*/


	return 0;

}