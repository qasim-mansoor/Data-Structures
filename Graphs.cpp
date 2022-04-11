#include<iostream>
using namespace std;

struct adjacent
{
	int data;
	adjacent* next;
};

struct node
{
	int data;
	int flag;
	adjacent* adjacent_nodes;
	node* next_node;
};

class stack
{
public:

	adjacent* top;

	stack()
	{
		top = NULL;
	}

	void push(int value)
	{
		adjacent* temp;

		if (top == NULL)
		{
			top = new adjacent;
			top->data = value;
			top->next = NULL;
			return;
		}

		temp = top;

		top = new adjacent;
		top->data = value;
		top->next = temp;
		return;
	}

	int pop()
	{
		adjacent* temp;
		int popper;

		if (top == NULL)
		{
			cout << "Empty stack" << endl;
			return 0;
		}

		if (top->next == NULL)
		{
			popper = top->data;
			delete top;
			top = NULL;

			return popper;
		}

		temp = top;
		top = top->next;
		popper = temp->data;

		delete temp;
		return popper;
	}

	bool is_empty()
	{
		if (top == NULL)
			return true;
		else
			return false;
	}

	int peek()
	{
		return top->data;
	}
};

class queue
{
public:

	adjacent* front;

	queue()
	{
		front = NULL;
	}

	void enqueue(int value)
	{
		adjacent* temp;
		temp = front;

		if (front == NULL)
		{
			front = new adjacent;
			front->data = value;
			front->next = NULL;
			return;
		}

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = new adjacent;
		temp->next->data = value;
		temp->next->next = NULL;
		
	}

	int dequeue()
	{
		adjacent* temp;
		int ret_val;

		if (front == NULL)
		{
			cout << "Empty queue" << endl;
			return 0;
		}

		if (front->next == NULL)
		{
			ret_val = front->data;
			delete front;
			front = NULL;
			return ret_val;
		}

		temp = front;
		ret_val = temp->data;
		front = front->next;


		delete temp;
		return ret_val;
	}

	bool isempty()
	{
		if (front == NULL)
			return true;
		else
			return false;
	}

	int peek()
	{
		return front->data;
	}
};

class graph
{
	node* head;
	stack s;
	queue q;

public:

	graph()
	{
		head = NULL;
	}

	void add_node(int value)
	{
		node* temp;
		temp = head;

		if (head == NULL)
		{
			head = new node;
			head->data = value;
			head->adjacent_nodes = NULL;
			head->next_node = NULL;
			head->flag = 0;

			return;
		}

		while (temp->next_node != NULL)
		{
			temp = temp->next_node;
		}

		temp->next_node = new node;
		temp->next_node->data = value;
		temp->next_node->adjacent_nodes = NULL;
		temp->next_node->next_node = NULL;
		temp->next_node->flag = 0;

		return;
	}

	void add_adjacency(int value, int adj)
	{
		node* temp;
		adjacent* temp1;

		temp = head;

		if (head == NULL)
		{
			cout << "No node with value: " << value << " found" << endl;
			return;
		}

		while (temp->data != value)
		{
			temp = temp->next_node;
		}

		if (temp->adjacent_nodes == NULL)
		{
			temp->adjacent_nodes = new adjacent;
			temp->adjacent_nodes->data = adj;
			temp->adjacent_nodes->next = NULL;

			return;
		}

		temp1 = temp->adjacent_nodes;

		while (temp1->next != NULL)
		{
			temp1 = temp1->next;
		}

		temp1->next = new adjacent;
		temp1->next->data = adj;
		temp1->next->next = NULL;
		return;

	}

	void print()
	{
		node* temp;
		adjacent* temp1;

		temp = head;

		while (temp != NULL)
		{
			temp1 = temp->adjacent_nodes;
			cout << temp->data << ": ";
			while (temp1 != NULL)
			{
				cout << temp1->data << " ";
				temp1 = temp1->next;
			}

			cout << endl;
			temp = temp->next_node;
		}
		cout << endl;
	}

	void set_flag(int value)
	{
		node* temp = head;

		while (temp != NULL)
		{
			if (temp->data == value)
			{
				temp->flag = 1;
				return;
			}
			temp = temp->next_node;
		}
	}

