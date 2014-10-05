#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;


int challenge(int winner, int loser);

void main(void){
	int winner, loser, temp;
	printf("->:");
	scanf("%d %d", &winner, &loser);
	if(winner < loser){
		temp = winner;
		winner = loser;
		loser = temp;
	}
	if(winner < 100 && loser< 100){
		printf("winner is %d", winner);
		return;
	}
	if(winner > 10000 && loser > 10000){
		printf("winner is %d", winner);
		return;
	}
	winner = challenge(winner, loser);
	printf("winner is %d", winner);
	return;
}

int challenge_0(int winner, int loser){
	int i, leftW, leftL;
	int tempW = winner;
	int tempL = loser;
	vector<int> winnerVct;
	vector<int> loserVct;
	for(i = 1; i< 101; i++){
		leftW = winner/i;
		if(leftW > i && winner%i == 0){
			winnerVct.push_back(leftW);
			winner = leftW;
		}else{
			continue;
		}
	}
	winnerVct.push_back(winner);

	for(i = 2; i < 101; i++){
		leftL = loser/i;
		if(leftL > i && loser%i == 0){
			loserVct.push_back(leftL);
			loser = leftL;
		}else{
			continue;
		}
	}
	loserVct.push_back(loser);

	if(loserVct.size()==1 && loserVct.front() > 100)
		return tempW;
	if(winnerVct.size()==1 && winnerVct.front()> 100)
		return tempW;

	vector<int>::iterator it;
	vector<int>::iterator itt;
	for(it = winnerVct.begin(); it!= winnerVct.end(); ++it){
		for(itt = loserVct.begin(); itt!= loserVct.end(); ++ itt){
			if(*it == *itt)
				return tempL;
		}
	}
	return tempW;
}

int challenge(int winner, int loser){
	int tempW = winner, tempL = loser;
	vector<int> vectorW;
	vector<int> vectorL;
	vector<int> flags;
	int leftW, leftL;
	bool flagW = false, flagL = false;

	for(int i = 2; i< 101; i++){
		leftW = winner/i;
		leftL = winner/i;
		if(leftW > i && winner%i == 0){//���i������winner�� �����̴��ڳ������ڳ�����1��ʼ����������£������С�ڳ�������Ȼ�ǲ�����ģ�
			flagW = true;//����ǰ�����û�flag
			vectorW.push_back(i);//��¼���Ӹ���
		}
		if(leftL > i && loser%i == 0){
			flagL = true;
			vectorL.push_back(i);
		}
		if(flagL==true && flagW == true)//�����һ��ֵ��ͬʱ�������ߣ����ɣ���¼����
			flags.push_back(1);
		flagL = false;
		flagW = false;
	}
	if(vectorW.size() == 0 && vectorL.size() == 0)//������������޷���1-100����
		return tempW;
	else if(vectorW.size() == 0)//���ڼ���������߲������ѣ����ԣ�����������ߵķ������Դ�����������߻�ʤ
		return tempL;

	if(flags.size() == 1)//�����һ�������ϣ�1-100֮����ͬ�����������������ߣ�����ս�ɹ�
		return tempL;
	else //������սʧ��
		return tempW;
}