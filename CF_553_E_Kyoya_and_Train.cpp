#include<bits/stdc++.h>
#define double long double
using namespace std;
using compd=complex<double>;
const int MN=8e4+15,MM=119,MR=MN<<2;
int n,m,t,x,u[MM],v[MM],w[MM],dis[MM][MM];
double f[MM][MN],g[MM][MN],p[MM][MN];
compd F[MN],G[MN],Ans[MN];

namespace PolyFFT{
    const double pi=acos(-1.0);
    constexpr int MXREV=1e7;
    using compd=complex<double>;
    int rev[MXREV];
    compd tf[MN],tg[MN];

    void dorev(compd f[],int len){
        for(int i=0;i<len;i++){
            rev[i]=rev[i>>1]>>1;
            if(i&1){
                rev[i]|=len>>1;
            }
        }
        for(int i=0;i<len;i++){
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        }
    }

    void fft(compd f[],int len,int mode){
        dorev(f,len);
        for(int i=2;i<=len;i<<=1){//处理的区间长度
            compd wn(cos(2*pi/i),sin(2*pi*mode/i));
            for(int j=0;j<len;j+=i){//步长为i
                compd w(1,0);
                for(int k=j;k<j+i/2;k++){// 蝶形优化
                    compd u=f[k];//左区间
                    compd t=w*f[k+i/2];//右区间
                    f[k]=u+t;
                    f[k+i/2]=u-t;
                    w=w*wn;
                }
            }
        }
        if(mode==-1){
            for(int i=0;i<len;i++){
                f[i]/=len;
            }
        }
    }
    
    void Mul(compd F[],compd G[],compd ans[],int len){
        for(int i=0;i<len;i++) tf[i]=(i<n?F[i]:0);
        for(int i=0;i<len;i++) tg[i]=(i<m?G[i]:0);
        fft(tf,len,1);
        fft(tg,len,1);
        for(int i=0;i<len;i++) tf[i]=tf[i]*tg[i];
        fft(tf,len,-1);
        for(int i=0;i<len;i++) ans[i]=tf[i];
    }

    void cdq(int l,int r){
        if(l==r){
            for(int i=1;i<n;i++) f[i][l]=1e9;
            for(int i=1;i<=m;i++){
                f[u[i]][l]=min(f[u[i]][l],g[i][l]);
            }
            return;
        }
        int mid=(l+r)>>1;
        int len=r-l,lenm=r-mid,lim=1;
        while(lim<=len+lenm) lim<<=1;
        cdq(mid+1,r);
        for(int i=1;i<=m;i++){
            for(int j=0;j<lim;j++) F[j]=G[j]=Ans[j]=compd(0,0);
            for(int j=0;j<len;j++){
                F[j]=compd(p[i][j+1],0);
            }
            for(int j=0;j<lenm;j++){
                G[j]=compd(f[v[i]][r-j],0);
            }
            Mul(F,G,Ans,lim);
            for(int j=l;j<=mid;j++) g[i][j]+=Ans[r-j-1].real();
        }
        cdq(l,mid);
    }

}

signed main(){
    memset(dis,0x3f,sizeof(dis));
    cin>>n>>m>>t>>x;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        dis[u[i]][v[i]]=w[i];
        for(int j=1;j<=t;j++){
            cin>>p[i][j];
            p[i][j]/=1e5;
        }
    }
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    for(int i=1;i<=m;i++){
        double sum=0;
        for(int j=0;j<=t;sum+=p[i][t-j],j++){
            g[i][j]=sum*(dis[v[i]][n]+x)+w[i];
        }
    }
    PolyFFT::cdq(0,t);
    cout<<fixed<<setprecision(8)<<min(f[1][0],(double)x+dis[1][n]);
    return 0;
}
