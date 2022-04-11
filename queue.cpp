#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;
};

class queue
{
	node* front;

public:
	queue()
	{
		front = NULL;
	}

	void enqueue(int value)
	{
		if (front == NULL)
		{
			front = new node;
			front->data = value;
			front->next = NULL;
			return;
		}

		node* temp = front;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = new node;
		temp->next->data = value;
		temp->next->next = NULL;
	}

	void dequeue()
	{
		if (front == NULL)
		{
			cout << "Stack empty" << endl;
			return;
		}
		if (front->next == NULL)
		{
			delete front;
			front = NULL;
			return;
		}

		node*temp = front;
		front = front->next;
		delete temp;
	}

	int peek()
	{
		if (front == NULL)
		{
			cout << "Stack empty" << endl;
			return 0;
		}

		return front->data;
	}

	bool isempty()
	{
		if (front == NULL)
			return true;
		else
			return false;
	}

	void print()
	{
		node* temp = front;
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
//	queue p;
//
//	p.enqueue(10);
//	p.enqueue(15);
//	p.enqueue(3);
//	p.enqueue(5);
//	p.enqueue(1);
//	p.enqueue(7);
//	p.enqueue(9);
//
//	p.print();
//
//	p.dequeue();
//
//	p.print();
//
//	if (p.isempty())
//		cout << "empty" << endl;
//
//	p.dequeue();
//	p.print();
//	p.dequeue();
//	p.print();
//	p.dequeue();
//	p.print();
//	p.dequeue();
//	p.print();
//	p.dequeue();
//	p.print();
//	p.dequeue();
//	p.print();
//
//	if (p.isempty())
//		cout << "empty" << endl;
//
//	p.enqueue(12);
//	p.print();
//
//	return 0;
//}