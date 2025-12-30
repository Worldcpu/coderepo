#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=15,MOD=998244353;
int n,a[MN],ans;

bool check(){
    for(int i=1;i<=n;i++){
        int stl=a[i-1],str=a[i+1],st=a[i];
        if(st==3) continue;
        int cnt[4]{};
        for(int i=0;i<4;i++){
            cnt[i]+=(stl==i)+(str==i)+(st==i);
        }
        if((3-cnt[0])>=2&&((cnt[1]+cnt[3]>=1)&&(cnt[2]+cnt[3]>=1))){
            return 0;
        }else{
            int mxcnt=*max_element(cnt,cnt+4);
            if(cnt[st]!=mxcnt) return 0;
        }
    }
    for(int i=1;i<=n;i++){
        ans+=(a[i]==0);
        ans%=MOD;
    }
    return 1;
}

void dfs(int pos){
    if(pos==n+1){
        if(check()){
            for(int i=0;i<=n+1;i++){
                cerr<<a[i]<<' ';
            }
            cerr<<'\n';
        }
        return;
    }
    for(int i=0;i<4;i++){
        a[pos]=i;
        dfs(pos+1);
    }
}

signed main(){
    cin>>n;
    a[0]=a[n+1]=3;
    dfs(1);
    cout<<ans;
    
    return 0;
}