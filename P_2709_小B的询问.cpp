#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15;
struct kuai{
    int l,r,id;
}q[MN];
int n,m,len,K,a[MN],ans[MN],cnt[MN],ret;

bool cmp(kuai x,kuai y){
    if(x.l/len!=y.l/len){
        return x.l<y.l;
    }
    return x.r<y.r;
}

void add(int p){
    ret+=cnt[a[p]]*2+1;
    cnt[a[p]]++;
}

void del(int p){
    ret-=2*cnt[a[p]]-1;
    cnt[a[p]]--;
}

int main(){
    cin>>n>>m>>K;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l>q[i].l){
            l--;
            add(l);
        }
        while(r<q[i].r){
            r++;
            add(r);
        }
        while(l<q[i].l){
            del(l);
            l++;
        }
        while(r>q[i].r){
            del(r);
            r--;
        }
        ans[q[i].id]=ret;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}