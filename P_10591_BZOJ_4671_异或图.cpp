#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int n,m,g[MN],pw[MN],col[MN],ans;

struct xxj{
    int p[65],cnt;

    void clear(){
        memset(p,0,sizeof(p));
        cnt=0;
    }

    void insert(int x){
        for(int i=60;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    cnt++;
                    break;
                }else x^=p[i];
            }
        }
    }

}xj;


void init(){
    pw[0]=1;
    for(int i=1;i<=15;i++){
        pw[i]=pw[i-1]*i;
    }
}

int clac(int S){
    xj.clear();
    for(int i=1;i<=n;i++){
        xj.insert(g[i]&S);
    }
    return 1ll<<(n-xj.cnt);
}

void dfs(int now,int cnt){
    if(now==m+1){
        int p=0,ret=0;
        for(int i=1;i<=m;i++){
            for(int j=i+1;j<=m;j++){
                if(col[i]!=col[j]) ret|=(1ll<<p);
                p++;
            }
        }
        if(cnt&1) ans+=clac(ret)*pw[cnt-1];
        else ans-=clac(ret)*pw[cnt-1];
        return;
    }
    for(int i=1;i<=cnt+1;i++){
        col[now]=i;
        dfs(now+1,max(cnt,col[now]));
    }
}

signed main(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(m=0;m<=10;m++){
            if(m*(m-1)/2==s.size()) break;
        }
        for(int j=0;j<s.size();j++){
            if(s[j]=='1'){
                g[i]|=(1<<j);
            }
        }
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
