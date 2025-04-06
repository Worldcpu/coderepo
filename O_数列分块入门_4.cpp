#include<iostream>
#include<cmath>
#define int long long
using namespace std;
const int MN=1e5+15,MQ=700;
int l[MQ],r[MQ],pos[MN],tag[MQ],a[MN],n,len;
void init(){
    len=sqrt(n);//块长设置为根号n
    for(int i=1;i<=len;i++){
        l[i]=r[i-1]+1;//左端点是上一个块右端点+1
        r[i]=i*len;//直接乘长度
    }
    if(r[len]<n){//如果不够n就在建一个块，有的就是直接把最后一个块右端点改到n，其实都一样
        r[++len]=n;
        l[len]=r[len-1]+1;
    }
    for(int i=1;i<=len;i++){
        for(int j=l[i];j<=r[i];j++){
            pos[j]=i;//处理一下每个点所对应的块id
        }
    }
}
void add(int fl,int fr,int k){
    int ql=pos[fl],qr=pos[fr];
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            a[i]+=k;
            sum[ql]+=k;
        }
        return;
    }
    for(int i=fl;i<=r[ql];i++){
        a[i]+=k;
        sum[ql]+=k;
    }
    for(int i=l[qr];i<=fr;i++){
        a[i]+=k;
        sum[qr]+=k;
    }
    for(int i=ql+1;i<qr;i++){
        tag[i]+=k;
        sum[i]+=(r[i]-l[i]+1)*k;
    }
}
int query(int fl,int fr,int k){
    int ql=pos[fl],qr=pos[fr],ans=0;
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            ans=(ans+a[i]+tag[ql])%k;
        }
        return ans;
    }
    for(int i=fl;i<=r[ql];i++){
        ans=(ans+a[i]+tag[ql])%k;
    }
    for(int i=l[qr];i<=fr;i++){
        ans=(ans+a[i]+tag[qr])%k;
    }
    for(int i=ql+1;i<qr;i++){
        ans=(ans+sum[i])%k;
    }
    return ans;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    init();
    while (n--)
    { 
        int op,l,r,k;
        cin>>op>>l>>r>>k;
        if(op==0){
            add(l,r,k);
        }else cout<<query(l,r,k+1)<<endl;
    }
    
    return 0;
}