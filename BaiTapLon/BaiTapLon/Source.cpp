#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;


void nhap(int a[100][100], int d, int c) {
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			cin >> a[i][j];
		}
	}
}
void xuat(int a[100][100], int d, int c) {
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

int xep(int a[100][100], int d, int c) { // tìm phần tử lớn nhất trong hàng  

	int max = 0;
	for (int i = 0; i < c; i++) {
		if (max < a[0][i]) {
			max = a[0][i];
		}
	}
	return max;

}

int main()
{
	int a[100][100];
	int d, c;

	cout << "Nhap so dong: ";
	cin >> d;
	cout << "Nhap so cot: ";
	cin >> c;

	nhap(a, d, c);
	xuat(a, d, c);


	_getch();
	return 0;
}
