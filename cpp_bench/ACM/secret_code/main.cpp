#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define MAXLENGTH 256
#define SIZE 70
using namespace std;

void main(void){
	int code = 0;
	int key = 0;
	int i = 0;
	char text[MAXLENGTH];
	int *textcode;
	int *detextcode;
	char detext[MAXLENGTH];
	int n = 0;
	int j = 0;

	while(1){
		scanf("%d", &key);

		if(key == 0)
			break;
		scanf(" %s", text);
		if(strlen(text)>SIZE){
			cout<<"too much"<<endl;
			continue;
		}
		textcode = (int*)malloc(strlen(text)*sizeof(int));
		detextcode = (int*)malloc(strlen(text)*sizeof(int));
		for(i = 0; i< strlen(text); i++){
			if(text[i]== '_')
				textcode[i] = 0;
			else if(text[i]== '.')
				textcode[i] = 27;
			else if(96< text[i]< 123)
				textcode[i] = text[i]- 96;
			else{
				cout<<"illegal character!"<<endl;
				code = -1;
				break;
			}
			//printf("%d ", textcode[i]);
		}

		
		if(code != -1){
			n = strlen(text);
			for(int i = 0; i< n;i++){
				j = i;
				while(j%key != 0)j+= n;
				j /= key;
				detextcode[i] = (textcode[j]+j)%28;
			}
			
			for(i = 0; i< n; i++)
				if(detextcode[i]== 0)
					detext[i] = '_';
				else if(detextcode[i]== 27)
					detext[i] = '.';
				else if(0< detextcode[i]< 27)
					detext[i] = detextcode[i]+ 96;
				else{
					cout<<"illegal character!"<<endl;
				}
			detext[n] = '\0';
			printf("%s\n",detext);
	    }
	}
	/*while((c = getchar())!=EOF){
		if(c == '0')
			break;
		else if(c == '_')
			code = 0;
		else if(c == '.')
			code = 27;
		else if(96< c< 123)
			code = c - 96;
		else{
			cout<<"illegal character!"<<endl;
			code = -1;
		}
		if(code != -1){
		}
	}*/

	free(textcode);
	free(detextcode);
}