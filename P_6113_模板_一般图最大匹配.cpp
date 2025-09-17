#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int K,n,xa,a[MN],match[MN],matt[MN],ans;
bool vis[MN];

int getrd(int x){ // output random number in [1,x]
    return (rand()*rand()+rand())%x;
}

void solve(){
    vector<int> vct;
    for(int i=0;i<n;i++){
        if(match[i]==-1) vct.push_back(i);
    }
    if(vct.empty()) return;
    int u=vct[getrd(vct.size())];
    vct.clear();
    for(int i=0;i<n;i++){
        if(matt[i]==-1&&!vis[u^a[i]]){
            vct.push_back(i);
        }
    }
    if(vct.size()){
        int v=vct[getrd(vct.size())];
        match[u]=v;
        matt[v]=u;
        vis[u^a[v]]=1;
        ans++;
        return;
    }
    for(int i=0;i<n;i++){
        if(matt[i]==-1){
            vct.push_back(i);
        }
    }
    int v=vct[getrd(vct.size())];
    for(int i=0;i<n;i++){
        if(~match[i]&&(i^a[match[i]])==(u^a[v])){
            matt[match[i]]=-1;
            match[i]=-1;
            match[u]=v;
            matt[v]=u;
            return;
        }
    }
}

int main(){
    memset(match,-1,sizeof(match));
    memset(matt,-1,sizeof(matt));
    srand(time(0));
    cin>>K;
    n=(1<<K);
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
    for(int i=0;i<n;i++){
        cout<<matt[i]<<' ';
    }
    cout<<'\n';
    for(int i=0;i<n;i++){
        cout<<(matt[i]^a[i])<<' ';
    }


    return 0;
}