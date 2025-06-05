#include<bits/stdc++.h>
using namespace std;
const int MN=6e6+15,MR=MN<<2;
const double pi=acos(-1);
using compd=complex<double>;
int n,m,k,nm;
int rev[MN];
compd a[MN],b[MN],c[MN],ans[MN];

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

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        double x;
        cin>>x;
        c[n-i]=a[i]=x;
        b[i]=(double)(1.0/i/i);
    }
    int len=1;
    while(len<=(n<<1)) len<<=1;
    fft(a,len,1);
    fft(b,len,1);
    fft(c,len,1);
    for(int i=0;i<len;i++){
        a[i]=a[i]*b[i];
        c[i]=c[i]*b[i];
    }
    fft(a,len,-1);
    fft(c,len,-1);
    for(int i=1;i<=n;i++){
        cout<<fixed<<setprecision(3)<<a[i].real()-c[n-i].real()<<'\n';
    }
    return 0;
}
