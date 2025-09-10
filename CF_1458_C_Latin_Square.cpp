#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int a[MN][MN][3],b[MN][MN],n,m,f[3],g[3],p[MN];
string op;

void init(){
    for(int i=0;i<3;i++){
        f[g[i]=i]=0;
        p[i]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            memset(a[i][j],0,sizeof(a[i][j]));
            b[i][j]=0;
        }
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j][2];
            a[i][j][2]--;
            a[i][j][0]=i;
            a[i][j][1]=j;
        }
    }
    cin>>op;
    op=" "+op;
    for(int i=1;i<=m;i++){
        if(op[i]=='L') f[1]--;
        if(op[i]=='R') f[1]++;
        if(op[i]=='U') f[0]--;
        if(op[i]=='D') f[0]++;
        if(op[i]=='I'){
            swap(g[1],g[2]);
            swap(f[1],f[2]);
        }
        if(op[i]=='C'){
            swap(g[0],g[2]);
            swap(f[0],f[2]);
        }
    }
    for(int i=0;i<3;i++){
        f[i]=(f[i]%n+n)%n;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<3;k++){
                p[k]=(a[i][j][g[k]]+f[k])%n;
            }
            b[p[0]][p[1]]=p[2];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<b[i][j]+1<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}