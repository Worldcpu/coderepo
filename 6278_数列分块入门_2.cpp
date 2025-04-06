#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
const int MN=5e4+15,MQ=700;
int n;
vector<int> bl[MQ];
int l[MQ],r[MQ],pos[MN],tag[MQ],a[MN],len;
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
            bl[i].push_back(a[j]);
        }
        sort(bl[i].begin(),bl[i].end());
    }
}
void bladd(int fl,int fr,int k){
    int ql=pos[fl];
    for(int i=fl;i<=fr;i++){
        a[i]+=k;
    }
    bl[ql].clear();
    for(int i=l[ql];i<=r[ql];i++){
        bl[ql].push_back(a[i]);
    }
    sort(bl[ql].begin(),bl[ql].end());
}
void add(int fl,int fr,int k){
    int ql=pos[fl],qr=pos[fr];
    if(ql==qr){
        bladd(fl,fr,k);
        return;
    }
    bladd(fl,r[ql],k);
    bladd(l[qr],fr,k);
    for(int i=ql+1;i<qr;i++){
        tag[i]+=k;
    }
}
int query(int fl,int fr,int k){
    int ql=pos[fl],qr=pos[fr],ret=0;
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            if(a[i]+tag[ql]<k){
                ret++;
            }
        }
        return ret;
    }
    for(int i=fl;i<=r[ql];i++){
        if(a[i]+tag[ql]<k){
            ret++;
        }
    }
    for(int i=l[qr];i<=fr;i++){
        if(a[i]+tag[qr]<k){
            ret++;
        }
    }
    for(int i=ql+1;i<qr;i++){
        ret+=lower_bound(bl[i].begin(),bl[i].end(),k-tag[i])-bl[i].begin();
    }
    return ret;
}
int main(){
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
        }else cout<<query(l,r,k*k)<<endl;
    }
    
    return 0;
}