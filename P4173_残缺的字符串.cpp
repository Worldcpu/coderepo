#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MN=1e7+15,MR=MN<<2;
const double pi=acos(-1);
using compd=complex<double>;
int n,m,len,s[MN],tot;
int rev[MN],A[MN],B[MN];
compd a[MN],b[MN],ans[MN];
string s1,s2;

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

signed main(){
    cin>>m>>n>>s1>>s2;
    reverse(s1.begin(),s1.end());
    len=1;
    while(len<=n+m) len<<=1;
    for(int i=0;i<m;i++){
        A[i]=(s1[i]!='*')?(s1[i]-'a'+1):0;
    }
    for(int i=0;i<n;i++){
        B[i]=(s2[i]!='*')?(s2[i]-'a'+1):0;
    }
    for(int i=0;i<=len;i++){
        a[i]=compd(A[i]*A[i]*A[i],0);
        b[i]=compd(B[i],0);
    }
    fft(a,len,1);
    fft(b,len,1);
    for(int i=0;i<=len;i++) ans[i]=ans[i]+a[i]*b[i];
    for(int i=0;i<=len;i++){
        a[i]=compd(A[i],0);
        b[i]=compd(B[i]*B[i]*B[i],0);
    }
    fft(a,len,1);
    fft(b,len,1);
    for(int i=0;i<=len;i++) ans[i]=ans[i]+a[i]*b[i];
    for(int i=0;i<=len;i++){
        a[i]=compd(A[i]*A[i],0);
        b[i]=compd(B[i]*B[i],0);
    }
    fft(a,len,1);
    fft(b,len,1);
    for(int i=0;i<=len;i++) ans[i]=ans[i]+a[i]*b[i]*compd(-2,0);
    fft(ans,len,-1);
    for(int i=m-1;i<n;i++){
        if(fabs(ans[i].real())<=1e-7) s[++tot]=i-m+2;
    }
    cout<<tot<<'\n';
    for(int i=1;i<=tot;i++) cout<<s[i]<<" ";
    return 0;
}
