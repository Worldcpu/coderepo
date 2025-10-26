#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int a[MN],b[MN],n,K,stot;
bool vise[MN],inS[MN],del[MN];
map<int,int> mp;

void init(){
    for(int i=1;i<=n;i++){
        inS[i]=del[i]=0;
    }
    for(int i=1;i<=K;i++){
        vise[i]=0;
    }
    mp.clear();
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=K;i++){
        cin>>a[i]>>b[i];
    }
    cin>>stot;
    for(int i=1;i<=stot;i++){
        int x;
        cin>>x;
        inS[x]=1;
    }
    for(int i=K;i>=1;i--){
        if(inS[b[i]]&&!mp[b[i]]){
            if(inS[a[i]]&&!mp[a[i]]) continue;
            mp[b[i]]=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(inS[i]&&!mp[i]){
            cout<<"NIE\n";
            return;
        }
    }
    for(int i=1;i<=n;i++){
        if(inS[i]){
            vise[mp[i]]=1;
        }
    }
    cout<<"TAK\n";
    for(int i=1;i<=K;i++){
        if(vise[i]){
            cout<<"T";
        }else cout<<"N";
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}