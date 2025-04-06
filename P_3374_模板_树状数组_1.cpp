#include<iostream>
#include<cmath>
#define endl '\n'
#define ll long long
using namespace std;
const int MN=5e5+15;
int n,m;
int l[MN],r[MN],pos[MN];
ll a[MN],sum[MN],len;
void add(int x,ll k){
    a[x]+=k;
    sum[pos[x]]+=k;
}
void init(){
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
ll query(int fl,int fr){
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
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    init();
    while (m--)
    {
        int op;
        ll x,y;
        cin>>op>>x>>y;
        if(op==1){
            add(x,y);
        }else cout<<query(x,y)<<endl;
    }
    
    return 0;
}