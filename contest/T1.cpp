#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
int K,fk,ret;
vector<pir> op;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

signed main(){
    freopen("SH.in","r",stdin);
    freopen("SH.out","w",stdout);
    cin>>K;
    fk=K;
    for(int i=2;i<=sqrt(fk);i++){
        if(K%i==0){
            int s=0;
            while(K%i==0){
                K/=i;
                s++;
            }
            op.push_back(pir(i,s));
        }
    }
    if(K>1) op.push_back(pir(K,1));
    ret=1;
    for(auto p:op){
        if(p.second%2==0) ret*=ksm(p.first,p.second/2);
        else ret*=ksm(p.first,(p.second+1)/2);
    }
    if(ret%fk==0) cout<<-1;
    else cout<<ret;
    return 0;
}
