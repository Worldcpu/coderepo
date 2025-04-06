#include<bits/stdc++.h>
#define pir pair<long long,int>
#define ll long long
using namespace std;
const int MN=1e6+15;
int n,m,d,tot,awa,pre[MN];
ll a[MN],f[MN];

struct segtree{
    int ls,rs,pos;
    ll val;
}t[MN<<2];

void pushup(int p){
    // t[p].val=max(t[t[p].ls].val,t[t[p].rs].val);
    if(t[t[p].ls].val<t[t[p].rs].val){
        t[p].val=t[t[p].rs].val;
        t[p].pos=t[t[p].rs].pos;
    }else{
        t[p].val=t[t[p].ls].val;
        t[p].pos=t[t[p].ls].pos;
    }
}

void docov(int &p,ll l,ll r,ll pos,ll k,int xb){
    if(!p){
        p=++tot;
    }
    if(l==r){
        // t[p].val=max(t[p].val,k);
        if(t[p].val<k){
            t[p].val=k;
            t[p].pos=xb;
        }
        return;
    }
    ll mid=(l+r)>>1;
    if(mid>=pos){
        docov(t[p].ls,l,mid,pos,k,xb);
    }else docov(t[p].rs,mid+1,r,pos,k,xb);
    pushup(p);
}

pir query(int p,ll l,ll r,ll fl,ll fr){
    if(fr<=0) return pir(-1,0);
    if(!p) return pir(-1,0);
    if(l>=fl&&r<=fr){
        return pir(t[p].val,t[p].pos);
    }
    ll mid=l+r>>1;
    pir ret;
    if(mid>=fl) ret=max(ret,query(t[p].ls,l,mid,fl,fr));
    if(mid<fr) ret=max(ret,query(t[p].rs,mid+1,r,fl,fr));
    return ret;
}

vector<int> ans;

int main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    // cout<<'\n';
    awa=0;
    for(int i=1;i<=n;i++){
        pir res=max(query(1,1,1e16,1,a[i]-d),query(1,1,1e16,a[i]+d,1e16));
        f[i]=res.first+1;
        pre[i]=res.second;
        docov(awa,1,1e16,a[i],f[i],i);
    }
    ll mx=-1,wz;
    // cout<<awa<<" ";
    for(int i=1;i<=n;i++){
        if(mx<f[i]){
            mx=f[i];
            wz=i;
        }
    }
    cout<<mx<<'\n';
    for(int i=wz;i>=1;i=pre[i]){
        ans.push_back(i);
    }

    sort(ans.begin(),ans.end());
    for(auto v:ans) cout<<v<<" ";

    return 0;
}