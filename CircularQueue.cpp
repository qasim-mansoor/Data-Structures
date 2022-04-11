#include<iostream>
using namespace std;

class queue
{
	int *arr, *front, *rear, num_of_elements, arr_size;

public:
	queue()
	{
		cout<<"Enter size: ";
		cin>>arr_size;
		arr = new int[arr_size];
		rear = NULL;
		front = NULL;
		num_of_elements = 0;
	}

	void Enqueue()
	{
		if(rear == NULL)
		{
			cout<<"Enter value: ";
			front = rear = arr;
			cin>>*rear;
			num_of_elements++;
			return;
		}

		if(rear == (arr+(arr_size-1)) && front == arr || rear+1 == front)
		{
			cout<<"FUll"<<endl;
			return;
		}

		if(rear == arr+(arr_size-1))
			rear = arr;
		else
			rear++;

		cout<<"Enter value: ";
		cin>>*arr;
		num_of_elements++;
	}

	void Dequeue()
	{
		if(front == NULL)
		{
			cout<<"Empty"<<endl;
			return;
		}

		if(front == rear)
		{
			front = NULL;
			rear = NULL;
			num_of_elements--;
			return;
		}

		if(front == arr+(arr_size-1))
			front = arr;
		else
			front++;

		num_of_elements--;
	}

	void Print()
	{
		cout<<"List: "<<endl;
		for(int i=0;i<arr_size;i++)
		{
			cout<<*front<<" ";
			
			if(front == arr+(arr_size-1))
				front = arr;
			else 
				front++;
		}
		cout<<endl;
	}
};

int main()
{

