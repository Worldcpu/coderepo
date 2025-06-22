#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e3+15;
constexpr double INF=1e18;
struct Node{
    double x,y;
    int id;
}a[MN],b[MN];
double f[MN][MN][2];
int n,mx,pre[MN][MN][2];

double dis(int x,int y){
    return sqrt((b[x].x-b[y].x)*(b[x].x-b[y].x)+(b[x].y-b[y].y)*(b[x].y-b[y].y));
}

void getpre(int l,int r,int op){
    if(l==r){
        cout<<b[l].id<<" ";
        return;
    }
    if(op) cout<<b[r].id<<" ",getpre(l,r-1,pre[l][r][op]);
    else cout<<b[l].id<<" ",getpre(l+1,r,pre[l][r][op]);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
    }
    mx=1;
    for(int i=2;i<=n;i++) if(a[i].y>a[mx].y) mx=i;
    for(int i=1;i<=mx;i++) b[i+n-mx]=a[i];
    for(int i=mx+1;i<=n;i++) b[i-mx]=a[i];
    for(int len=2;len<n;len++){
        for(int l=1,r=len;r<n;l++,r++){
            f[l][r][0]=f[l][r][1]=INF;
            if(f[l][r][0]>f[l+1][r][0]+dis(l,l+1)){
                f[l][r][0]=f[l+1][r][0]+dis(l,l+1);
                pre[l][r][0]=0;
            }
            if(f[l][r][0]>f[l+1][r][1]+dis(l,r)){
                f[l][r][0]=f[l+1][r][1]+dis(l,r);
                pre[l][r][0]=1;
            }
            if(f[l][r][1]>f[l][r-1][0]+dis(l,r)){
                f[l][r][1]=f[l][r-1][0]+dis(l,r);
                pre[l][r][1]=0;
            }
            if(f[l][r][1]>f[l][r-1][1]+dis(r,r-1)){
                f[l][r][1]=f[l][r-1][1]+dis(r,r-1);
                pre[l][r][1]=1;
            }
        }
    }
    cout<<b[n].id<<" ";
    if(f[1][n-1][0]+dis(1,n)>f[1][n-1][1]+dis(n-1,n))
        getpre(1,n-1,1);
    else getpre(1,n-1,0);
    return 0;
}
