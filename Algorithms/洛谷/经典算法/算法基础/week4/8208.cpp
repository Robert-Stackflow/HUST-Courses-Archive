//by Guo Wei
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

struct Rectangle {
	long long left,top,w,h;	
};
Rectangle a[10100];
long long  CountLeftSideArea(const Rectangle & r, long long x)
{
	if( r.left >= x)
		return 0;
	if( r.left + r.w <= x)
		return r.w * (long long) r.h;
	return r.h * (x - r.left);
}

int main()
{
	int t;

	int n,maxR;
	cin >> maxR>> n;
	for(int i = 0;i < n; ++i) {
		cin >> a[i].left >> a[i].top >> a[i].w >> a[i].h ;
	}
	int L = 0, R = maxR;
	int lastDif = 0; //左边比右边多的面积 
	long long leftTotal;
	long long rightTotal;
	int x;
	long long minDif ;
	while(L < R) {
		x = (L+R)/2;
		leftTotal = 0;
		rightTotal = 0;
		for(int i = 0; i < n; ++i) {
			long long leftArea =  CountLeftSideArea(a[i],x);
			leftTotal += leftArea;
			rightTotal += a[i].w * a[i].h - leftArea;
		}
		if( leftTotal - rightTotal >= 0) {
			minDif = leftTotal - rightTotal; //左边比右边多的面积
			R = x;
		}
		else
			L = x+1;
	}
	
	R = maxR;
	while(L < R) {
		x = (L+R)/2;
		if( x == L )
			break;
		leftTotal = 0;
		rightTotal = 0;
		for(int i = 0; i < n; ++i) {
			long long leftArea = CountLeftSideArea(a[i],x);
			leftTotal += leftArea;
			rightTotal += a[i].w * a[i].h - leftArea;
		}
		if( leftTotal - rightTotal > minDif) 
			R = x-1;
		else 
			L = x;
			
	}
	leftTotal = 0;
	rightTotal = 0;
	for(int i = 0; i < n; ++i) {
		long long leftArea = CountLeftSideArea(a[i],R);
		leftTotal += leftArea;
		rightTotal += a[i].w * a[i].h - leftArea;
	}
	if( leftTotal - rightTotal == minDif)
		cout << R << endl;
	else
		cout << L <<endl; 
	return 0;
}
