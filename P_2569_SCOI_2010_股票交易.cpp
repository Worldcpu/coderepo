#include<bits/stdc++.h>
using namespace std;
const int MN=2015;
struct youaremyidolQUEUE{
    int ap,bp,as,bs;
}d[MN];
int f[MN][MN],n,m,w,q[MN],ql,qr;

bool isnotokap(int i,int j,int k){
    return f[i-w-1][k]+d[i].ap*k<=f[i-w-1][j]+d[i].ap*j;
}

bool isnotokbp(int i,int j,int k){
    return f[i-w-1][k]+d[i].bp*k<=f[i-w-1][j]+d[i].bp*j;
}

int main(){
    memset(f,128,sizeof(f));
    cin>>n>>m>>w;
    for(int i=1;i<=n;i++){
        cin>>d[i].ap>>d[i].bp>>d[i].as>>d[i].bs;
    }
    for(int i=1;i<=n;i++){
        
        for(int j=0;j<=d[i].as;j++){
            f[i][j]= -1*d[i].ap*j;
            
        }
        for(int j=0;j<=m;j++){
            f[i][j]=max(f[i][j],f[i-1][j]);
        }
        if(i<=w) continue;
        ql=1,qr=0;
        for(int j=0;j<=m;j++){
            while(ql<=qr&&q[ql]<j-d[i].as) ql++;
            while(ql<=qr&&isnotokap(i,j,q[qr])){
                qr--;
            }
            q[++qr]=j;
            if(ql<=qr){
                f[i][j]=max(f[i-w-1][q[ql]]+q[ql]*d[i].ap-d[i].ap*j,f[i][j]);
            }
        }
        ql=1,qr=0;
        for(int j=m;j>=0;j--){
            while(ql<=qr&&q[ql]>j+d[i].bs) ql++;
            while(ql<=qr&&isnotokbp(i,j,q[qr])){
                qr--;
            }
            q[++qr]=j;
            if(ql<=qr){
                f[i][j]=max(f[i-w-1][q[ql]]+q[ql]*d[i].bp-d[i].bp*j,f[i][j]);
            }
        }
    }
    int ans=-2e9;
    for(int i=0;i<=m;i++){
        ans=max(ans,f[n][i]);
    }
    cout<<ans;
    return 0;
}