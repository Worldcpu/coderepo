#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,MV=2000000000LL;
int n,a,b,rt[2][MN],X[MN],Y[MN],dtot,dis,ans;
bool vis[MN];
set<pir> st[2][MN];
map<int,int> mp[2];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson

    struct Node{
        int lson,rson,sum;
    }t[MN*20];
    int tot;

    void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        t[p].sum++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p||fl>fr) return 0;
        if(l>=fl && r<=fr) return t[p].sum;
        int mid=(l+r)>>1,ret=0;
        if(fl<=mid) ret+=query(ls,l,mid,fl,fr);
        if(fr>mid) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }
}sg;

void bfs(){
    queue<int> q;
    q.push(a);
    q.push(b);
    while(!q.empty()){
        int u=q.front(); q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(mp[0].count(X[u]+dis)){
            int now=mp[0][X[u]+dis];
            ans += sg.query(rt[0][now], -MV, MV, max(-MV, Y[u]-dis), min(MV, Y[u]+dis));
            auto &s = st[0][now];
            for(auto it = s.lower_bound(pir(Y[u]-dis,0)); it!=s.end() && llabs(it->first - Y[u]) <= dis; it = s.erase(it)){
                q.push(it->second);
            }
        }
        if(mp[0].count(X[u]-dis)){
            int now=mp[0][X[u]-dis];
            ans += sg.query(rt[0][now], -MV, MV, max(-MV, Y[u]-dis), min(MV, Y[u]+dis));
            auto &s = st[0][now];
            for(auto it = s.lower_bound(pir(Y[u]-dis,0)); it!=s.end() && llabs(it->first - Y[u]) <= dis; it = s.erase(it)){
                q.push(it->second);
            }
        }
        if(mp[1].count(Y[u]+dis)){
            int now=mp[1][Y[u]+dis];
            ans += sg.query(rt[1][now], -MV, MV, max(-MV, X[u]-dis+1), min(MV, X[u]+dis-1));
            auto &s = st[1][now];
            for(auto it = s.lower_bound(pir(X[u]-dis,0)); it!=s.end() && llabs(it->first - X[u]) <= dis; it = s.erase(it)){
                q.push(it->second);
            }
        }
        if(mp[1].count(Y[u]-dis)){
            int now=mp[1][Y[u]-dis];
            ans += sg.query(rt[1][now], -MV, MV, max(-MV, X[u]-dis+1), min(MV, X[u]+dis-1));
            auto &s = st[1][now];
            for(auto it = s.lower_bound(pir(X[u]-dis,0)); it!=s.end() && llabs(it->first - X[u]) <= dis; it = s.erase(it)){
                q.push(it->second);
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        X[i]=x+y; Y[i]=x-y;
        if(!mp[0].count(X[i])){
            mp[0][X[i]] = ++dtot;
        }
        sg.modify(rt[0][ mp[0][X[i]] ], -MV, MV, Y[i]);
        st[0][ mp[0][X[i]] ].insert(pir(Y[i], i));

        if(!mp[1].count(Y[i])){
            mp[1][Y[i]] = ++dtot;
        }
        sg.modify(rt[1][ mp[1][Y[i]] ], -MV, MV, X[i]);
        st[1][ mp[1][Y[i]] ].insert(pir(X[i], i));
    }
    dis = max( llabs(X[a]-X[b]), llabs(Y[a]-Y[b]) );
    bfs();
    cout << (ans>>1) << '\n';
    return 0;
}
