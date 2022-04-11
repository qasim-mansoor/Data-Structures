#include<iostream>
using namespace std;

int* MergeS(int size, int* arr)
{
	int *L, *R, L_size, R_size;

	if (size == 1)
		return arr;


	L_size = size / 2;
	L = new int[L_size];
	R_size = size - L_size;
	R = new int[R_size];

	for (int i = 0; i < L_size; i++)
	{
		L[i] = arr[i];
	}

	for (int i = 0; i < R_size; i++)
	{
		R[i] = arr[i + L_size];
	}

	L = MergeS(L_size, L);
	R = MergeS(R_size, R);

	int L_index = 0;
	int R_index = 0;

	for (int i = 0; i < size; i++)
	{
		if (R_index == R_size)
		{
			arr[i] = L[L_index];
			L_index++;
		}
		
		else if (L_index == L_size)
		{
			arr[i] = R[R_index];
			R_index++;
		}

		else if (L[L_index] < R[R_index])
		{
			arr[i] = L[L_index];
			L_index++;
		}

		else if (L[L_index] > R[R_index])
		{
			arr[i] = R[R_index];
			R_index++;
		}

		else if (L[L_index] == R[R_index])
		{
			arr[i] = L[L_index];
			L_index++;
		}
	}

	return arr;
}


int main()
{
	int size, *arr, *sorted;

	cout << "Enter size: ";
	cin >> size;

	arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Value " << i + 1 << " :";
		cin >> arr[i];
	}

	arr = MergeS(size, arr);

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	system("pause");
	return 0;
}