#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

void Create(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);
	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
		if (i < rowCount - 1)
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Input(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << "a[" << i << "][" << j << "] = ";
	cin >> a[i][j];
	if (j < colCount - 1)
		Input(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Input(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl;
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl << endl;
}

int Zero(int** a, const int k, const int i, const int j, int s)
{
	if (a[i][j] == 0)
		s++;
	if (i < k - 1)
		Zero(a, k, i + 1, j, s);
	else
		return s;
}
int Calck(int** a, const int k, const int n, int j, int s)
{
	if (Zero(a, k, 0, j, 0) > 0)
		s++;
	if (j < n - 1)
		Calck(a, k, n, j + 1, s);
	else
		return n - s;
}
int Chart(int** a, const int n, const int i, int j, int sum)
{
	if (a[i][j] > 0 && a[i][j] % 2 == 0)
		sum += a[i][j];
	if (j < n - 1)
		Chart(a, n, i, j + 1, sum);
	else
		return sum;
}
void Change(int** a, const int row1, const int row2, const int colCount, int tmp, int j)
{
	tmp = a[row1][j];
	a[row1][j] = a[row2][j];
	a[row2][j] = tmp;
	if (j < colCount - 1)
		Change(a, row1, row2, colCount, tmp, j + 1);
}
void Replace(int** a, const int k, const int n, int i1, int i2)
{
	if (Chart(a, n, i1, 0, 0) < Chart(a, n, i2, 0, 0))
		Change(a, i1, i2, n, 0, 0);
	if (i1 < k - 1)
		Replace(a, k, n, i1 + 1, i2);
	else
		if (i2 < k - 1)
			Replace(a, k, n, i1, i2 + 1);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));

	int Low = -20;
	int High = 20;
	int k, n;

	cout << "rowCount = "; cin >> k;
	cout << "colCount = "; cin >> n;

	int** a = new int* [k];
	for (int i = 0; i < k; i++)
		a[i] = new int[n];

	Create(a, k, n, Low, High, 0, 0);
	Input(a, k, n, 0, 0);

	cout << "a[" << k << "][" << n << "] = " << endl;

	Print(a, k, n, 0, 0);

	cout << "Number of matrices without zeros: " << Calck(a, k, n, 0, 0) << endl;
	cout << endl;

	Replace(a, k, n, 0, 0);

	cout << "Matrix arranged according to the growth of characteristics: " << endl;
	cout << "a[" << k << "][" << n << "] = " << endl;

	Print(a, k, n, 0, 0);

	for (int i = 0; i < k; i++)
		delete[] a[i];
	delete[] a;

	return 0;
}
