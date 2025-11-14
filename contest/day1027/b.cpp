#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,x[MN],y[MN];
bitset<MN> A,B,C,B2,A2;

void shift(bitset<MN> &bit,int k){
    if(k>=0) bit>>=k;
    else bit<<=-k;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i];
        A.set(x[i]);
    }
    for(int i=1;i<=n;i++){
        cin>>y[i];
        B.set(y[i]);
    }
    for(int i=1;i<=n;i++){
        int r1=y[1]-x[i];
        C=A;
        shift(C,r1);        
        C&=B;
        B2=B,B2^=C;
        shift(C,-r1);
        A2=A;
        A2^=C;
        int posa=A2._Find_first(),posb=B2._Find_first();
        shift(A2,posb-posa);
        if(A2==B2){
            cout<<r1<<' '<<posb-posa<<'\n';
            return 0;
        }
    }

    return 0;
}