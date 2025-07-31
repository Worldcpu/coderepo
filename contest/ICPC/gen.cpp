#include<bits/stdc++.h>
#include <random>
#define ull unsigned long long
using namespace std;
constexpr int n=2e5,q=2e5;
ull lst;

ull shift(ull x){
	x^=x<<5;
	x^=x>>11;
	x^=x<<54;
	return x;
}


int randd(int l,int r){
    return (lst=shift(lst))%(r-l+1)+l;
}

int main(){
    ios::sync_with_stdio(0);
    cout.tie(0);
    freopen("memory.in","w",stdout);
    srand(time(0));
    lst=rand();
    cout<<n<<" "<<q<<'\n';
    for(int i=1;i<=q;i++){
        int op,l,r,k;
        op=randd(1,3);
        l=randd(1,n),r=randd(1,n);
        if(l>r) swap(l,r);
        if(op==1){
            k=randd(1,n);
            cout<<op<<" "<<l<<" "<<r<<" "<<k<<'\n';
        }else cout<<op<<" "<<l<<" "<<r<<'\n';
    }

    return 0;
}