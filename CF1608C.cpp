#pragma GCC optimize(0)
#include<iostream> 
#include<cstdio> 
#include<cstdlib> 
#include<ctime> 
#include<fstream> 
#include<algorithm> 
#include<map> 
#include<queue> 
#include<deque> 
#include<set> 
#include<vector>
#define ll long long
#define lf double
#define ld long double
using namespace std;
ll tot,tot2,st;
int main(){
	for(int i=0;i<3;i++){
		tot=0;
	    st=clock();
	    for(int i=0;i<100000000;i++)tot++;
	    tot=100000000/((clock()-st)*1.0/CLOCKS_PER_SEC);
	    cout<<tot<<' ';
	    tot2+=tot;
	}
	cout<<tot2/3;
	return 0;
} 
