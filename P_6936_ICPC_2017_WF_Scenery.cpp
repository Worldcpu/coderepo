#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Node{
    int l,r;
}q[MN];
int n,t,L[MN],R[MN],f[MN],g[MN],p[MN];

bool cmp(Node x,Node y){
    if(x.l==y.l) return x.r<y.r;
    return x.l<y.l;
}

int main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++){
        cin>>q[i].l>>q[i].r;
        R[i]=q[i].r;
        L[i]=q[i].l;
        p[i]=n;
    }
    sort(q+1,q+1+n,cmp);
    sort(L+1,L+1+n);
    sort(R+1,R+1+n);
    for(int i=1;i<=n;i++) f[i]=R[i],g[i]=q[i].l;
    for(int i=n;i>=1;i--){
        for(int j=n;R[j]>=q[i].r;j--){
            f[j]-=t;
            while(p[j]>i&&f[j]<q[p[j]].l){
                f[j]=min(f[j],g[p[j]]);
                p[j]--;
            }
            if(f[j]<q[i].l){
                cout<<"no";
                return 0;
            }
            g[i]=min(g[i],f[j]-t);
        }
    }
    cout<<"yes";
    return 0;
}