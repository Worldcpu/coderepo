#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=7e5+15,MK=10000;
struct Query{
    int op,pos,x;
};
int n,q,ans[MN];
vector<Query> qry[MN];

struct FK{
    int len,L[MN],R[MN],pos[MN],a[MN],tag[MN];
    vector<int> vk[MN];

    void init(){
        len=sqrt(q);
        for(int i=1;i<=len;i++){
            L[i]=R[i-1]+1;
            R[i]=i*len;
        }
        if(R[len]<q){
            R[len]=q;
            L[len]=R[len-1]+1;
        }
        for(int i=1;i<=len;i++){
            for(int j=L[i];j<=R[i];j++){
                pos[j]=i;
                vk[i].push_back(a[j]);
            }
        }
    }

    void update(int p,int k){
        int qp=pos[p];
        vk[qp].clear();
        for(int i=p;i<=R[qp];i++){
            a[i]+=k;
        }
        for(int i=L[qp];i<=R[qp];i++) vk[qp].push_back(a[i]);
        sort(vk[qp].begin(),vk[qp].end());
        for(int i=qp+1;i<=len;i++) tag[i]+=k;
    }

    int query(int p,int x){
        int ret=0,qp=pos[p];
        for(int i=L[qp];i<=p;i++){
            if(a[i]+tag[qp]>=x) ret++;
        }
        for(int i=1;i<qp;i++){
            ret+=R[i]-(lower_bound(vk[i].begin(),vk[i].end(),x-tag[i])-vk[i].begin());
        }
        return ret;
    }

}fk;

signed main(){
    memset(ans,-1,sizeof(ans));
    cin>>n>>q;
    q++;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        qry[i].push_back({1,1,x});
        qry[i+1].push_back({1,1,-x});
    }
    for(int i=2;i<=q;i++){
        int op,x,y,z;
        cin>>op>>x>>y;
        if(op==1){
            cin>>z;
            qry[x].push_back({1,i,z});
            qry[y+1].push_back({1,i,-z});
        }else{
            qry[x].push_back({2,i,y});
        }
    }
    fk.init();
    for(int i=1;i<=n;i++){
        for(auto p:qry[i]){
            if(p.op==1){
                fk.update(p.pos,p.x);  
            }else{
                ans[p.pos]=fk.query(p.pos-1,p.x);
            }
        }
    }
    for(int i=2;i<=q;i++) if(~ans[i]) cout<<ans[i]<<'\n';
    return 0;
}
