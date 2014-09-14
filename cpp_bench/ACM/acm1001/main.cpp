#include<stdlib.h>
#include<iostream>
#include<string>//c++ string
#include<string.h>//c string
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> vnum;
vector<int> vstprst;
vector<int>::iterator it;

void addUpToVector(string stringNum, vector<int> &vectorNum);
void addUpCarryBit(int loop, int &carry, vector<int> &vectorNum);

int main(){
	int i, j, point, ltime;
	string input, number, temnum;
	while(getline(cin, input)&&input.length() != 0){
		/*break input in between blank, get number and t.*/
		if((i = input.find(' '))!=string::npos){
			number = input.substr(0, i);
			ltime = atoi(input.substr(i+1).c_str());
		}else{
			cout<<"input fault"<<endl;
			return 1;
		}

		if((i = number.find('.'))!= string::npos){
			point = i;
			number.erase(i, 1);
		}

		/*do mutiply for per number for ltime times, store result into vector*/
		if(vnum.empty())
			for(i = number.length() - 1; i>=0; i--)
				vnum.insert(vnum.begin(), number.at(i) - '0');

		while(ltime){
			ltime--;
		}
	}
	
	/*//move this part into while loop//
	reverse(vdec.begin(), vdec.end());

	int loop = vdec.size();
	addUpCarryBit(loop, carry, vdec);
	loop = vint.size();
	addUpCarryBit(loop, carry, vint);
	

	if(carry!=0)
		vint.insert(vint.begin(), carry);
	
	for(ivint = vint.begin(); ivint != vint.end(); ivint++)
		cout<<*ivint;
	cout<<".";
	for(ivdec = vdec.begin(); ivdec != vdec.end(); ivdec++)
		cout<<*ivdec;*/
}



void addUpCarryBit(int loop, int &carry, vector<int> &vectorNum){
	int tail;
	while(loop){
		int num = vectorNum.back();
		num += carry;
		vectorNum.pop_back();
		tail = num %10;
		carry = (num - tail)/10;
		vectorNum.insert(vectorNum.begin(), tail);
		loop--;
	}
}