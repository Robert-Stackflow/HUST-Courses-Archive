//blg2152 Pots , bfs, By Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int A,B,C;
struct Status {
	int a;
	int b;
	int prev;	//
	int mov;	//operation 
	int src,dest;
};

Status que[11000];
int head,tail;
int flags[110][110];
vector<Status> result;
int main()
{
	cin >> A >> B >> C;
	memset(flags,0,sizeof(flags));
	head = 0;
	tail = 1;
	que[head].a = 0;
	que[head].b = 0;
	que[head].prev = -1;
	flags[0][0] = 1;
	while(head!= tail) {
		Status st = que[head];
		if( st.a == C || st.b == C) {
			int ptr = head;
			while(true) {
				if( que[ptr].prev == -1)
					break;
				result.push_back(que[ptr]);
				ptr = que[ptr].prev;
			}
			cout << result.size() << endl;
			for(int i= result.size()-1;i >= 0; --i) {
				switch(result[i].mov) {
					case 1: //FILL
						cout << "FILL(" << result[i].src << ")" << endl;
						break;
					case 2: //DROP	
						cout << "DROP(" << result[i].src << ")" << endl;
						break;
					case 3:
						cout << "POUR(" << result[i].src << "," << result[i].dest << ")" << endl;
						break;
				}
			}
			return 0;
		}
		
		Status newSt;
		if( st.a < A && !flags[A][st.b]) {
			newSt = st;
			newSt.a = A;
			newSt.mov = 1;	//FILL
			newSt.src = 1;
			newSt.prev = head;
			que[tail++] = newSt;
			flags[A][st.b] = 1;
		}
		if( st.b < B && ! flags[st.a][B]) {
			newSt = st;
			newSt.b = B;
			newSt.mov = 1;	//FILL
			newSt.src = 2;
			newSt.prev = head;
			que[tail++] = newSt;
			flags[st.a][B] = 1;
		}
		if( st.a > 0 && !flags[0][st.b] ) {
			newSt = st;
			newSt.a = 0;
			newSt.mov = 2;	//DROP
			newSt.src = 1;
			newSt.prev = head;
			que[tail++] = newSt;
			flags[0][st.b] = 1;
		}
		if( st.b > 0 && !flags[st.a][0] ) {
			newSt = st;
			newSt.b = 0;
			newSt.mov = 2;	//DROP
			newSt.src = 2;
			newSt.prev = head;
			que[tail++] = newSt;
			flags[st.a][0] = 1;
		}
		if( st.b < B && st.a > 0) {
			newSt = st;
			int tmp = B - st.b;
			int newa, newb;
			if (st.a >= tmp ) {
				newa = st.a - tmp;
				newb = B;
			}
			else {
				newa = 0;
				newb = st.b + st.a;
			}
			if( !flags[newa][newb]) {
					newSt.a = newa;
					newSt.b = newb;
					newSt.src = 1;
					newSt.dest = 2;
					newSt.prev = head;
					newSt.mov = 3;	//POUR
					que[tail++] = newSt;
					flags[newa][newb] = 1;
			}
		}
		if( st.a < A && st.b > 0) {
			newSt = st;
			int tmp = A - st.a;
			int newa, newb;
			if (st.b >= tmp ) {
				newb = st.b - tmp;
				newa = A;
			}
			else {
				newb = 0;
				newa = st.a + st.b;
			}
			if( !flags[newa][newb]) {
					newSt.a = newa;
					newSt.b = newb;
					newSt.src = 2;
					newSt.dest = 1;
					newSt.prev = head;
					newSt.mov = 3;	//POUR
					que[tail++] = newSt;
					flags[newa][newb] = 1;
			}
		}
		++head;
	}
	cout << "impossible" << endl;
	return 0;
}