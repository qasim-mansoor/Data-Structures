#include<iostream>
#include<string>

using namespace std;

void string_rev(string a, string b = "", int index = 0)
{
	string k;

	if(a[index] == '\0')
		return;

	if(a[index] != ' ')
	{
		k = a[index];
		b = b+k;
		string_rev(a,b,index+1);
	}
	else
		string_rev(a,"",index+1);

	if(a[index+1] == '\0' || a[index+1] == ' ')
		cout<<b<<" ";
}



int main()
{
	string p = "It is raining today";

	string_rev(p);
	system("pause");
	return 0;
}