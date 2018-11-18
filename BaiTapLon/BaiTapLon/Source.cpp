#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS
template<typename T> static void read(T &S) { char K[1000009]; scanf("%s", &K); S = K; }
using namespace std;

//int tau[1000][1000];
int bai[1000][1000];
int tam[1000][1000];
//int row,col;
vector<string> dataInit(7);
int row;
int col;
int numContainer;
int temp;
int numStep = 0;
vector<vector<int>> tau(1000, vector<int>(1000));

int MakeNumberFromString(string str) {
	int res = 0;
	for (int i = 0; i < str.size(); i++)
		if (str[i] >= '0'&&str[i] <= '9')
			res = res * 10 + (str[i] - '0');
	return res;
}

void Nhap() {
	cin >> row >> col;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			cin >> tau[i][j];
}

void ShowTau() {
	cout << "gia tri cua tau" << endl;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (tau[i][j] == -1)
				cout << "-  ";
			else
				cout << tau[i][j] << "  ";
		}
		cout << endl;
	}
}

void WriteLocationOfShip() {
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (tau[i][j] == -1)
				cout << "-  ";
			else
				cout << tau[i][j] << " --> " << "[" << i << "," << j << "]";
		}
		cout << endl;
	}
}

void ShowData() {
	cout << "chieu cao = " << row << endl;
	cout << "chieu rong = " << col << endl;
	cout << "so container = " << numContainer << endl;
	cout << "so bai tam = " << temp << endl;
}

void Init() {
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			bai[i][j] = -1;
		}
	}
	for (int i = 0; i < 7; i++) {
		read(dataInit[i]);
	}
	row = MakeNumberFromString(dataInit[1]);
	col = MakeNumberFromString(dataInit[2]);
	numContainer = MakeNumberFromString(dataInit[3]);
	temp = MakeNumberFromString(dataInit[5]);
	for (int i = 0; i < col; i++) {
		string rac; read(rac); // doc cot
	}
	for (int i = 1; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			string str; read(str); // doc dong
			if (j == 0)continue;
			if (str == "x") {
				tau[i][j] = -1;
			}
			else {
				tau[i][j] = MakeNumberFromString(str);
			}
		}
	}
}

void ShowBai() {
	cout << "value Bai" << endl;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (bai[i][j] == -1)
				cout << "-  ";
			else
				cout << bai[i][j] << "  ";
		}
		cout << endl;
	}
}

int GetValueTopCol(int idCol, bool isTau) {
	int idRow = 1;
	if (isTau == true) {
		while (idRow <= row && tau[idRow][idCol] == -1)++idRow;
		if (idRow == row + 1)return -1;
		else return tau[idRow][idCol];
	}
	else {
		while (idRow <= row && bai[idRow][idCol] == -1)++idRow;
		if (idRow == row + 1)return -1;
		else return bai[idRow][idCol];
	}
	return -1;
}

pair<int, int> FinNumberFollowTarget(int target) {
	int ma = -1;
	int saveID = -1;
	for (int i = 1; i <= col; i++) {
		int valTop = GetValueTopCol(i, true);
		if (valTop == -1)continue;
		if (target != -1)
			if (valTop > target)continue;
		if (ma < valTop) {
			saveID = i;
			ma = valTop;
		}
	}
	return make_pair(ma, saveID);
}

void SetValueToTop(int idCol, int val, bool isTau) {
	int idRow = 1;
	if (isTau == true) {
		while (idRow <= row && tau[idRow][idCol] == -1)++idRow;
		//cout<<"idRow of tau= "<<idRow<<endl;
		tau[idRow][idCol] = val;
	}
	else {
		while (idRow <= row && bai[idRow][idCol] == -1)++idRow;
		if (idRow != 1)
			--idRow;
		//cout<<"idRow of bai= "<<idRow<<endl;
		bai[idRow][idCol] = val;
	}
}

void DoVanLoi() {
	int soLuongMove = numContainer;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			bai[i][j] = -1;
		}
	}
	ShowBai();
	while (soLuongMove) {
		bool daBoc = false;
		for (int i = 1; i <= col; i++) {
			if (bai[1][i] != -1)continue;
			int valTop = GetValueTopCol(i, false);
			pair<int, int> val = FinNumberFollowTarget(valTop);
			cout << "top bai = " << valTop << " top tau = " << val.first << " second = " << val.second << endl;
			if (val.first != -1) {
				SetValueToTop(i, val.first, false);
				SetValueToTop(val.second, -1, true);
				soLuongMove--;
				++numStep;
				daBoc = true;
				break;
			}
		}
		ShowTau();
		ShowBai();
		if (daBoc == false) {
			break;
		}
		//WriteLocationOfShip();
	}
	ShowTau();
	ShowBai();
	cout << "so buoc move = " << numStep << endl;
}

int main() {
	//freopen("C:\\Users\\quynh\\OneDrive\\Máy tính\\CodeBocHangTestCase", "r", stdin);
	freopen("input.txt", "r", stdin);
	Init();
	ShowData();
	ShowTau();
	//Nhap();
	//ShowTau();
	//while(true){
	//    int cot; cin>>cot;
	//    cout<<GetValueTopCol(cot,true)<<endl;
	//}
	//WriteLocationOfShip();
	DoVanLoi();

	/*for (int i = 1; i <= row; i++) {
		for (int j = col; j <= col; j++) {
			if (tau[i][j] == -1)
				cout << tau[i][j] << " --> " << "[" << i << "," << j << "]";
		}
	}*/
	//fstream file;
	//file.write(WriteLocationOfShip());
	//file.open("output.txt", ios::out);
	//file << WriteLocationOfShip();
	//file.close();
	//freopen("output.txt", "w", stdout);
	_getch();
	return 0;
}