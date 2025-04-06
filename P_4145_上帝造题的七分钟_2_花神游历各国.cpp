#include<iostream>
#include<cmath>
#define endl '\n'
#define il inline
#define ll long long
using namespace std;
const int MB=700,MN=1e5+15;
int n,len,l[MB],r[MB],pos[MN],tag[MB],m;
ll a[MN],sum[MB];
il void init(){
    len=sqrt(n);
    for(int i=1;i<=len;i++){
        l[i]=r[i-1]+1;
        r[i]=i*len;
    }
    if(r[len]<n){
        r[++len]=n;
        l[len]=r[len-1]+1;
    }
    for(int i=1;i<=len;i++){
        for(int j=l[i];j<=r[i];j++){
            pos[j]=i;
            sum[i]+=a[j];
        }
    }
}
il void kuaikai(int p){
    if(tag[p]) return;
    tag[p]=1;
    for(int i=l[p];i<=r[p];i++){
        sum[p]-=a[i];
        a[i]=sqrt(a[i]);
        sum[p]+=a[i];
        if(a[i]>1){
            tag[p]=0;
        }
    }
}
il void kai(int fl,int fr){
    int ql=pos[fl],qr=pos[fr];
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            sum[ql]-=a[i];
            a[i]=sqrt(a[i]);
            sum[ql]+=a[i];
        }
        return;
    }
    for(int i=fl;i<=r[ql];i++){
        sum[ql]-=a[i];
        a[i]=sqrt(a[i]);
        sum[ql]+=a[i];
    }
    for(int i=l[qr];i<=fr;i++){
        sum[qr]-=a[i];
        a[i]=sqrt(a[i]);
        sum[qr]+=a[i];
    }
    for(int i=ql+1;i<qr;i++){
        kuaikai(i);
    }
}
il ll ask(int fl,int fr){
    int ql=pos[fl],qr=pos[fr];
    ll ret=0;
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            ret+=a[i];
        }  
        return ret;
    }
    for(int i=fl;i<=r[ql];i++){
        ret+=a[i];
    }
    for(int i=l[qr];i<=fr;i++){
        ret+=a[i];
    }
    for(int i=ql+1;i<qr;i++){
        ret+=sum[i];
    }
    return ret;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    init();
    cin>>m;
    while (m--)
    {
        int op,l,r;
        cin>>op>>l>>r;
        if(l>r) swap(l,r);
        if(op==0){
            kai(l,r);
        }else cout<<ask(l,r)<<endl;
    }
    
    return 0;
}