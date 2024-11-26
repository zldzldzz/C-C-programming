#include <iostream>
#include <string>
#include <vector>
using namespace std;

string alphabet1="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class Playfair {
	string mTable[25];
	string mPair;
	string mKey;
public:
	Playfair(string mKey, string mPair);
	void makeTable();
	void showTable();
    void findindex(char let,int& row,int& col);
	string makeEncryption(string mEncryption);
};

//"assasinator", "q/z"
Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
    if (mPair[0]>mPair[2]){
        string tmp="";
        tmp[0]=mPair[0];//z a
        mPair[0]=mPair[2];
        mPair[2]=tmp[0];
    }
    for(int i=0;i<mPair.size();i++){
        mPair[i]=toupper(mPair[i]);
    }
	this->mPair = mPair;

}


void Playfair::makeTable() {
	// mKey�� mPair�� �̿��Ͽ� mTable�� ���弼��. (5 X 5 �� ǥ���Ͻÿ�)
    string str=this->mKey;
    string afterStr="";
    string afterPair="";
    string alphabet="";

    int check=0;

    for (int i=0;i<str.size();i++){
        str[i]=toupper(str[i]);
    }

    for (int i = 0; i <str.length(); i++) {
        check = 0; // �ʱ�ȭ: �ߺ� ���θ� Ȯ��
        // �̹� afterStr�� �����ϴ��� Ȯ��
        for (int j = 0; j < afterStr.length(); j++) {
            if (afterStr[j] ==str[i]) {
                check = 1;
                break; // �ߺ� �߰� �� �ߴ�
            }
        }
        // �ߺ����� �ʰ� ���ǿ� �����ϸ� �߰�
        if (check == 0 && 
            alphabet1.find(str[i]) != string::npos && // alphabet1�� �ִ� �������� Ȯ��
            mPair.find(str[i]) == string::npos) {    // mPair�� ���� �������� Ȯ��
            afterStr.push_back(str[i]);
        }
    }
    // cout<<"afterstr:"+afterStr+"\n";

   for (int i = 0; i < alphabet1.size(); i++) {
    check = 0; // �ʱ�ȭ: �ߺ� ���θ� Ȯ��

    // �̹� alphabet�� �����ϴ��� Ȯ��
    for (int j = 0; j < alphabet.size(); j++) {
        if (alphabet[j] == alphabet1[i]) {
            check = 1; // �ߺ� �߰�
            break; // �ߺ� �߰� �� �� �̻� Ȯ������ ����
        }
    }

    // �ߺ����� �ʰ� �� ���ǿ� �����ϸ� �߰�
    if (check == 0 && 
        afterStr.find(alphabet1[i]) == string::npos)  // afterStr�� ���� �������� Ȯ��) 
        { 
        alphabet.push_back(alphabet1[i]); // �� ���ڿ� ��ο� ������ �߰�
    }
}
   
   
    this->mKey=afterStr;
    // cout<<"���ĺ�"+alphabet;

//���̺� ������
int index=0;
    for (char ch : afterStr) {
        if (index < 25) {
            mTable[index++] = string(1, ch); // �� ���ھ� ����
        }
    }

    for (char ch : alphabet) {
    // ���� ���ڸ� ���ڿ��� ��ȯ
    string currentChar(1, ch);

    // mPair�� ù ��° �ܾ�� ������ mPair�� ����
    if (currentChar == mPair.substr(0, 1)) {
        mTable[index++] = mPair;
        continue; // ���� ���ڷ� �Ѿ
    }

    // mPair�� �� ��° �ڸ��� ������ �ش� ���ڴ� �߰����� ����
    if (mPair.length() >= 3 && currentChar == mPair.substr(2, 1)) {
        continue; // �ƹ� �۾��� ���� �ʰ� ���� ���ڷ� �Ѿ
    }

    // �⺻ ����: �� ���ھ� ����
    if (index < 25) {
        mTable[index++] = currentChar;
    } else {
        break; // ������ �� ���� ����
    }
}

}
void Playfair::findindex(char let, int& row, int& col) {
    // mTable �迭���� ������ ��ġ�� ã�� ��(row)�� ��(col)�� ���
    if(mPair[2]==let){
        let=mPair[0];
    }
    for (int i = 0; i < 25; i++) { // mTable�� ��� ��Ҹ� ��ȸ
        if (mTable[i][0] == let) { // mTable[i]�� ù ���ڰ� ã�� ���ڿ� ���ٸ�
            row = i / 5; // 5�� ���� ���� �� ��ȣ
            col = i % 5; // 5�� ���� �������� �� ��ȣ
            return;      // ��ġ�� ã���� �Լ� ����
        }
    }
    // ���ڸ� ã�� ���ϸ� row�� col�� -1�� ���� (���� ó��)
    row = -1;
    col = -1;
}
void Playfair::showTable() {
	// mTable�� �ִ� ������ 5 X 5 �� ȭ�鿡 ����Ͻÿ�.
    cout << "mTable:" << endl;
    for(int j=0;j<5;j++){
        cout<<"\n";
        for (int i = 0; i < 5; i++) {
        cout  << mTable[5*j+i] +"\t";
    }
    }
    cout << endl;

}

