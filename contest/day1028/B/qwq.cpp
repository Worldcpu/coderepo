#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[2][8];

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

// 检查子集 mask 是否是非空且边连通
bool is_connected(int mask) {
    if(mask == 0) return false;
    vector<vector<int>> id(2, vector<int>(n));
    int cnt = 0;
    for(int x=0;x<2;x++)
        for(int y=0;y<n;y++)
            if(mask & (1<<(x*n+y))) id[x][y]=1;

    // 找到第一个格子做 BFS
    queue<pair<int,int>> q;
    bool vis[2][8]={0};
    bool found=false;
    for(int x=0;x<2&&!found;x++)
        for(int y=0;y<n&&!found;y++)
            if(id[x][y]){q.push({x,y});vis[x][y]=1;found=true;}

    if(!found) return false;

    int reached=0;
    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        reached++;
        for(int d=0;d<4;d++){
            int nx=x+dx[d], ny=y+dy[d];
            if(nx<0||nx>=2||ny<0||ny>=n) continue;
            if(id[nx][ny]&&!vis[nx][ny]){
                vis[nx][ny]=1;
                q.push({nx,ny});
            }
        }
    }

    // 统计子集总格数
    int total=__builtin_popcount(mask);
    return reached==total;
}

// 翻转指定列集合 T
void flip_cols(int b[2][8], int maskT){
    for(int j=0;j<n;j++){
        if(maskT & (1<<j)) swap(b[0][j], b[1][j]);
    }
}

// 计算当前 b 下集合 S 的 V 值
int calc_V(int b[2][8], int maskS){
    int v=0;
    for(int x=0;x<2;x++){
        for(int y=0;y<n;y++){
            if(maskS & (1<<(x*n+y))){
                v += (b[x][y]==1 ? 1 : -1);
            }
        }
    }
    return v;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int subt,T;
    cin>>subt>>T;
    while(T--){
        cin>>n>>m;
        string s1,s2;cin>>s1>>s2;
        for(int j=0;j<n;j++) a[0][j]=s1[j]-'0';
        for(int j=0;j<n;j++) a[1][j]=s2[j]-'0';

        int ans=-1e9;

        // 枚举所有可能连通块 S
        int total_cells = 2*n;
        for(int maskS=1; maskS<(1<<total_cells); maskS++){
            if(!is_connected(maskS)) continue;

            int worst = 1e9;
            // 枚举所有翻列集合 T，|T|<=m
            for(int maskT=0; maskT<(1<<n); maskT++){
                if(__builtin_popcount(maskT)>m) continue;

                int b[2][8];
                memcpy(b,a,sizeof(a));
                flip_cols(b,maskT);
                int v = calc_V(b,maskS);
                worst = min(worst, v);
            }
            ans = max(ans, worst);
        }

        cout<<ans<<"\n";
    }
}