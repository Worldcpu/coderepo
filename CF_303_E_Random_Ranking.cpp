#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=166;
constexpr double eps=1e-10;
int n,v,L[MN],R[MN],lsan[MN],dtot,p[MN];
double p1[MN][MN],p2[MN][MN],p3[MN][MN],f[MN][MN][MN],s[MN][MN][MN],g[MN][MN];
double ans[MN][MN];

double getp(int i,int x){
    if(L[i]>x) return 0;
    if(R[i]<x) return 1;
    return 1.0*(x-L[i])/(R[i]-L[i]);
}

void add(int d,int x){
    for(int i=0;i<=p[d];i++){
        for(int j=0;i+j<=p[d];j++){
            if(f[d][i][j]<eps) continue;
            g[i+1][j]+=f[d][i][j]*p1[x][v];
            g[i][j+1]+=f[d][i][j]*p2[x][v];
            g[i][j]+=f[d][i][j]*p3[x][v];
        }
    }
    p[d]++;
    for(int i=0;i<=p[d];i++){
        for(int j=0;i+j<=p[d];j++){
            f[d][i][j]=g[i][j];
            g[i][j]=0;
        }
    }
}

void cdq(int d,int l,int r){
    if(l==r){
        for(int i=0;i<=p[d];i++){
            for(int j=0;i+j<=p[d];j++){
                s[l][i][j]+=f[d][i][j]*p2[l][v];
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    p[d+1]=p[d];
    for(int i=0;i<=p[d];i++){
        for(int j=0;i+j<=p[d];j++){
            f[d+1][i][j]=f[d][i][j];
        }
    }
    for(int i=l;i<=mid;i++){
        add(d+1,i);
    }
    cdq(d+1,mid+1,r);
    p[d+1]=p[d];
    for(int i=0;i<=p[d];i++){
        for(int j=0;i+j<=p[d];j++){
            f[d+1][i][j]=f[d][i][j];
        }
    }
    for(int i=mid+1;i<=r;i++){
        add(d+1,i);
    }
    cdq(d+1,l,mid);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        lsan[++dtot]=L[i];
        lsan[++dtot]=R[i];
    }
    sort(lsan+1,lsan+1+dtot);
    dtot=unique(lsan+1,lsan+1+dtot)-lsan-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=dtot;j++){
            double x=getp(i,lsan[j]),y=getp(i,lsan[j+1]);
            p1[i][j]=x;
            p2[i][j]=y-x;
            p3[i][j]=1-y;
        }
    }
    f[1][0][0]=1.0;
    p[1]=0;
    for(v=1;v<dtot;v++) cdq(1,1,n);
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;j+k<n;k++){
                for(int p=1;p<=k+1;p++){
                    ans[i][j+p]+=s[i][j][k]/(k+1);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<fixed<<setprecision(7)<<ans[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}