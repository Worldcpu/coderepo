#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
struct Query{
    int l,r,id;
}q[MN];
int n,m,tot,len,ed2[MN],ed[MN],ans[MN],R[MN],st[MN],bl[MN],a[MN],b[MN];

bool cmp(Query x,Query y){
    if(bl[x.l]==bl[y.l]) return x.r<y.r;
    return x.l<y.l;
}

int main(){
    cin>>n;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
        bl[i]=(i-1)/len+1;
    }
    for(int i=1;i<=bl[n];i++){
        R[i]=(i==bl[n])?n:len*i;
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    int block=0,tmp1=0,l=0,r=0,now=0;
    for(int i=1;i<=m;i++){
        if(bl[q[i].l]==bl[q[i].r]){
            tmp1=0;
            for(int j=q[i].l;j<=q[i].r;j++){
                st[a[j]]=0;
            }
            for(int j=q[i].l;j<=q[i].r;j++){
                if(!st[a[j]]) st[a[j]]=j;
                tmp1=max(tmp1,j-st[a[j]]);
            }
            for(int j=q[i].l;j<=q[i].r;j++){
                st[a[j]]=0;
            }
            ans[q[i].id]=tmp1;
            continue;
        }
        now=bl[q[i].l];
        if(block!=now){
            tmp1=0;
            for(int j=l;j<=r;j++) st[a[j]]=ed[a[j]]=0;
            l=R[now];
            r=l-1;
            block=now;
        }
        while(r<q[i].r){
            r++;
            if(!st[a[r]]) st[a[r]]=r;
            ed[a[r]]=r;
            tmp1=max(tmp1,r-st[a[r]]);
        }
        int p=l,tmp2=0;
        while(q[i].l<p){
            p--;
            if(!ed2[a[p]]) ed2[a[p]]=p;
            tmp2=max(tmp2,max(ed[a[p]],ed2[a[p]])-p);
        }
        while(p<l){
            ed2[a[p]]=0;
            p++;
        }
        ans[q[i].id]=max(tmp1,tmp2);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}