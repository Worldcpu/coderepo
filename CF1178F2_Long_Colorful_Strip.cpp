#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1020,MK=1e6+15,MOD=998244353;
int n,m,c[MK],f[MN][MN];
vector<int> col[MK];

int dfs(int l,int r){
    if(~f[l][r]) return f[l][r];
    if(l>r) return (f[l][r]=1);
    int p=c[l];
    for(int i=l;i<=r;i++){
        p=min(p,c[i]);
    }
    if(col[p].front()<l||col[p].back()>r) return f[l][r]=0;
    if(l==r) return f[l][r]=1;
    int ans1=0,ans2=1,ans3=0,pl=col[p].front(),pr=col[p].back();
    for(int i=l;i<=pl;i++){
        ans1=(ans1+dfs(l,i-1)*dfs(i,pl-1)%MOD)%MOD;
    }
    for(int i=0;i<col[p].size()-1;i++){
        ans2=ans2*dfs(col[p][i]+1,col[p][i+1]-1)%MOD;
    }
    for(int i=pr;i<=r;i++){
        ans3=(ans3+dfs(pr+1,i)*dfs(i+1,r)%MOD)%MOD;
    }
    return f[l][r]=ans1*ans2%MOD*ans3%MOD;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        if(i>n*2){
            cout<<0;
            return 0;
        }
        int qwq;
        cin>>qwq;
        if(qwq==c[i-1]){
            m--;
            i--;
        }else{
            c[i]=qwq;
            col[c[i]].push_back(i);
        }
    }
    memset(f,-1,sizeof(f));
    cout<<dfs(1,m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            cerr<<f[i][j]<<" ";
        }
        cerr<<'\n';
    }
    return 0;
}
