#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,p[MN],pos[MN];
set<pir> st;


namespace DSU{
    int pre[MN],siz[MN],mnid[MN];

    void initpre(){
        iota(pre+1,pre+1+n,1);
        fill(siz+1,siz+1+n,1);
        iota(mnid+1,mnid+1+n,1);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    // merge x->y
    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        st.erase(pir(mnid[rx],rx));
        st.erase(pir(mnid[ry],ry));
        pre[rx]=ry;
        mnid[ry]=min(mnid[ry],mnid[rx]);
        siz[ry]+=siz[rx];
        st.insert(pir(mnid[ry],ry));
    }
}using namespace DSU;

void init(){
    initpre();
    st.clear();
    for(int i=1;i<=n;i++) pos[i]=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>p[i];
        pos[p[i]]=i;
        st.insert(pir(i,i));
    } 
    for(int i=1;i<=n;i++){
        merge(i,p[i]);
    }
    for(int i=1;i<=n;i++){
        if(st.size()==1) break;
        auto it=st.begin();
        while(root(i)==root(it->second)) it++;
        auto now=*it;
        if(now.first<p[i]||siz[root(i)]==1){
            int j=pos[now.first];
            swap(p[i],p[j]);
            swap(pos[p[i]],pos[p[j]]);
            merge(i,j);
        }
        siz[root(i)]--;
    }
    for(int i=1;i<=n;i++){
        cout<<p[i]<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}