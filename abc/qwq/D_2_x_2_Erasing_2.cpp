#include<bits/stdc++.h>
using namespace std;
constexpr int MN=10,INF=1e9;
int n,m,f[MN][1<<MN],btot,hst[MN],ret;
char mp[MN][MN];

void init(){
    btot=0;
    memset(f,128,sizeof(f)); 
}

bool check2x2(int mask1,int mask2,int w){
    for(int j=0;j<w-1;j++){
        int b1=(mask1>>j)&3;
        int b2=(mask2>>j)&3;
        if(b1==3 && b2==3) return 0; 
    }
    return 1;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        int row=0;
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#') row|=(1<<(j-1)), btot++;
        }
        hst[i]=row;
    }

    for(int i=0;i<(1<<m);i++){
        if((i&hst[1])==i) f[1][i]=__builtin_popcount(i);
    }

    for(int i=2;i<=n;i++){
        for(int cur=0;cur<(1<<m);cur++){
            if((cur&hst[i])!=cur) continue; 
            f[i][cur]=-INF;
            for(int pre=0;pre<(1<<m);pre++){
                if((pre&hst[i-1])!=pre) continue;
                if(f[i-1][pre]<0) continue;
                if(check2x2(pre,cur,m)){
                    f[i][cur]=max(f[i][cur],f[i-1][pre] + __builtin_popcount(cur));
                }
            }
        }
    }

    ret=0;
    for(int i=0;i<(1<<m);i++){
        ret=max(ret,f[n][i]);
    }
    cout<<btot-ret<<'\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
}
