#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,a[MN],L[MN],R[MN],col,lst[MN],ans[MN];
vector<pir> qry[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int queryqwq(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int x){
        return queryqwq(MN-1)-queryqwq(x-1);
    }
}bit;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!L[a[i]]){
            L[a[i]]=i;
            col++;
        }
        R[a[i]]=i;
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        qry[r].push_back(pir(l,i));
    }
    for(int i=1;i<=n;i++){
        if(R[a[i]]==i){
            bit.modify(L[a[i]],-1);
            if(lst[a[i]-1]){
                bit.modify(min(lst[a[i]-1],L[a[i]]),1);
            }
        }
        if(!L[a[i]+1]){
            bit.modify(i,1);
            if(lst[a[i]]) bit.modify(lst[a[i]],-1);
        }else if(R[a[i]+1]<i&&lst[a[i]]<L[a[i]+1]){
            bit.modify(L[a[i]+1],1);
            if(lst[a[i]]) bit.modify(lst[a[i]],-1);
        }
        lst[a[i]]=i;
        for(auto p:qry[i]){
            ans[p.second]=bit.query(p.first)+col;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}