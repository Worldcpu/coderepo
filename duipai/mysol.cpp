
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5;
struct Node{
    int posx,posy,posac,st;
    
    friend bool operator <(const Node &x,const Node &y){
        if(x.posx==y.posx){
            if(x.posy==y.posy){
                if(x.posac==y.posac){
                    return x.st<y.st;
                }
                return x.posac<y.posac;
            }
            return x.posy<y.posy;
        }
        return x.posx<y.posx;
    }
};
int n,m,K;
string x,y;
map<Node,int> mp;


struct ACAuto{
    int nxt[MN][58],fail[MN],end[MN],tot;

    void insert(string s,int st){
        int p=0;
        for(auto c:s){
            int k=c-'A';
            if(!nxt[p][k]) nxt[p][k]=++tot;
            p=nxt[p][k];
        }
        end[p]|=st;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<58;i++){
            if(nxt[0][i]) q.push(nxt[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            end[u]|=end[fail[u]];
            for(int i=0;i<58;i++){
                int v=nxt[u][i];
                if(v){
                    fail[v]=nxt[fail[u]][i];
                    q.push(v);
                }else nxt[u][i]=nxt[fail[u]][i];
            }
        }
    }

}ac;

struct Seq{
    vector<int> nxt[MN];

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);\
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq[2];

int dfs(int px,int py,int pac,int st){
    if(mp.count({px,py,pac,st})) return mp[{px,py,pac,st}];
    int ret=-1e9;
    if(st==(1<<K)-1) ret=0;
    for(int i=0;i<58;i++){
        if(sq[0].gnxt(px,i)&&sq[1].gnxt(py,i)){
            ret=max(ret,dfs(sq[0].gnxt(px,i),sq[1].gnxt(py,i),ac.nxt[pac][i],st|=ac.end[ac.nxt[pac][i]])+1);
        }
    }
    return mp[{px,py,pac,st}]=ret;
}

signed main(){
    cin>>n>>m>>K;
    for(int i=1,qwq;i<=K;i++){
        cin>>qwq;
    }
    cin>>x>>y;
    x=" "+x,y=" "+y;
    for(int i=1;i<=n;i++){
        int k=x[i]-'A';
        sq[0].nxt[k].push_back(i);   
    }
    for(int i=1;i<=m;i++){
        int k=y[i]-'A';
        sq[1].nxt[k].push_back(i);   
    }
    for(int i=1;i<=K;i++){
        string qwq;
        cin>>qwq;
        ac.insert(qwq,1<<(i-1));
    }
    ac.build();
    cout<<dfs(0,0,0,0);

    return 0;
}