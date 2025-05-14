#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6,MC=3e5,MK=1e5+15;
struct Node{
    int op,l,r,t,id;
}q[MN];
int n,m,tot,qtot,ptot,mptot,ans[MN],lst[MN],pre[MK],a[MK];
map<int,int> mp;

struct BIT{
    int t[MK];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

struct ODTNode{
    int l,r,val;
    bool operator<(const ODTNode &x)const{
        return l<x.l;
    }
};

struct ODT{
    set<ODTNode> s,col[MC];

    auto insert(int l,int r,int k){
        col[k].insert({l,r,k});
        return s.insert({l,r,k}).first;
    }

    void del(int l,int r,int k){
        col[k].erase({l,r,k});
        s.erase({l,r,k});
    }

    auto split(int x){
        auto it=s.lower_bound({x,0,0});
        if(it!=s.end()&&it->l==x) return it;
        it--;
        int l=it->l,r=it->r,k=it->val;
        del(l,r,k);
        insert(l,x-1,k);
        return insert(x,r,k);
    }

    int getpre(int x){
        auto it=s.upper_bound({x,0,0});
        it--;
        if(it->l<x) return x-1;
        else{
            auto co = col[it->val].lower_bound({ x, 0, 0 });
            if (co != col[it->val].begin()) return (--co)->r;
            return 0;
        }
    }

    void Assign(int l, int r, int v, int t) {
        auto itr = split(r + 1), itl = split(l);
        vector<int> ps;
        for (auto it = itl; it != itr; it++) {
            if (it != itl) ps.emplace_back(it->l);
            auto nxt = col[it->val].upper_bound(*it);
            if (nxt != col[it->val].end()) ps.emplace_back(nxt->l);
            col[it->val].erase(*it);
        }
        s.erase(itl, itr);
        insert(l, r, v);
        ps.emplace_back(l);
        auto nxt = col[v].upper_bound({ l, r, v });
        if (nxt != col[v].end()) ps.emplace_back(nxt->l);
        for (int i = 0; i < ps.size(); i++) {
            q[++qtot] = { -1,ps[i], pre[ps[i]], t, 0 };
            pre[ps[i]] = getpre(ps[i]);
            q[++qtot] = { 1,ps[i], pre[ps[i]], t, 0 };
        }
    }

}odt;

bool cmp1(Node x,Node y){
    if(x.t==y.t){
        return x.id<y.id;
    }
    return x.t<y.t;
}

bool cmp2(Node x,Node y){
    if(x.l==y.l)return x.id<y.id;
    return x.l<y.l;
}

void cdq(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    // sort(q+l+1,q+mid+1,cmp2);
    // sort(q+mid+1,q+r+1,cmp2);
    int i=l,j=mid+1;
    while(j<=r){
        while(q[i].l<=q[j].l&&i<=mid){
            if(!q[i].id) bit.update(q[i].r+1,q[i].op);
            // tmp[ttot++]=q[i++];
            i++;
        }
        if(q[j].id) ans[q[j].id]+=q[j].op*bit.query(q[j].r+1);
        // tmp[ttot++]=q[j++];
        j++;
    }
    for(int p=l;p<i;p++){
        if(!q[p].id) bit.update(q[p].r+1,-q[p].op);
    }
    // while(i<=mid) tmp[ttot++]=q[i++];
    // for(int p=l;p<=r;p++) q[p]=tmp[p];
    inplace_merge(q+l,q+mid+1,q+r+1,cmp2);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!mp[a[i]]) mp[a[i]]=++mptot;
        a[i]=mp[a[i]];
        pre[i]=lst[a[i]];
        lst[a[i]]=i;
        q[++qtot]={1,i,pre[i],0,0};
        odt.insert(i,i,a[i]);
    }
    for(int i=1;i<=m;i++){
        int op,l,r,d;
        cin>>op>>l>>r;
        if(op==1){
            cin>>d;
            if(!mp[d]) mp[d]=++mptot;
            d=mp[d];
            odt.Assign(l,r,d,i);
        }else{
            q[++qtot]={1,r,l-1,i,++tot};
            q[++qtot]={-1,l-1,l-1,i,tot};
        }
    }
    stable_sort(q+1,q+1+qtot,cmp1);
    cdq(1,qtot);
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}