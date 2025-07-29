#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5520;
int a[MN],b[MN],s[MN],ans[MN],n,m;

void dfs(int x){
    if(x>m){
        int cnt0=0;
        for(int j=1;j<=n;j++){
            cnt0+=(!s[j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=i,cnt=0;j<=n;j++){
                if(s[j]>0) break;
                cnt+=(!s[j]);
                if(cnt==cnt0){
                    ans[j-i+1]^=1;
                }
            }
        }
        return;
    }
    int pa=a[x],pb=b[x];
    if(s[pa]<0&&s[pb]<0){
        s[pa]=s[pb]=0;
        dfs(x+1);
        s[pa]=s[pb]=1;
        dfs(x+1);
        s[pa]=s[pb]=-1;
    }else{
        bool flag=(!s[pa])||(s[pb]>0);
        if(flag) swap(s[pa],s[pb]);
        dfs(x+1);
        if(flag) swap(s[pa],s[pb]);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1;i<=n;i++) s[i]=-1;
    dfs(1);
    for(int i=1;i<=n;i++){
        cout<<(ans[i])<<" ";
    }

    return 0;
}