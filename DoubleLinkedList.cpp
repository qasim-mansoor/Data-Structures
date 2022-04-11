#include<iostream>
using namespace std;

struct node
{
	int data;
	node* next;
	node* prev;
};

class DLL
{
	node* head;
	node* temp;

public:
	DLL()
	{
		head = NULL;
		temp = NULL;
	}

	void Insertion()
	{
		int value, choice;
		cout<<"\t1. Add value at the start of the list"<<endl;
		cout<<"\t2. Add value at the end of the list"<<endl;
		cout<<"\tChoice: ";
		cin>>choice;
		cout<<endl;
		cout<<"\t\tEnter value: ";
		cin>>value;
		cout<<endl;

		if(head == NULL)
		{
			head = new node;
			head->data = value;
			head->next = NULL;
			head->prev = NULL;
			return;
		}

		switch(choice)
		{
		case 1:
			temp = new node;
			temp->data = value;
			temp->next = head;
			temp->prev = NULL;
			head->prev = temp;

			head = temp;
			break;

		case 2:
			temp = head;
			node* temp1;
			while(temp->next!=NULL)
			{
				temp = temp->next;
			}

			temp1 = new node;
			temp1->data = value;
			temp1->next = NULL;
			temp1->prev = temp;
			temp->next = temp1;
			break;
		}
		return;
	}

	void Deletion()
	{
		int value, count;
		node* temp1;
		count = 0;
		cout<<"\tEnter the value to delete: ";
		cin>>value;

		temp = head;
		temp1 = NULL;

		while(temp!=NULL)
		{
			if(temp->data == value)
			{
				temp1 = temp;
				count++;
			}
			temp = temp->next;
		}

		if(count == 0)
		{
			cout<<"\t\tNo value found"<<endl;
			return;
		}

		if(count == 1)
		{
			cout<<"\t\tValue deleted"<<endl;
			cout<<endl;
			if(temp1 == head)
			{
				head = temp1->next;
				delete temp1;
				temp1 = NULL;
				return;
			}

			if(temp1->next == NULL)
			{
				temp1->prev->next = NULL;
				delete temp1;
				temp1 = NULL;
				return;
			}

			temp1->next->prev = temp1->prev;
			temp1->prev->next = temp1->next;
			delete temp1;
			temp1 = NULL;
			return;
		}

		if(count > 1)
		{
			int instance;
			cout<<"\t\t"<<count<<" instances of the value found"<<endl;
			cout<<"\t\tEnter 1 to delete the first instance of the value, 2 to delete the second instance, etc."<<endl;
			cout<<"\t\tChoice: ";
			cin>>instance;

			while(instance > count)
			{
				cout<<"\t\t\tThe entered instance exceeds the total instances. Please re-enter: ";
				cin>>instance;
			}

			temp = head;
			count = 0;

			while(temp != NULL)
			{
				if(temp->data == value)
				{
					count++;
					if(count == instance)
					{
						break;
					}
				}
				temp = temp->next;
			}

			cout<<"\t\t\tValue deleted"<<endl;
			cout<<endl;
			if(temp == head)
			{
				head = temp->next;
				delete temp;
				temp = NULL;
				return;
			}

			if(temp->next == NULL)
			{
				temp->prev->next = NULL;
				delete temp;
				temp = NULL;
				return;
			}

			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
			temp = NULL;
		}

		return;
	}



	void Print()
	{
		cout<<"\tList: ";
		temp = head;
		while(temp != NULL)
		{
			cout<<temp->data<<" ";
			temp = temp->next;
		}

		cout<<endl<<endl;
	}

	void Printback()
	{
		cout<<"\tList: ";
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		while(temp != NULL)
		{
			cout<<temp->data<<" ";
			temp = temp->prev;
		}

		cout<<endl<<endl;
	}
};

int main()
{
	DLL a;
	int input;
	
	do
	{
		cout<<"1. Add a new value"<<endl;
		cout<<"2. Print list"<<endl;
		cout<<"3. Delete a value"<<endl;
		cout<<"4. Print backwards"<<endl;
		cout<<"5. Exit program"<<endl;
		cout<<"Choice: ";
		cin>>input;
		cout<<endl;

		switch(input)
		{
		case 1:
			a.Insertion();
			break;
		case 2:
			a.Print();
			break;
		case 3:
			a.Deletion();
			break;
		case 4:
			a.Printback();
			break;
		case 5:
			cout<<"Exiting program"<<endl;
			break;
		default:
			cout<<"Invalid input"<<endl;
			break;
		}
	}while(input!=5);
	
	system("pause");
	return 0;
}




		


