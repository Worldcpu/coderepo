#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define ls t[p].lson
#define rs t[p].rson
using namespace std;
const int MN=1e6+15,INF=INT_MAX;
int n,m,tot,a[MN],rt[MN],now[MN],past[MN],ncnt,pcnt,LM;
vector<int> lsan;
struct segtree{
    int lson,rson,val;
}t[MN*100];
struct querynode{
    int op,x,y,z;
}q[MN];

void dolisan(){
    sort(lsan.begin(),lsan.end());
    LM=unique(lsan.begin(),lsan.end())-lsan.begin();
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(lsan.begin(),lsan.begin()+LM,a[i])-lsan.begin();
    }
    for(int i=1;i<=n;i++){
        if(q[i].op==2) q[i].y=lower_bound(lsan.begin(),lsan.begin()+LM,q[i].y)-lsan.begin();
    }

    //for(int i=1;i<=n;i++){
    //    cout<<a[i]<<" ";
    //}
    //cout<<'\n';
}

void change(int &p,int l,int r,int pos,int k){
    if(!p) p=++tot;
    t[p].val+=k;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(mid>=pos) change(ls,l,mid,pos,k);
    else change(rs,mid+1,r,pos,k);
}

int kth(int l,int r,int k){
    if(l==r) return l;
    int sum=0;
    for(int i=1;i<=ncnt;i++){
        sum+=t[t[now[i]].lson].val;
    }
    for(int i=1;i<=pcnt;i++){
        sum-=t[t[past[i]].lson].val;
    }
    int mid=(l+r)>>1;
    if(sum>=k){
        for(int i=1;i<=ncnt;i++){
            now[i]=t[now[i]].lson;
        }
        for(int i=1;i<=pcnt;i++){
            past[i]=t[past[i]].lson;
        }
        return kth(l,mid,k);
    }else{
        for(int i=1;i<=ncnt;i++){
            now[i]=t[now[i]].rson;
        }
        for(int i=1;i<=pcnt;i++){
            past[i]=t[past[i]].rson;
        }
        return kth(mid+1,r,k-sum);
    }
}

void build(){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=lowbit(j)){
            change(rt[j],1,LM-1,a[i],1);
        }
    }
}

int main(){
    lsan.push_back(-INF);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        lsan.push_back(a[i]);
    }
    for(int i=1;i<=m;i++){
        char op;
        cin>>op;
        if(op=='Q'){
            q[i].op=1;
            cin>>q[i].x>>q[i].y>>q[i].z;
        }else{
            q[i].op=2;
            cin>>q[i].x>>q[i].y;
            lsan.push_back(q[i].y);
        }
    }
    dolisan();
    build();

    for(int i=1;i<=m;i++){
        if(q[i].op==1){
            pcnt=ncnt=0;
            for(int j=q[i].x-1;j>0;j-=lowbit(j)){
                past[++pcnt]=rt[j];
            }
            for(int j=q[i].y;j>0;j-=lowbit(j)){
                now[++ncnt]=rt[j];
            }
            cout<<lsan[kth(1,LM-1,q[i].z)]<<'\n';
        }else{
            for(int j=q[i].x;j<=n;j+=lowbit(j)){
                change(rt[j],1,LM-1,a[q[i].x],-1);
            }
            for(int j=q[i].x;j<=n;j+=lowbit(j)){
                change(rt[j],1,LM-1,q[i].y,1);
            }
            a[q[i].x]=q[i].y;
        }
    }
    return 0;
}