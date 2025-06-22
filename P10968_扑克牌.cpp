#include<bits/stdc++.h>
using namespace std;
constexpr int MN=25;
constexpr double INF=1e18;
int A,B,C,D;
bool vis[MN][MN][MN][MN][5][5];
double dp[MN][MN][MN][MN][5][5];

double dfs(int a,int b,int c,int d,int e,int f){
    if(vis[a][b][c][d][e][f]) return dp[a][b][c][d][e][f];
    vis[a][b][c][d][e][f]=1;
    int sum=a+b+c+d+(e!=0)+(f!=0);
    double val=0;
    if(a>13||b>13||c>13||d>13||sum>54){
        dp[a][b][c][d][e][f]=INF;
        return dp[a][b][c][d][e][f];
    }
    if(a+(e==1)+(f==1)>=A&&b+(e==2)+(f==2)>=B&&c+(e==3)+(f==3)>=C&&d+(e==4)+(f==4)>=D) dp[a][b][c][d][e][f]=0;
    else{
        val+=(13.0-a)/(54.0-sum)*dfs(a+1,b,c,d,e,f);
        val+=(13.0-b)/(54.0-sum)*dfs(a,b+1,c,d,e,f);
        val+=(13.0-c)/(54.0-sum)*dfs(a,b,c+1,d,e,f);
        val+=(13.0-d)/(54.0-sum)*dfs(a,b,c,d+1,e,f);
        if(e==0){
            double minn=INF;
            for(int i=1;i<=4;i++) minn=min(minn,dfs(a,b,c,d,i,f));
            val+=1.0/(54.0-sum)*minn;
        }
        if(f==0){
            double minn=INF;
            for(int i=1;i<=4;i++) minn=min(minn,dfs(a,b,c,d,e,i));
            val+=1.0/(54.0-sum)*minn;
        }
        dp[a][b][c][d][e][f]=val+1.0;
    }
    return dp[a][b][c][d][e][f];
}

void solve(){
    cin>>A>>B>>C>>D;
    memset(dp,0,sizeof(dp));
    memset(vis,0,sizeof(vis));
    dfs(0,0,0,0,0,0);
    if(dp[0][0][0][0][0][0]>54) cout<<"-1.000\n";
    else cout<<fixed<<setprecision(3)<<dp[0][0][0][0][0][0]<<'\n';
}

int main(){
    int T,cnt=0;
    cin>>T;
    while(T--){
        cout<<"Case "<<++cnt<<": ";
        solve();
    }
    return 0;
}
