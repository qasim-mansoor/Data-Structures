#include<iostream>
#include<math.h>
using namespace std;


int digit(int n)
{
	int count = 0;

	if (n == 0)
		return 1;

	while (n != 0)
	{
		n = n / 10;
		count++;
	}

	return count;
}

int flag = 0;

long int DivideAndConquer(int a, int b)
{
	int n;

	if (a < 10 && b < 10)
		return a * b;

	if (a > b)
		n = digit(a);
	else
		n = digit(b);

	int ah, al, aln, bh, bl, bln, an, bn;

	an = digit(a);
	bn = digit(b);

	if (an > bn)
	{
		ah = a / pow(10, n - (n / 2));
		aln = pow(10, n - digit(ah));
		al = a % aln;

		bh = b / pow(10, n - (n / 2));
		bln = pow(10, n - digit(ah));
		bl = b % bln;
	}
	else
	{
		bh = b / pow(10, n - (n / 2));
		bln = pow(10, n - digit(bh));
		bl = b % bln;

		ah = a / pow(10, n - (n / 2));
		aln = pow(10, n - digit(bh));
		al = a % aln;
	}

	long int w, x, y, z;

	w = DivideAndConquer(ah, bh);
	x = DivideAndConquer(ah, bl);
	y = DivideAndConquer(al, bh);
	z = DivideAndConquer(al, bl);

	if ((n % 2 != 0 && an == bn) || an + bn == 9 && abs(an - bn) == 1)
		n++;

	return w * pow(10, n) + ((x + y)*pow(10, n - (n / 2))) + z;
}

int main()
{
	int num1, num2;

	cout << "Enter the first number: ";
	cin >> num1;
	cout << "Enter the second number: ";
	cin >> num2;

	cout << endl << "Product: " << DivideAndConquer(num1, num2) << endl;

	return 0;
}