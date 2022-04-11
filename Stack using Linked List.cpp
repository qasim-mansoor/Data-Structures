#include <iostream> 
using namespace std; 

struct node
{
	int data;
	node* next;
};

int Max = 10;
static int stackSize = 0;

class LinkedList
{
	
	private:
    node *head;
    node *tail;
    
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void printList() 
	{
		if(head == NULL)
			cout<<"The stack is empty"<<endl;
		else
		{
			node * current = head;

			while (current != NULL) 
			{
				cout << current->data <<endl;
				current = current->next;
			}
		}
    }
    
    //inserting new Node at the head
    void push(int value) 
	{
		if(stackSize==Max)
			cout<<"The stack is full"<<endl;
		else if(head == NULL)
		{
			node *temp = new node;
			temp->data = value;
			temp->next = NULL;
			head = temp;
            tail = temp;
			stackSize++;
		}
		else
		{
			node * new_node;
			new_node = new node;
				
			new_node->data = value;
			new_node->next = head;
				
			head = new_node;
			stackSize++;
		}
	}
  
	//Deleting first item of the list
	int pop() 
	{
		int retval = 0;

		if(head == NULL)
			cout<<"The list is empty"<<endl;

		else if(head->next == NULL)
		{
			retval = head->data;
			delete head;
			head = NULL;
			tail = NULL;
			stackSize--;
			return retval;
		}
		
		else
		{
			node * next_node = NULL;

			next_node = head->next;
			retval = head->data;
			delete head;
			head = next_node;
			stackSize--;
			return retval;
		}   
	}

	void peek()
	{
		if(head == NULL)
			cout<<"The stack is empty"<<endl;
		else
			cout<<"The top-most value is: "<<head->data<<endl;
	}
	

	bool isempty()
	{
		if(stackSize == 0)
			return true;
		else
			return false;
	}

	bool isfull()
	{
		if(stackSize==Max)
			return true;
		else 
			return false;
	}

};



int main() 
{ 
	LinkedList L;
	int choice,data;
	do
	{
		cout<<"Please choose an option below by entering the corresponding number"<<endl;
		cout<<"1. Add a value to the stack"<<endl;
		cout<<"2. Remove a value from the stack"<<endl;
		cout<<"3. Check if the stack is full"<<endl;
		cout<<"4. Check if the stack is empty"<<endl;
		cout<<"5. Check the top-most value"<<endl;
		cout<<"6. Print all values"<<endl;
		cout<<"7. Exit Program"<<endl;
		cout<<"Choice: ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
		case 1:
			cout<<"Please enter an integer to add to the list: ";
			cin>>data;
			L.push(data);
			break;
		case 2:
			L.pop();
			cout<<"Data removed"<<endl;
			break;
		
		case 3:
			if(L.isfull())
				cout<<"The stack is full"<<endl;
			else
				cout<<"The stack is not full"<<endl;
			break;
		case 4:
			if(L.isempty())
				cout<<"The stack is empty"<<endl;
			else
				cout<<"The stack is not empty"<<endl;
			break;
		case 5:
			L.peek();
			break;
		case 6:
			L.printList();
			break;
		case 7:
			break;
		default:
			cout<<"Invalid selection. Please re-enter."<<endl;
		}
		cout<<endl;
	}while(choice!=7);
  
	system("pause");
    return 0; 
}  


