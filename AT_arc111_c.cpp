#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],p[MN],revp[MN],st[MN],top;
bool vis[MN];
vector<pir> ans;

bool cmp(int x,int y){
    return a[x]<a[y];
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>p[i];
        revp[p[i]]=i;
        if(a[i]<=b[p[i]]&&i!=p[i]){
            cout<<-1;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i]||i==p[i]) continue;
        top=0;
        int it=i;
        while(!vis[it]){
            vis[it]=1;
            st[++top]=it;
            it=p[it];
        }
        sort(st+1,st+1+top,cmp);
        for(int j=1;j<top;j++){
            int now=st[j];
            ans.push_back(pir(now,revp[now]));
            p[revp[now]]=p[now];
            revp[p[now]]=revp[now];
        }
    }
    cout<<ans.size()<<'\n';
    for(auto p:ans){
        cout<<p.first<<' '<<p.second<<'\n';
    }

    return 0;
}