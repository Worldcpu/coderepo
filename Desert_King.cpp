#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e6+15;
constexpr double eps=1e-8;
struct Node{
    int x,y,z;
}pt[MN];
struct Edge
{
    int u,v;
    double w;
}e[MN];
int n,etot,pre[MN];

double getdis(int i,int j){
    return sqrt((double)(pt[i].x-pt[j].x)*(pt[i].x-pt[j].x)+(double)(pt[i].y-pt[j].y)*(pt[i].y-pt[j].y));
}

int root(int x){
    if(pre[x]==x) return x;
    else return pre[x]=root(pre[x]);
}

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

bool check(double k){
    double sum=0;
    etot=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            e[++etot].u=i;
            e[etot].v=j;
            e[etot].w=abs(pt[i].z-pt[j].z)-k*getdis(i,j);
        }
        pre[i]=i;
    }
    sort(e+1,e+1+etot,cmp);
    for(int i=1;i<=etot;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru==rv) continue;
        if(e[i].w<0) continue;
        sum+=e[i].w;
        pre[rv]=ru;
    }
    return sum>=0;
}

void solve(){
    for(int i=1;i<=n;i++){
        cin>>pt[i].x>>pt[i].y>>pt[i].z;
    }
    double l=1,r=100;
    while(l+eps<r){
        double mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<fixed<<setprecision(3)<<r<<'\n';
}

int main(){
    while(1){
        cin>>n;
        if(n==0) break;
        solve();
    }
    return 0;
}