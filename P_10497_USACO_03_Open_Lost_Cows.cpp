#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,a[MN],ans[MN];
struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

int main(){
    cin>>n;
    bit.update(1,1);
    for(int i=2;i<=n;i++){
        cin>>a[i];
        bit.update(i,1);
    }
    for(int i=n;i>=1;i--){
        int p=0,s=0;
        for(int j=20;j>=0;j--){
            int np=p+(1<<j);
            if(np>n) continue;
            int ns=s+bit.t[np];
            if(ns<a[i]+1){
                s=ns;
                p=np;
            }
        }
        p++;
        bit.update(p,-1);
        ans[i]=p;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}