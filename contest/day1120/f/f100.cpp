#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18,ML=30;
int n,a[MN],lim[MN],f[MN],res;
priority_queue<pir,vector<pir>,greater<pir>> q;
unordered_map<int,set<int>> mp;
unordered_map<int,bool> vis;
vector<int> fib;

void init(){
    int fx=0,fy=1;
    fib.push_back(fx);
    fib.push_back(fy);
    for(int i=2;;i++){
        int tmp=fx+fy;
        if(tmp>2e9) break;
        swap(fx,fy);
        fy=tmp;
        fib.push_back(tmp);
    }
    for(auto p:fib) vis[p]=1;
}

signed main(){
    // freopen("f.in","r",stdin);
    // freopen("f.out","w",stdout);
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(auto p:fib){
            if(p-a[i]<0) continue;
            int k=p-a[i];
            if(mp[k].size()){
                res++;
                mp.clear();
            }
        }
        mp[a[i]].insert(i);
    }
    cout<<res+1;
    return 0;
}