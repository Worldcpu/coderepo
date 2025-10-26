#include<bits/stdc++.h>
using namespace std;
constexpr int MN=15;
int n,K,a[MN],b[MN],s,c[MN];
bool vise[MN],visd[MN];

bool dfs(int pos){
    if(pos==K+1){
        for(int i=1;i<=s;i++){
            if(!visd[c[i]]) return 0; 
        }
        return 1;
    }
    if(!visd[a[pos]]&&!visd[b[pos]]){
        visd[b[pos]]=1;
        vise[pos]=1;
        int ret=dfs(pos+1);
        if(ret){
            return 1;
        }
        visd[b[pos]]=0;
        vise[pos]=0;
        return dfs(pos+1);
    }else{
        return dfs(pos+1);
    }
}

void init(){
    for(int i=1;i<=n;i++){
        visd[i]=0;
    }
    for(int i=1;i<=K;i++){
        vise[i]=0;
    }
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=K;i++){
        cin>>a[i]>>b[i];
    }
    cin>>s;
    for(int i=1;i<=s;i++){
        cin>>c[i];
    }
    if(dfs(1)){
        cout<<"TAK\n";
        for(int i=1;i<=K;i++){
            cout<<(vise[i]?"T":"N");
        }
        cout<<'\n';
    }else cout<<"NIE\n";
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}