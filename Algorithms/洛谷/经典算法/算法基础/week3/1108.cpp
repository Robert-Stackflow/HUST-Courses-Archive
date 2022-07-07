#include <iostream>
#include <cstdio>
using namespace std;
char wholeExp[200];
bool exp();
bool factor();
bool item();
int ptr = 0;
bool exp() {
	bool result = item();
	while(wholeExp[ptr] == '|' ) {
		++ptr;
		result = result | item();
	}
	return result;
}
bool item() {
	bool result = factor();
	while(wholeExp[ptr] == '&') {
		++ptr;
		result = result & factor();
	}
	return result;
}
bool notExp()
{
	//wholeExp[ptr] == '!' when called;
	ptr++;
	bool result;
	switch(wholeExp[ptr]) {
		case 'F':
			++ptr;
			return true;
			break;
		case 'V':
			++ptr;
			return false;
			break;
		case '(':
			++ptr;
			result = exp();
			++ptr;  //skip ')'
			return !result;
			break;
		case '!':
			result = notExp();
			return !result;
			break;
	}
}

bool factor() {
	bool result;
	switch( wholeExp[ptr]) {
		case 'F':
			++ptr;
			return false;
			break;
		case 'V':
			++ptr;
			return true;
			break;
		case '(': 
			++ptr;
			result = exp();
			++ptr;
			return result;
			break;
		case '!':
			result = notExp();
			return result;
			break;
	}
}


int main()
{
	char c;
	int i = 0;
	int t = 1;
	int n = EOF + 1; 
	while(n != EOF) {
		 n =  scanf("%c",&c);
		if(	n == EOF || c == '\n') {
			wholeExp[i] = 0;
			if( i > 0) {
				ptr = 0;
				bool r = exp();
				if (r) {
					printf("Expression %d: V\n",t++);
				}
				else 
					printf("Expression %d: F\n",t++);
			}
			i = 0;
		}
		else if( c != ' ') 
			wholeExp[i++] = c;
	}
}
