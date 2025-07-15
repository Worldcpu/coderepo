#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
struct QNode{
    int val,id;

    bool operator <(const QNode &x)const{
        return val<x.val;
    }
};
struct Node{
    int val,l,r;
}a[MN];
int n,m,ans;
bool vis[MN];
priority_queue<QNode> q;

void del(int x){
    a[x].l=a[a[x].l].l;
    a[x].r=a[a[x].r].r;
    a[a[x].l].r=x;
    a[a[x].r].l=x;
}

int main(){
    cin>>n>>m;
    if(n/2<m){
        cout<<"Error!";
        return 0;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i].val;
        a[i].l=i-1,a[i].r=i+1;
        q.push({a[i].val,i});
    }
    a[1].l=n,a[n].r=1;
    for(int i=1;i<=m;i++){
        while(vis[q.top().id]) q.pop();
        auto now=q.top();
        q.pop();
        vis[a[now.id].l]=vis[a[now.id].r]=1;
        a[now.id].val=a[a[now.id].l].val+a[a[now.id].r].val-a[now.id].val;
        q.push({a[now.id].val,now.id});
        ans+=now.val;
        del(now.id);
    }
    cout<<ans;
    return 0;
}
