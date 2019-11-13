#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

void print(float** a, int n, int m) {
	cout << "matrix: " << n << "x" << m << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			//if( j == m-1) cout << "\t| " << a[i][j];
			//else cout << a[i][j] << " ";
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void scan(float** matrix, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cout << "Element " << " [" << i + 1 << " , " << j + 1 << "]: ";
			cin >> matrix[i][j];
		}
}

void decision(float** matrix, int n, int m, int* swapping) {
	print(matrix, n, m);
	int i = 0;

	cout << endl;
	for (i = 0; i < n; i++) {
		cout << "x[" << swapping[i] << "] = " << matrix[i][m - 1] << " ";
		for (int j = i + 1; j < m - 1; j++)
			if (matrix[i][j] != 0) {
				if (-1 * matrix[i][j] > 0) cout << "+";
				cout << -1 * matrix[i][j] << "*x[" << swapping[j] << "] ";
			}
		cout << endl;
	}
	for (; i < m - 1; i++)
		cout << "x[" << swapping[i] << "] = any\n";

	exit(1);
}
int delete_null_line(float** matrix, int n, int m) {

	int last_line = n;

	for (int i = n - 1; i >= 0; i--) {
		bool is = true;
		for (int j = 0; j < m - 1; j++) {
			if (matrix[i][j] != 0) {
				is = false;
				break;
			}
		}

		if (is && matrix[i][m - 1] != 0) {
			cout << "INF" << endl;
			exit(101);
		}
		else if (is && matrix[i][m - 1] == 0)
			last_line -= 1;
		else
			break;
	}

	return last_line;
}

bool nullOndiag(float** a, int null_elem, int n, int m, int* swapping) {
	bool toEnd = true;
	//print(a, n, m);
	for (int j = null_elem; j < m - 1; j++) {
		for (int i = null_elem; i < n; i++) {
			//cout << "array[" << i << "][" << j << "]= " << a[i][j] << endl;
			if (a[i][j] != 0) {
				//cout << "if" << endl;
				swap(a[null_elem], a[i]);
				//print(a, n, m);
				if (null_elem != j) {
					//cout << "wrap if" << endl;
					swap(swapping[null_elem], swapping[j]);
					for (int k = 0; k < n; k++)
						swap(a[k][null_elem], a[k][j]);
					//print(a, n, m);
				}
				toEnd = false;
				break;
			}
			//cout << "array[" << i << "][" << j << "]= " << a[i][j] << endl;
		}
		if (!toEnd)
			break;
	}
	if (toEnd)
		return true;
	return false;
}
void gauss(float** matrix, int n, int m, int* swapping) {
	float  tmp;
	for (int i = 0; i < n; i++)
	{
		if (matrix[i][i] == 0)
			if (nullOndiag(matrix, i, n, m, swapping))
				decision(matrix, delete_null_line(matrix, n, m), m, swapping);


		tmp = matrix[i][i];
		//print(matrix, n, m);

		for (int j = m; j >= i; j--)
			matrix[i][j] /= tmp;

		for (int j = 0; j < n; j++)
		{
			if (i != j) {
				tmp = matrix[j][i];
				//cout << "temp= " << tmp << ", j= " << j << ", i= " << i << endl;
				for (int k = m - 1; k >= 0; k--)
					matrix[j][k] -= tmp * matrix[i][k];
			}
		}

	}

	int last_line = delete_null_line(matrix, n, m);
	cout << last_line << endl;
	decision(matrix, last_line, m, swapping);
}

int main() {

	int i, j, n, m;
	//создаем массив
	cout << "Number of equations: ";
	cin >> n;
	cout << "Number of variables: ";
	cin >> m;
	m += 1;

	int* swapping = new int[m];
	for (i = 0; i < m; i++) swapping[i] = i;
	float** matrix = new float* [n];
	for (i = 0; i < n; i++)
		matrix[i] = new float[m];

	//инициализируем
	scan(matrix, n, m);
	print(matrix, n, m);
	cout << "RESULT" << endl;
	gauss(matrix, n, m, swapping);
	print(matrix, n, m);

	delete[] matrix;
	system("pause");
	return 0;
}
