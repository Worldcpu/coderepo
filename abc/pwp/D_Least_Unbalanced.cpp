#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,K,ans;
vector<int> vct;

void dfs(int cnt,int sum){
    if(cnt==n){
        vct.push_back(sum);
        return;
    }
    int ret=sum/2;
    dfs(cnt+1,ret);
    dfs(cnt+1,sum-ret);
}

int calc(){
    int x=0,n=vct.size();
    vector<int> b=vct,c;
    while(n>1){
        c.clear();
        int mn=*min_element(b.begin(),b.end()),mx=*max_element(b.begin(),b.end());
        x=max(x,mx-mn);
        c.reserve(n/2);
        for(int i=0;i<n/2;i++){
            c[i]=b[2*i]+b[2*i+1];
        }
        b=move(c);
        n=b.size();
    }
    return x;
}

signed main(){
    cin>>n>>K;
    dfs(0,K);
    cout<<calc()<<'\n';
    for(auto p:vct) cout<<p<<' ';
    return 0;
}