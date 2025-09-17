#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15;
struct Node{
    int a,b,c,id;

}a[MN];
struct PNode{
    int a,b,c,id,tim;

    PNode(Node x,int t){
        a=x.a,b=x.b,c=x.c,id=x.id,tim=t;
    }

    friend bool operator>(const PNode &x,const PNode &y){
        return x.tim>y.tim;
    }
};
int n,K,T,pcnt,ans[MN];
priority_queue<PNode,vector<PNode>,greater<PNode>> q;

bool cmp(Node x,Node y){
    return x.a<y.a;
}

signed main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i].a>>a[i].b>>a[i].c;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    ans[a[1].id]=a[1].a;
    T=a[1].a;
    pcnt=a[1].c;
    q.push(PNode(a[1],T+a[1].b));
    for(int i=2;i<=n;i++){
        if(pcnt+a[i].c>K){
            while(!q.empty()&&pcnt+a[i].c>K){
                auto tp=q.top();
                q.pop();
                T=tp.tim;
                pcnt-=tp.c;
            }
            T=max(T,a[i].a);
            ans[a[i].id]=T;
            pcnt+=a[i].c;
            q.push(PNode(a[i],T+a[i].b));
        }else{
            pcnt+=a[i].c;
            T=max(T,a[i].a);
            ans[a[i].id]=T;
            q.push(PNode(a[i],T+a[i].b));
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}