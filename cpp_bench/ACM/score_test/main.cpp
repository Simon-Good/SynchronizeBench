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
		if(leftW > i && winner%i == 0){//如果i能整除winner， 并且商大于除数（在除数从1开始递增的情况下，商如果小于除数，显然是不合理的）
			flagW = true;//给当前除数置换flag
			vectorW.push_back(i);//记录因子个数
		}
		if(leftL > i && loser%i == 0){
			flagL = true;
			vectorL.push_back(i);
		}
		if(flagL==true && flagW == true)//如果有一个值能同时整除二者，可疑，记录下来
			flags.push_back(1);
		flagL = false;
		flagW = false;
	}
	if(vectorW.size() == 0 && vectorL.size() == 0)//如果两个数都无法被1-100整除
		return tempW;
	else if(vectorW.size() == 0)//由于假设分数低者不会撒谎，所以，如果分数高者的分数明显错误，则分数低者获胜
		return tempL;

	if(flags.size() == 1)//如果有一个及以上，1-100之内相同的数，可以整除二者，则挑战成功
		return tempL;
	else //否则挑战失败
		return tempW;
}