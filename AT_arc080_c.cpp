#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int ML=30,MN=5e5+15,INF=1e9;
int n,p[MN];
vector<int> ans;

struct Node{
    int l,r,x,y;

    friend bool operator>(const Node &x,const Node &y){
        return p[x.x]>p[y.x];
    }
};
priority_queue<Node,vector<Node>,greater<Node>> q;

namespace ST{
    int st[2][ML+2][MN];

    int cmp(int x,int y){
        return (p[x]<p[y]?x:y);
    }

    void initst(){
        for(int i=1;i<=ML;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[0][i][j]=cmp(st[0][i-1][j],st[0][i-1][j+(1<<i-1)]);
                st[1][i][j]=cmp(st[1][i-1][j],st[1][i-1][j+(1<<i-1)]);
            }
        }
    }

    int query(int l,int r,int id){
        int lg=__lg(r-l+1);
        return cmp(st[id][lg][l],st[id][lg][r-(1<<lg)+1]);
    }

}using namespace ST;

pir cut(int l,int r){
    pir ans;
    ans.first=query(l,r,l&1);
    ans.second=query(ans.first,r,r&1);
    return ans;
}

int main(){
    cin>>n;
    p[0]=INF;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        st[i&1][0][i]=i;
    }
    for(int i=1;i<=n;i++){
        cerr<<st[0][0][i]<<' ';
    }
    cerr<<'\n';
    for(int i=1;i<=n;i++){
        cerr<<st[1][0][i]<<' ';
    }
    cerr<<'\n';
    initst();
    auto qwq=cut(1,n);
    cerr<<qwq.first<<' '<<qwq.second<<'\n';
    q.push({1,n,qwq.first,qwq.second});
    while(!q.empty()){
        auto tp=q.top();
        q.pop();
        ans.push_back(p[tp.x]);
        ans.push_back(p[tp.y]);
        if(tp.l<tp.x-1){
            auto tmp=cut(tp.l,tp.x-1);
            q.push({tp.l,tp.x-1,tmp.first,tmp.second});
        }
        if(tp.x+1<tp.y-1){
            auto tmp=cut(tp.x+1,tp.y-1);
            q.push({tp.x+1,tp.y-1,tmp.first,tmp.second});
        }
        if(tp.y+1<tp.r){
            auto tmp=cut(tp.y+1,tp.r);
            q.push({tp.y+1,tp.r,tmp.first,tmp.second});
        }
    }
    for(auto p:ans) cout<<p<<' ';
    return 0;
}