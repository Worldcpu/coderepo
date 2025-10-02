#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=114,MOD=1e8+7;
constexpr int fx[2]={0,1},fy[2]={1,0};
int n,m;
char mp[MN][MN];

struct Node{
    int ans,s0,s1,num;

    Node(int a=0,int b=0,int c=0,int d=0){
        ans=a,s0=b,s1=c,num=d;
    }

    void clear(){
        ans=0,s0=0,s1=0,num=0;
    }

    friend Node operator+(const Node &x,const Node &y){
        Node ret;
        ret.ans=(x.ans+y.ans)%MOD;
        ret.s0=(x.s0+y.s0)%MOD;
        ret.s1=(x.s1+y.s1)%MOD;
        ret.num=(x.num+y.num)%MOD;
        return ret;
    }

    friend Node operator+(const Node &x,const char ch){
        if(ch=='+'){
            return Node((x.ans+x.s1)%MOD,x.num,0,x.num);
        }
        if(ch=='*'){
            return Node(x.ans,x.s1,0,x.num);
        }
        return Node(x.ans,x.s0,(x.s1*10+x.s0*(ch-'0')),x.num);

    }
}f[MN][MN],g[MN][MN];

bool isop(char x){
    return (x=='*'||x=='+');
}

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j].clear();
            g[i][j].clear();
        }
    }

}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
        }
    }
    if(mp[1][1]=='0'){
        g[1][1]=Node(0,0,0,1);
    }else f[1][1]=Node(0,1,mp[1][1]-'0',1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<2;k++){
                int ni=i+fx[k],nj=j+fy[k];
                if(ni>=1&&ni<=n&&nj>=1&&nj<=m&&!(isop(mp[i][j])&&isop(mp[ni][nj]))){
                    if(isop(mp[ni][nj])&&mp[i][j]=='0'){
                        f[ni][nj]=f[ni][nj]+(g[i][j]+mp[ni][nj]);
                    }
                    if(isop(mp[i][j])&&mp[ni][nj]=='0'){
                        g[ni][nj]=g[ni][nj]+(f[i][j]+mp[i][nj]);
                    }
                    if(!isop(mp[i][j])||mp[ni][nj]!='0'){
                        f[ni][nj]=f[ni][nj]+(f[i][j]+mp[ni][nj]);
                    }
                }
            }
        }
    }
    cout<<(f[n][m].ans+g[n][m].ans+f[n][m].s1)%MOD<<'\n';
}

signed main(){
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
    int qwq,T;
    cin>>qwq>>T;
    while(T--){
        solve();
    }
    return 0;
}