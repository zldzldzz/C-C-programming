#include "playfair.h"
#include <iostream>
#include <vector> //�������� �迭 ���
#include <map> //��ųʸ� ���� ���
#include <string>
#include <algorithm> // std::find

using namespace std;

void Playfair::makeTable() {
	vector<char> temp;	//key���� char������ �ڸ��� ����

	//Key�� �ߺ� �����ϰ� ������ Table �����ϱ�
	for (int i = 0; i < this->mKey.length(); i++) {
		if (find(temp.begin(), temp.end(), this->mKey[i]) == temp.end()) {
			temp.push_back(this->mKey[i]);
		}
	}
	//alphabet �迭���� key���� �ߺ�����
	for (int i = 0; i < temp.size(); i++) {
		auto index = find(alphabet.begin(), alphabet.end(), string(1, temp[i]));
		if (index != alphabet.end()) {
			alphabet.erase(index);
		}
	}
	vector <string> str;
	int cnt = 0;
	for (int i = 0; i < temp.size() + alphabet.size(); i++) {
		if (i < temp.size()) str.push_back(string(1, temp.at(i)));
		else str.push_back(alphabet.at(cnt++));
	}

	//���ĺ����� '/'�� ���е� mPair �����
	auto pos = this->mPair.find('/');  // '/'�� ��ġ�� ã��
	string pair_1, pair_2;
	if (pos != string::npos) {
		pair_1 = this->mPair.substr(0, pos);      // ù ��° �κ� (a)
		pair_2 = this->mPair.substr(pos + 1);
	}

	auto index = find(str.begin(), str.end(), pair_1);
	if (index != str.end()) {
		index = str.erase(index);
		str.insert(index, pair_1 + "/" + pair_2);

		index = find(str.begin(), str.end(), pair_2);
		str.erase(index);
		//for (string c : str) cout << c << endl;
	}

	//mtable ����
	cnt = 0;
	for (int i = 0; i < SIZE; i++) {
		this->mTable[i] = str[i];
	}
	//for (int i = 0; i < SIZE; i++) cout << this->mTable[i]<< " ";
}

void Playfair::showTable() {
	for (int i = 0; i < SIZE; i++) {
		if (i % 5 == 0 && i != 0) cout << endl;
		cout.width(3);
		cout << this->mTable[i] << " ";
	}
	cout << endl;
}

string Playfair::makeEncryption(string mEncryption) {
	//���� ��ȣ������ �ٲٱ� ���� �۾�
	vector<vector<string>> str;
	vector<string> checkStr;

	for (int i = 0; i < mEncryption.size();){
		string firstStr = (i< mEncryption.size()) ? string(1, mEncryption[i++]) : "x";
		if ((firstStr == string(1, this->mPair.at(0))
			|| (firstStr == string(1, this->mPair.at(2))))) {
			firstStr = this->mPair;
		}
		// ù ��° ���� ��������
		checkStr.push_back(firstStr);
		// �ߺ��� ������ ��� "x" �߰�
		if (i < mEncryption.size() 
			&& firstStr == string(1, mEncryption[i])
			&& checkStr.size()<=1) {
			checkStr.push_back("x");
		}
		else if ((i < mEncryption.size()&& firstStr == this->mPair)
			&& (mEncryption[i] == this->mPair.at(0) || mEncryption[i] == this->mPair.at(2))
			&& checkStr.size() <= 1) {
			checkStr.push_back("x");
		}
		// 2���� ���� ä�������� ������ �߰�
		if (checkStr.size() == 2) {
			str.push_back(checkStr);
			checkStr.clear();
		}
	}

	// ���� �����͸� ó��
	if (!checkStr.empty()) {
		// ������ �� ä���
		while (checkStr.size() < 2) {
			checkStr.push_back("x");
		}
		str.push_back(checkStr);
	}

	/*for (const auto& row : str) {
		for (const auto& elem : row) {
			cout << "\"" << elem << "\"" << " ";
		}
		cout<< endl;
	}*/


	for (int i = 0; i < str.size(); i++) {
		// �� ������ ��ǥ�� ���
		int index1 = -1, index2 = -1;

		// `mTable`���� �� ������ �ε����� ã��
		for (int k = 0; k < SIZE; k++) {
			if (mTable[k] == str[i][0]) index1 = k;
			if (mTable[k] == str[i][1]) index2 = k;
		}

		int row1 = index1 / ROW, col1 = index1 % COL;
		int row2 = index2 / ROW, col2 = index2 % COL;
		//cout << row1 << col1 << " " << row2 << col2 << endl;
		// ���� ��
		if (col1 == col2) {
			row1 = (row1 + 1) % ROW;
			row2 = (row2 + 1) % ROW;
		}
		// ���� ��
		else if (row1 == row2) {
			if (col1 + 1 >= 5)col1 = (col1 - 1) % COL;
			else col1 = (col1 + 1) % COL;
			if (col2 + 1 >= 5)col2 = (col2 + 1) % COL;
			else col2 = (col2 + 1) % COL;
		}
		// �ٸ� ��, �ٸ� ��
		else {
			swap(col1, col2);
		}

		// �� ���ڸ� `mTable`���� ������
		str[i][0] = mTable[row1 * COL + col1][0];
		str[i][1] = mTable[row2 * COL + col2][0];
	}
	mEncryption = "";	//�� ����
	for (const auto& pair : str) {
		mEncryption += pair[0];
		mEncryption += pair[1];
	}
	return mEncryption;
}

int main() {
	Playfair key("goodgirl", "d/l");
	key.showTable();
	string nomalKey = "oordd";
	string afterKey = key.makeEncryption(nomalKey);
	cout << nomalKey << " -> " << afterKey;
	return 0;
}