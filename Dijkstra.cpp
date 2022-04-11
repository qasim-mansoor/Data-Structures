#include<iostream>
using namespace std;

struct tableEntry
{
	int value;
	int subscript;
	bool checked;
};

class dijistra
{
	tableEntry current_table[9][9];
	int graph_matrix[9][9];
	int columns_visited[9];
	int table_rows;

public:

	void set_graph_matrix(int graph[9][9])
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				graph_matrix[i][j] = graph[i][j];
			}
		}
	}

	void print_graph_matrix()
	{
		cout << "Input Matrix: " << endl;
		for (int i = 0; i < 9; i++)
		{
			cout << "| ";
			for (int j = 0; j < 9; j++)
			{
				cout << graph_matrix[i][j] << " ";
			}
			cout << "|" << endl;
		}
		cout << endl;
	}

	int check_smallest(int counter)
	{
		int smallest, smallest_index;
		for (int i = 0; i < 9; i++)
		{
			if (current_table[counter][i].value == false)
			{
				smallest = current_table[counter][i].value;
				smallest_index = i;
				break;
			}
		}

		int i;
		for (i = 0; i < 9; i++)
		{
			if (current_table[counter][i].checked == false)
			{
				if (current_table[counter][i].value != 0)
				{
					if (smallest == 0)
					{
						smallest = current_table[counter][i].value;
						smallest_index = i;
					}
					else if (smallest > current_table[counter][i].value)
					{
						smallest = current_table[counter][i].value;
						smallest_index = i;
					}
				}
			}
		}

		current_table[counter][smallest_index].checked = true;
		return smallest_index;
	}

	void print_table(int temp, int counter)
	{
		cout << "Iteration " << counter + 1 << ":" << endl << endl;
		cout << "  | \t  0\t  1\t  2\t  3\t  4\t  5\t  6\t  7\t  8\t" << endl;
		cout << "__|______________________________________________________________________________" << endl;
		for (int i = 0; i <= counter; i++)
		{
			cout << columns_visited[i] << " | \t";
			for (int j = 0; j < 9; j++)
			{
				/*cout << current_table[i][j].value << "(" << current_table[i][j].subscript << ")";
				if (current_table[i][j].checked)
					cout << "*";*/

				if (current_table[i][j].checked)
					cout << "|" << current_table[i][j].value << "(" << current_table[i][j].subscript << ")|";
				else
					cout << " " << current_table[i][j].value << "(" << current_table[i][j].subscript << ") ";


				cout << "\t";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}

	void algorithm(int start, int end)
	{
		int counter = 0;
		int old_temp = start;
		int temp = start;

		columns_visited[counter] = temp;

		for (int i = 0; i < 9; i++)
		{
			current_table[counter][i].value = graph_matrix[i][temp];
			if(i == temp)
				current_table[counter][i].checked = true;
			else
				current_table[counter][i].checked = false;
			current_table[counter][i].subscript = temp;
		}
		
		temp = check_smallest(counter);
		print_table(old_temp, counter);
		old_temp = temp;

		while (temp != end)
		{
			counter++;

			columns_visited[counter] = temp;

			for (int i = 0; i < 9; i++)
			{
				current_table[counter][i] = current_table[counter - 1][i];
			}

			for (int i = 0; i < 9; i++)
			{
				if (graph_matrix[i][temp] != 0 && current_table[counter][i].checked != true &&
					(current_table[counter][i].value == 0 || (graph_matrix[i][temp] + current_table[counter][temp].value) < current_table[counter][i].value))
				{
					current_table[counter][i].value = graph_matrix[i][temp] + current_table[counter][temp].value;
					current_table[counter][i].subscript = temp;
				}
			}

			temp = check_smallest(counter);
			print_table(old_temp, counter);

			old_temp = temp;
		}

		counter++;
		columns_visited[counter] = temp;

		for (int i = 0; i < 9; i++)
		{
			current_table[counter][i] = current_table[counter - 1][i];
		}

		for (int i = 0; i < 9; i++)
		{
			if (graph_matrix[i][temp] != 0 && current_table[counter][i].checked != true &&
				(current_table[counter][i].value == 0 || (graph_matrix[i][temp] + current_table[counter][temp].value) < current_table[counter][i].value))
			{
				current_table[counter][i].value = graph_matrix[i][temp] + current_table[counter][temp].value;
				current_table[counter][i].subscript = temp;
			}
		}

		print_table(temp, counter);
		table_rows = counter;

	}

	void pathfinder(int start, int end)
	{
		int path[9], i = 0;
		cout << "Length of smallest path: " << current_table[table_rows][end].value << endl;
		cout << "Smallest path: ";

		while (end != start)
		{
			path[i] = end;
			end = current_table[table_rows][end].subscript;
			i++;
		}

		path[i] = start;

		for (int j = i; j >= 0 ; j--)
		{
			cout << path[j];
			if (j != 0)
				cout << " -> ";
		}

		cout << endl;
	}

};

int main()
{
	dijistra a;
	int start, end;
	int matrix[9][9] = { {0,3,0,2,0,0,0,0,4},
						 {3,0,0,0,0,0,0,4,0},
						 {0,0,0,6,0,1,0,2,0},
						 {2,0,6,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0,8},
						 {0,0,1,0,0,0,8,0,0},
						 {0,0,0,0,0,8,0,0,0},
						 {0,4,2,0,0,0,0,0,0},
						 {4,0,0,0,8,0,0,0,0} };

	a.set_graph_matrix(matrix);
	a.print_graph_matrix();

	cout << "Find path from: ";
	cin >> start;
	cout << "Find path to: ";
	cin >> end;

	cout << endl;
	a.algorithm(start, end);
	a.pathfinder(start, end);

	system("pause");
	return 0;
}