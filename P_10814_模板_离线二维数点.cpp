#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
struct Query{
    int x,op,id;
};
int n,m,a[MN],ans[MN];
vector<Query> qry[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int l,r,x;
        cin>>l>>r>>x;
        qry[l-1].push_back({x,-1,i});
        qry[r].push_back({x,1,i});
    }
    for(int i=1;i<=n;i++){
        bit.update(a[i],1);
        for(auto v:qry[i]){
            ans[v.id]+=v.op*bit.query(v.x);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}
