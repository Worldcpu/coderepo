#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=18;
int tr=-1, tc=-1,n,m;
char a[MN][MN];
queue<string> q;
unordered_map<string,int> dist;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    string start;
    start.resize(n*m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if(a[i][j]=='T'){ tr=i; tc=j; start[i*m+j]='.'; }
        else if(a[i][j]=='#') start[i*m+j]='#';
        else start[i*m+j]='.';
    }
    dist.reserve(1<<16);
    dist[start]=0;
    q.push(start);
    int dx[4]={-1,1,0,0}, dy[4]={0,0,-1,1};
    while(!q.empty()){
        string s=q.front(); q.pop();
        int d=dist[s];
        bool empty=true;
        for(char ch: s) if(ch=='#'){ empty=false; break; }
        if(empty){ cout<<d<<"\n"; return 0; }
        for(int k=0;k<4;k++){
            string t(n*m, '.');
            bool bad=false;
            for(int i=0;i<n && !bad;i++){
                for(int j=0;j<m;j++){
                    if(s[i*m+j]=='#'){
                        int ni=i+dx[k], nj=j+dy[k];
                        if(ni<0||ni>=n||nj<0||nj>=m) continue;
                        if(ni==tr && nj==tc){ bad=true; break; }
                        t[ni*m+nj] = '#';
                    }
                }
            }
            if(bad) continue;
            if(!dist.count(t)){
                dist[t]=d+1;
                q.push(t);
            }
        }
    }
    cout<<-1<<"\n";
    return 0;
}
