#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;
};

class stack
{
	node* top;

public:
	stack()
	{
		top = NULL;
	}

	void push(int value)
	{
		if (top == NULL)
		{
			top = new node;
			top->data = value;
			top->next = NULL;
			return;
		}

		node* temp = top;
		top = new node;
		top->data = value;
		top->next = temp;
	}

	void pop()
	{
		if (top == NULL)
		{
			cout << "Stack empty" << endl;
			return;
		}
		if (top->next == NULL)
		{
			delete top;
			top = NULL;
			return;
		}

		node*temp = top;
		top = top->next;
		delete temp;
	}

	int peek()
	{
		if (top == NULL)
		{
			cout << "Stack empty" << endl;
			return 0;
		}

		return top->data;
	}

	bool isempty()
	{
		if (top == NULL)
			return true;
		else
			return false;
	}

	void print()
	{
		node* temp = top;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

//int main()
//{
//	stack p;
//
//	p.push(10);
//	p.push(15);
//	p.push(3);
//	p.push(5);
//	p.push(1);
//	p.push(7);
//	p.push(9);
//
//	p.print();
//
//	p.pop();
//
//	p.print();
//
//	if (p.isempty())
//		cout << "empty" << endl;
//
//	p.pop();
//	p.print();
//	p.pop();
//	p.print();
//	p.pop();
//	p.print();
//	p.pop();
//	p.print();
//	p.pop();
//	p.print();
//	p.pop();
//	p.print();
//
//	if (p.isempty())
//		cout << "empty" << endl;
//
//	p.push(12);
//	p.print();
//
//	return 0;
//}