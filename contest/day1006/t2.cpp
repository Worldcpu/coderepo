#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=(1<<19);
int n,m,a[MN],cnt0,cnt1,pos[2][MN],ans;
bool isxor=0;

pir solve(int l,int r,int p){
    int ans1=0,ans2=0,c1=0,c2=0;
    for(int i=l;i<=r;i++){
        if(((a[i]>>p)&1)){
            ans2+=c2;
            pos[1][++cnt1]=a[i];
            c1++;
        }else{
            ans1+=c1;
            pos[0][++cnt0]=a[i];
            c2++;
        }
    }
    return pir(ans1,ans2);
}

signed main(){
    cin>>n;
    m=(1<<n);
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    int bl=m;
    for(int p=n-1;p>=0;p--){
        cnt0=cnt1=0;
        int ret1=0,ret2=0;
        for(int i=1;i+bl-1<=m;i+=bl){
            auto qwq=solve(i,i+bl-1,p);
            ret1+=qwq.first;
            ret2+=qwq.second;
        }
        ans+=min(ret1,ret2);
        if(ret1<=ret2){
            for(int i=1;i<=m/2;i++) a[i]=pos[0][i];
            for(int i=1;i<=m/2;i++) a[m/2+i]=pos[1][i];
        }else{
            isxor=1;
            for(int i=1;i<=m/2;i++) a[i]=pos[1][i];
            for(int i=1;i<=m/2;i++) a[m/2+i]=pos[0][i];
        }
        bl/=2;
    }
    cout<<ans+isxor;
    

    return 0;
}