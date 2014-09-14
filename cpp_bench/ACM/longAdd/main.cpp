#include<stdlib.h>
#include<iostream>
#include<string>//c++ string
#include<string.h>//c string
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> vint;
vector<int> vdec;
vector<int>::iterator ivint;
vector<int>::iterator ivdec;
enum caculate{add,minus}operation;

void addUpToVector(string stringNum, vector<int> &vectorNum, const caculate &operation);
bool addUpCarryBit(int loop, int &carry, vector<int> &vectorNum, bool sign);

int main(){
	int i;
	string input, decimals, integer;
	while(getline(cin, input)&&input.length() != 0){
		if((i = input.find('.'))!= string::npos){
			integer = input.substr(0, i);
			decimals = input.substr(i+1);
		}
		else integer = input;

		if((i = input.find('-'))!=string::npos){
			integer = integer.substr(1);
			operation = caculate::minus;
		}
		else if(input.at(0)>'0'&&input.at(0)<'9')
			operation = add;

		addUpToVector(integer, vint, operation);
		if(!decimals.empty()){
			string revDec = string(decimals.rbegin(), decimals.rend());
			addUpToVector(revDec, vdec, operation);
		}
	}
	reverse(vdec.begin(), vdec.end());

	int loop = vdec.size(),carry = 0;
	bool sign = addUpCarryBit(loop, carry, vdec, true);
	loop = vint.size();
	addUpCarryBit(loop, carry, vint, sign);

	if(carry!=0)
		vint.insert(vint.begin(), carry);
	
	for(ivint = vint.begin(); ivint != vint.end(); ivint++)
		cout<<*ivint;
	cout<<".";
	for(ivdec = vdec.begin(); ivdec != vdec.end(); ivdec++)
		cout<<*ivdec;
}

void addUpToVector(string stringNum, vector<int> &vectorNum, const caculate &operation){
	int i, j;
	int loop, min;
	if(vectorNum.empty()){
		for(i = stringNum.length()-1; i >= 0; i--)
			vectorNum.insert(vectorNum.begin(), stringNum.at(i) - '0');
	}else{
		i = stringNum.length();
		j = vectorNum.size();
		loop =(i<j)?i:j, min = loop;
		while(loop){
			loop--;
			i--;
			int temp = vectorNum.back();
			vectorNum.pop_back();
			if(operation == caculate::add)
				vectorNum.insert(vectorNum.begin(), stringNum.at(i) - '0' + temp);
			else if(operation == caculate::minus)
				vectorNum.insert(vectorNum.begin(), temp - (stringNum.at(i) - '0'));
		} 
		if(j>min){
			while(j-min){
				int temp = vectorNum.back();
				vectorNum.insert(vectorNum.begin(), temp);
				vectorNum.pop_back();
				j--;
			}
		}else if(i>0){
			while(i){
				i--;
			if(operation == caculate::add)
				vectorNum.insert(vectorNum.begin(), stringNum.at(i) - '0');
			else if(operation == caculate::minus)
				vectorNum.insert(vectorNum.begin(), '0' - stringNum.at(i));
			}
		}
	}
}

bool addUpCarryBit(int loop, int &carry, vector<int> &vectorNum, bool sign){
	int tail;
	bool insign = true;
	if(!sign)insign = false;
	while(loop){
		int num = vectorNum.back();
		num += carry;
		vectorNum.pop_back();
		tail = num %10;
		carry = (num - tail)/10;
		if(tail<0){
			tail*=-1;
			sign = false;
		}
		if(!insign && loop ==1)tail*=-1;
		vectorNum.insert(vectorNum.begin(), tail);
		loop--;
	}
	return sign;
}