	bool check_flag(int value)
	{
		node* temp = head;

		while (temp != NULL)
		{
			if (temp->data == value)
			{
				return temp->flag;
			}
			temp = temp->next_node;
		}
	}

	node* reach_node(int value)
	{
		node* temp = head;

		while (temp != NULL)
		{
			if (temp->data == value)
			{
				return temp;
			}
			temp = temp->next_node;
		}
	}

	void reset_flags()
	{
		node* temp;

		temp = head;

		while (temp != NULL)
		{
			temp->flag = 0;
			temp = temp->next_node;
		}
	}

	void depth_traversal()
	{
		reset_flags();
		node* temp;
		adjacent* temp1;
		int move_on;

		temp = head;

		s.push(temp->data);
		set_flag(temp->data);
		
		while (!s.is_empty())
		{
			move_on = 0;

			temp1 = temp->adjacent_nodes;

			if (temp1 == NULL)
			{
				temp = reach_node(s.pop());
				cout << temp->data << " ";

				if (s.is_empty())
					return;

				temp = reach_node(s.peek());
			}
			else
			{
				while (check_flag(temp1->data))
				{
					if (temp1->next == NULL)
					{
						move_on = 1;
						break;
					}
					temp1 = temp1->next;
				}
				
				if (!move_on)
				{
					temp = reach_node(temp1->data);
					s.push(temp->data);
					set_flag(temp->data);
				}
				else
				{

					temp = reach_node(s.pop());
					cout << temp->data << " ";

					if (s.is_empty())
						return;

					temp = reach_node(s.peek());
				}
			}
		}
	}

	void breadth_traversal()
	{
		reset_flags();
		node* temp;
		adjacent* temp1;

		temp = head;
		
		q.enqueue(temp->data);

		while (!q.isempty())
		{
			temp1 = temp->adjacent_nodes;
			while (temp1 != NULL)
			{
				if (!check_flag(temp1->data))
				{
					q.enqueue(temp1->data);
					set_flag(temp1->data);
				}
				
				temp1 = temp1->next;
			}
			
			cout << q.dequeue() << " ";
			
			if (!q.isempty())
			{
				temp = reach_node(q.peek());
			}
		}
	}
};

int main()
{
	int node, adj, choice;
	graph a;

	/*while (true)
	{
		cout << "1. Add node" << endl;
		cout << "2. Add adjacency" << endl;
		cout << "3. Print" << endl;
		cout << "4. Breadth Traversal" << endl;
		cout << "5. End" << endl;
		cin >> choice;
		cout << endl;

		if (choice == 1)
		{
			cout << "Enter value of node: ";
			cin >> node;
			a.add_node(node);
			cout << endl;
		}
		else if (choice == 2)
		{
			cout << "Enter node: ";
			cin >> node;
			cout << "Enter adjacent number: ";
			cin >> adj;

			a.add_adjacency(node, adj);
			cout << endl;
		}
		else if (choice == 3)
		{
			a.print();
			cout << endl;
		}
		else if (choice == 4)
		{
			a.breadth_traversal();
			cout << endl;
		}
		else
		{
			break;
		}
	}*/

	a.add_node(1);
	a.add_adjacency(1, 2);
	a.add_adjacency(1, 3);
	a.add_adjacency(1, 5);

	a.add_node(2);
	a.add_adjacency(2, 4);
	a.add_adjacency(2, 5);

	a.add_node(3);
	a.add_adjacency(3, 5);
	a.add_adjacency(3, 6);

	a.add_node(4);
	a.add_adjacency(4, 5);
	a.add_adjacency(4, 8);

	a.add_node(5);
	a.add_adjacency(5, 6);

	a.add_node(6);
	a.add_adjacency(6, 7);
	a.add_adjacency(6, 9);

	a.add_node(7);
	a.add_adjacency(7, 4);
	a.add_adjacency(7, 5);
	a.add_adjacency(7, 8);

	a.add_node(8);

	a.add_node(9);
	a.add_adjacency(9, 8);
	a.add_adjacency(9, 7);

	a.print();
	a.breadth_traversal();
	cout << endl;
	a.depth_traversal();


	return 0;
}