string Playfair::makeEncryption(string mEncryption) {
    // �Է� ���ڿ��� �빮�ڷ� ��ȯ
    for (size_t i = 0; i < mEncryption.size(); i++) {
        mEncryption[i] = toupper(mEncryption[i]);
    }

 bool completion = true;
    while (completion) {
        completion = false; // �⺻������ �ݺ� ���Ḧ ����
        for (size_t i = 0; i + 1 < mEncryption.size(); i += 2) { // i+1�� ������ �ʰ����� �ʵ��� Ȯ��
            if (mEncryption[i] == mEncryption[i + 1]) {
                if (mEncryption[i] == 'X') { 
                    mEncryption.insert(i + 1, "Q"); // "X" ���̿� "Q" ����
                } else {
                    mEncryption.insert(i + 1, "X"); // �ٸ� ��� "X" ����
                }
                completion = true; // ������ �Ͼ�� ������ �ٽ� ����            // ������ �Ͼ�� ������ �ٽ� ����
                break;                         // �� �� ���� �� ����
            }
        }
    }

    // ���ڿ��� 2���ھ� ������ ���� �ʿ��� �迭 ũ�� ���

    size_t pairCount = (mEncryption.size() + 1) / 2; // 2���ھ� ������ �� �ʿ��� ���� ����
    string str[pairCount]; // �迭 ����
    string strl[pairCount]; // �迭 ����


    // ���ڿ��� 2���ھ� ������ �迭�� ����
    for (size_t i = 0, j = 0; i < mEncryption.size(); i += 2, j++) {
        if (i + 1 < mEncryption.size()) {
            // 2���ڰ� �ִ� ��� �״�� ����
            str[j] = mEncryption.substr(i, 2);
        } else {
            // ������ ���ڰ� �� ������ ��� �ڿ� 'X' �߰�
            str[j] = mEncryption.substr(i, 1) + "X";
        }
    }

    // 2���� �ܾ ��� Ȯ���ϱ�
    // for (size_t i = 0; i < pairCount; i++) {
    //     cout << "str[" << i << "]: " << str[i] << endl;
    // }
    int col1,row1,col2,row2=0;
    mEncryption="";
    for(int i=0;i<pairCount;i++){
        findindex(str[i][0],row1,col1);
        findindex(str[i][1],row2,col2);
        // cout<<row1<<col1<<str[i][0]<<" 2�� ";
        // cout<<row2<<col2<<str[i][1]<<endl;

        if(row1==row2){
        if(mTable[((row2+1)%5)*5+col1]==mPair){
                mEncryption.append(1,mPair[0]);
        }
        else{
        mEncryption.append(mTable[((row2+1)%5)*5+col1]);
        }
        if(mTable[((row2+1)%5)*5+col2]==mPair){
                mEncryption.append(1,mPair[0]);
        }
        else{
        mEncryption.append(mTable[((row2+1)%5)*5+col2]);

        }
        }
        else if(col1==col2){
            if(mTable[row2*5+((col2+1)%5)]==mPair){
                mEncryption.append(1,mPair[0]);
            }
            else{
                mEncryption.append(mTable[row2*5+((col2+1)%5)]);
            }
            if(mTable[row1*5+((col2+1)%5)]==mPair){
                    mEncryption.append(1,mPair[0]);
            }
            else{
            mEncryption.append(mTable[row1*5+((col2+1)%5)]);
            }
        }
        else
        {
            if(mTable[row2*5+col1]==mPair){
                mEncryption.append(1,mPair[0]);
            }
            else{
                mEncryption.append(mTable[row2*5+col1]);

            }
            if(mTable[row1*5+col2]==mPair){
                mEncryption.append(1,mPair[0]);
                }
            else{
                mEncryption.append(mTable[row1*5+col2]);
            }
        }
        


        cout<<i<<": "<<mEncryption<<endl;


    }


    return "\n";
}
