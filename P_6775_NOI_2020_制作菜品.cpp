#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MM=505,MN=2500000;
int n,m,K,d[MM];
bool vis[MM];
vector<int> vct;
bitset<10000*MM> f[MM];

void init(){
    vct.clear();
    for(int i=1;i<=n;i++){
        f[i].reset();
        vis[i]=0;
    }
}

void solve1(){
    set<pir> s;
    for(auto p:vct){
        s.insert(pir(d[p],p));
    }
    while(!s.empty()){
        pir fr=*s.begin(),bk=*s.rbegin();
        s.erase(fr);
        while(fr.first>=K){
            fr.first-=K;
            cout<<fr.second<<' '<<K<<'\n';
        }
        if(!fr.first) continue;
        s.erase(bk);
        int tmp=K-fr.first;
        cout<<fr.second<<' '<<fr.first<<' '<<bk.second<<' '<<tmp<<'\n';
        bk.first-=tmp;
        s.insert(bk);
    }
    vct.clear();
}

void divide(){
    f[0].reset();
    f[0][MN]=1;
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        if(d[i]>K){
            f[i]|=f[i-1]<<(d[i]-K);
        }else f[i]|=f[i-1]>>(K-d[i]);
    }
    if(!f[n][MN-K]){
        cout<<-1<<'\n';
        return;
    }
    int x=n,y=MN-K;
    while(x){
        if(f[x-1][y-(d[x]-K)]){
            y-=(d[x]-K);
            vis[x]=1;
            vct.push_back(x);
        }
        x--;
    }
    solve1();
    for(int i=1;i<=n;i++){
        if(!vis[i]) vct.push_back(i);
    }
    solve1();
}

void solve(){
    cin>>n>>m>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }
    if(m!=n-2){
        for(int i=1;i<=n;i++){
            vct.push_back(i);
        }
        solve1();
    }else{
        divide();
    }

}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}