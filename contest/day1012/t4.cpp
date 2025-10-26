#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int n,q,lson[MN],rson[MN],a[MN];
vector<int> ans;

void dfs(int u){
    if(!u) return;
    if(a[u]==-1){
        ans.push_back(u);
        dfs(lson[u]);
        dfs(rson[u]);
    }else if(a[u]==0){
        dfs(lson[u]);
        ans.push_back(u);
        dfs(rson[u]);
    }else{
        dfs(lson[u]);
        dfs(rson[u]);
        ans.push_back(u);
    }
}

int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>lson[i]>>rson[i];
        a[i]=-1;
    }
    while(q--){
        int op,l,r,x;
        cin>>op;
        if(op==1){
            cin>>l>>r>>x;
            for(int i=l;i<=r;i++) a[i]=x;
        }else{
            cin>>x;
            ans.clear();
            ans.push_back(0);
            dfs(1);
            for(int i=1;i<=n;i++){
                if(ans[i]==x){
                    cout<<i<<'\n';
                    break;
                }
            }
        }
    }

    return 0;
}