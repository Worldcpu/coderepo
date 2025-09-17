#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,m,b[MN];
vector<int> qwq;

int dfs(vector<int> vct,int k){
    if(vct.empty()) return 0;
    if(k==m+1){
        int sum=0;
        for(auto p:vct) sum+=p;
        return sum;
    }
    vector<int> a,bb;
    for(auto p:vct){
        if(p%b[k]==0) a.push_back(p);
        else bb.push_back(p);
    }
    if(!(k&1)) return max(dfs(a,k+1),dfs(bb,k+1));
    else return min(dfs(a,k+1),dfs(bb,k+1));
}

signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    cin>>n>>m;
    if(m>=30){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        qwq.push_back(x);       
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    cout<<dfs(qwq,1);

    return 0;
}