#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n,m,a[MN],cf[MN],pre[MN];
unordered_map<int,set<int>> mp;

struct Segment1{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,pre,mx,mn;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
        t[p].mn=min(t[ls].mn,t[rs].mn);
        t[p].pre=max(t[ls].pre,t[rs].pre);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mx=t[p].mn=a[l];
            t[p].pre=pre[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].mn=t[p].mx=k;
            t[p].pre=pre[t[p].l];
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int querymx(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mx;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=-1e9;
        if(mid>=fl) ret=max(ret,querymx(ls,fl,fr));
        if(mid<fr) ret=max(ret,querymx(rs,fl,fr));
        return ret;
    }

    int querymn(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mn;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=1e9;
        if(mid>=fl) ret=min(ret,querymn(ls,fl,fr));
        if(mid<fr) ret=min(ret,querymn(rs,fl,fr));
        return ret;
    }

    int querypre(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].pre;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=-1e9;
        if(mid>=fl) ret=max(ret,querypre(ls,fl,fr));
        if(mid<fr) ret=max(ret,querypre(rs,fl,fr));
        return ret;
    }
#undef ls
#undef rs
}t1;

struct SegmentGCD{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,gcdd;
    }t[MN<<2];

    void pushup(int p){
        t[p].gcdd=__gcd(t[ls].gcdd,t[rs].gcdd);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].gcdd=cf[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos){
        if(t[p].l==t[p].r){
            t[p].gcdd=cf[t[p].l];
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos);
        else modify(rs,pos);
        pushup(p);
    }

    int querygcd(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].gcdd;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fl) ret=__gcd(ret,querygcd(ls,fl,fr));
        if(mid<fr) ret=__gcd(ret,querygcd(rs,fl,fr));
        return ret;
    }
#undef ls
#undef rs
}t2;

bool solve(int x,int y,int k){
    if(x==y) return 1;
    int mx=t1.querymx(1,x,y),mn=t1.querymn(1,x,y),gcdd=t2.querygcd(1,x,y-1),mxpre=t1.querypre(1,x,y);
    if(mx-mn!=1ll*(y-x)*k) return 0;
    if(k&&mxpre>=x) return 0;
    if(gcdd!=k) return 0;
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++) cf[i]=abs(a[i+1]-a[i]);
    for(int i=1;i<=n;i++){
        if(!mp.count(a[i])) pre[i]=-1;
        else{
            auto it=mp[a[i]].end();
            --it;
            pre[i]=*it;
        }
        mp[a[i]].insert(i);
    }
    t1.build(1,1,n);
    t2.build(1,1,n-1);
    int cntyes=0;
    while(m--){
        int op,x,y,k;
        cin>>op>>x>>y;
        x^=cntyes,y^=cntyes;
        if(op==1){
            auto it=mp[a[x]].find(x);
            if(it!=mp[a[x]].end()){
                it++;
                if(it!=mp[a[x]].end()){
                    pre[*it]=pre[x];
                    t1.modify(1,*it,a[*it]);
                }
                it--;
            }
            mp[a[x]].erase(x);
            a[x]=y;
            mp[a[x]].insert(x);
            it=mp[a[x]].find(x);
            if(it!=mp[a[x]].begin()){
                it--;
                pre[x]=*it;
                it++;
            }else{
                pre[x]=-1;
            }
            it++;
            if(it!=mp[a[x]].end()){
                pre[*it]=x;
                t1.modify(1,*it,a[*it]);
            }
            if(x>1) cf[x-1]=abs(a[x]-a[x-1]);
            if(x<n) cf[x]=abs(a[x+1]-a[x]);
            t1.modify(1,x,y);
            if(x>1) t2.modify(1,x-1);
            if(x<n) t2.modify(1,x);
        }else{
            cin>>k;
            k^=cntyes;
            if(solve(x,y,k)){
                cout<<"Yes\n";
                cntyes++;
            }else cout<<"No\n";
        }
    }
    return 0;
}
