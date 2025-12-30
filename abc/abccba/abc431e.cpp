#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,INF=1e18;
constexpr int fx[]={0,1,0,-1}, fy[]={1,0,-1,0};
const string fg="ABC";

struct Node{
    int x, y, f;
};
int n, m, ans;
string st[MN];

vector<int> dis[4][MN];
vector<bool> vis[4][MN];

void nxtpos(int x, int y, int f, char c, int &nx, int &ny, int &nf){
    if(c=='A') nf=f;
    else if(c=='B') nf=(5-f)%4;
    else nf=3-f;
    nx = x + fx[nf];
    ny = y + fy[nf];
}

void dijk(){
    deque<Node> q;
    dis[0][1][1]=0;
    q.push_back({1,1,0});
    ans = INF;

    while(!q.empty()){
        auto [x, y, f] = q.front(); q.pop_front();
        if(vis[f][x][y]) continue;
        vis[f][x][y]=1;
        for(char c : fg){
            int nx, ny, nf;
            nxtpos(x, y, f, c, nx, ny, nf);
            int nd = dis[f][x][y] + (st[x][y]==c?0:1);
            if(nx==n && ny==m+1 && nf==0) ans = min(ans, nd);
            if(nx<1 || nx>n || ny<1 || ny>m) continue;
            if(nd < dis[nf][nx][ny]){
                dis[nf][nx][ny] = nd;
                if(st[x][y]==c) q.push_front({nx, ny, nf});
                else q.push_back({nx, ny, nf});
            }
        }
    }
}

void init(){
    for(int i=0;i<4;i++){
        for(int j=1;j<=n;j++){
            dis[i][j].clear();
            dis[i][j].resize(m+1);
            fill(dis[i][j].begin(),dis[i][j].end(),INF);
            vis[i][j].clear();
            vis[i][j].resize(m+1);
            fill(vis[i][j].begin(),vis[i][j].end(),0);
        }
    }
}

void solve(){
    cin >> n >> m;
    init();
    for(int i=1;i<=n;i++){
        cin >> st[i];
        st[i] = " " + st[i];
    }
    dijk();
    cout << ans << '\n';
}

signed main(){
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
