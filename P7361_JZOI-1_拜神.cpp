#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e4+15;
int n,q,pre[MN];
vector<int> vht[MN];
set<int> st[MN];
string s;

struct Segment{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson,val;
    }t[MN<<9];
    int tot,rt[MN];
    
    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void modfiy(int &p,int lst,int l,int r,int pos,int v){
        p=++tot;
        t[p]=t[lst];
        if(l==r){
            t[p].val=max(t[p].val,v);
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) modfiy(ls,t[lst].lson,l,mid,pos,v);
        else modfiy(rs,t[lst].rson,mid+1,r,pos,v);
        pushup(p);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr){
            return t[p].val;
        }
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret=max(ret,query(ls,l,mid,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,mid+1,r,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    // 接受 string 和 vector_int 输入，其他输入不保证正确性
    // ST表需要手动初始化调用initst函数
    template<typename vct>
    void getsa(vct &s){
        int m=400000;
        len=s.size();
        s.insert(s.begin(),' ');
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            ++c[x[i]];
        }
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=len;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=len;k<<=1){
            int num=0;
            for(int i=len-k+1;i<=len;i++) y[++num]=i;
            for(int i=1;i<=len;i++){
                if(sa[i]>k) y[++num]=sa[i]-k;
            }
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=len;i++) c[x[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=len;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            swap(x,y);
            num=1,x[sa[1]]=1;
            for(int i=2;i<=len;i++){
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
                else x[sa[i]]=++num;
            }
            if(num==len) break;
            m=num;
        }
        for(int i=1;i<=len;i++) rk[sa[i]]=i;
        for(int i=1,k=0;i<=len;i++){
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=ST[0][rk[i]]=k;
        }
    }
}using namespace SA;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void merge(int x,int y,int L){
    int rx=root(x),ry=root(y);
    if(rx==ry) return;
    if(st[rx].size()<st[ry].size()) swap(rx,ry);
    pre[ry]=rx;
    for(auto p:st[ry]){
        auto it=st[rx].lower_bound(p);
        if(it!=st[rx].end()){
            sg.modfiy(sg.rt[L],sg.rt[L],1,n,*it,p);
        }
        if(it!=st[rx].begin()){
            it--;
            sg.modfiy(sg.rt[L],sg.rt[L],1,n,p,*it);
        }
    }
    for(auto p:st[ry]) st[rx].insert(p);
}

int main(){
    cin>>n>>q>>s;
    getsa(s);
    for(int i=2;i<=n;i++){
        vht[ht[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        pre[i]=i;
        st[i].insert(i);
    }
    for(int i=n;i>=1;i--){
        sg.rt[i]=sg.rt[i+1];
        for(auto p:vht[i]){
            merge(sa[p],sa[p-1],i);
        }
    }
    while(q--){
        int L,R;
        cin>>L>>R;
        int l=0,r=R-L+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(sg.query(sg.rt[mid],1,n,L,R-mid+1)>=L){
                l=mid;
            }else r=mid;
        }
        cout<<l<<'\n';
    }
    return 0;
}
