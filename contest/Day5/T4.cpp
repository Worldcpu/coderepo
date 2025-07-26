#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN];

namespace Sub1{
    int tmp[MN],tot;

    void solve(){
        while(m--){
            int op,l,r,x,y,k;
            cin>>op>>l>>r;
            if(op==1){
                cin>>x>>y;
                for(int i=l;i<=r;i++){
                    if(a[i]==x) a[i]=y;
                }
            }else{
                cin>>k;
                tot=0;
                for(int i=l;i<=r;i++){
                    tmp[++tot]=a[i];
                }
                sort(tmp+1,tmp+1+tot);
                tot=unique(tmp+1,tmp+1+tot)-tmp-1;
                int ret=tmp[1]-1;
                if(ret>=k&&ret>=1) cout<<k<<'\n';
                else{
                    k-=ret;
                    for(int i=2;i<=tot;i++){
                        ret=tmp[i]-tmp[i-1]-1;
                        if(ret>=k){
                            cout<<tmp[i-1]+k<<'\n';
                            k=0;
                            break;
                        }else k-=ret;
                    }
                    if(k) cout<<tmp[tot]+k<<'\n';
                }
            }
        }

    }

}

namespace SubB{
    struct Query{
        int l,r,k,id;
    }q[MN];
    int cnt[MN],ans[MN],qtot,bl;
    bool vis[MN];
    set<int> s;

    bool cmp(Query x,Query y){
        if(x.l/bl==y.l/bl) return x.r<y.r;
        return x.l/bl<y.l/bl;
    }

    void add(int x){
        cnt[a[x]]++;
        if(cnt[a[x]]==1) s.erase(s.find(a[x]));
    }

    void del(int x){
        cnt[a[x]]--;
        if(!cnt[a[x]]) s.insert(a[x]);
    }

    void solve(){
        bl=sqrt(n);
        int ql=1,qr=0;
        for(int i=1;i<=m;i++){
            int op,l,r,k;
            cin>>op>>l>>r>>k;
            q[++qtot]={l,r,k,i};
        }
        sort(q+1,q+1+qtot,cmp);
        for(int i=1;i<=n;i++){
            s.insert(i);
        }
        for(int i=1;i<=m;i++){
            while(qr<q[i].r) add(++qr);
            while(ql>q[i].l) add(--ql);
            while(qr>q[i].r) del(qr--);
            while(ql<q[i].l) del(ql++);
            int cnt=0;
            if(q[i].k>s.size()){
                q[i].k-=s.size();
                ans[q[i].id]=*(--s.end())+q[i].k;
                continue;
            }
            for(auto c:s){
                cnt++;
                if(cnt==q[i].k){
                    ans[q[i].id]=c;
                    break;
                }
            }
            
        }
        for(int i=1;i<=m;i++){
            cout<<ans[i]<<'\n';
        }
    }

}

signed main(){
    freopen("kthmex.in","r",stdin);
    freopen("kthmex.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    if(m==0) return 0;
    if(n<=1e3&&m<=1e3){
        Sub1::solve();
    }
    else SubB::solve();

    return 0;
}