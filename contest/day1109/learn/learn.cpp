#include<bits/stdc++.h>
using namespace std;
constexpr int MN=10;
int n,m,K,p[MN],r[MN],t[MN],x[MN],lst,ans=1e9;
bool vis[MN];
set<int> st;
unordered_map<int,int> cnt;

void dfs(int stp){
    if(ans<stp) return;
    if(!lst){
        ans=min(ans,stp); 
        return;
    }
    if(st.size()>=K){
        auto qwq=st;
        for(auto p:qwq){
            st.erase(p);
            dfs(stp);
            st.insert(p);
        }
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            st.insert(i);
            lst-=cnt[i];
            if(st.count(p[i])){
                dfs(stp+t[i]);
            }
            dfs(stp+r[i]);
            lst+=cnt[i];
            st.erase(i);
            vis[i]=0;
        }
    }
}

int main(){
    freopen("learn.in","r",stdin);
    freopen("learn.out","w",stdout);
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        cin>>r[i];
    }
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=1;i<=m;i++){
        cin>>x[i];
        cnt[x[i]]++;
    }
    lst=m;
    dfs(0);
    cout<<ans;
    return 0;
}