#include <bits/stdc++.h>
using namespace std;

int K,n;
int xa=0;
int ans=0;
vector<int> a,matchv,mattv;
vector<char> vis;

int getrd(int x){ 
    return rand()%x;
}

void solve(){
    vector<int> vct;
    for(int i=0;i<n;i++)
        if(matchv[i]==-1) vct.push_back(i);
    if(vct.empty()) return;

    int u=vct[getrd((int)vct.size())];

    vct.clear();
    for(int i=0;i<n;i++)
        if(mattv[i]==-1 && !vis[u^a[i]])
            vct.push_back(i);

    if(!vct.empty()){
        int v=vct[getrd((int)vct.size())];
        matchv[u]=v;
        mattv[v]=u;
        vis[u^a[v]]=1;
        ans++;
        return;
    }

    vct.clear();
    for(int i=0;i<n;i++)
        if(mattv[i]==-1) vct.push_back(i);
    if(vct.empty()) return;

    int v=vct[getrd((int)vct.size())];
    for(int i=0;i<n;i++){
        if(matchv[i]!=-1 && (i^a[matchv[i]])==(u^a[v])){
            mattv[matchv[i]]=-1;
            matchv[i]=-1;
            matchv[u]=v;
            mattv[v]=u;
            return;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)time(0));

    cin>>K;
    n=1<<K;

    a.assign(n,0);
    matchv.assign(n,-1);
    mattv.assign(n,-1);
    vis.assign(n,0);
    xa=0;

    for(int i=0;i<n;i++){
        cin>>a[i];
        xa^=a[i];
    }
    if(xa){
        cout<<"Fou\n";
        return 0;
    }

    while(1.0*clock()/CLOCKS_PER_SEC<=0.95) solve();

    cout<<"Shi\n";
    for(int i=0;i<n;i++) cout<<mattv[i]<<' ';
    cout<<"\n";
    for(int i=0;i<n;i++) cout<<(mattv[i]^a[i])<<' ';
    cout<<"\n";
    return 0;
}
