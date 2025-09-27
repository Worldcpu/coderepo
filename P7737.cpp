#include <bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15,MV=100;
struct AEdge{
    int u,v,w;
};
struct Edge{
    int v,w,id;
};
int n,m,S,T,q,K,vdcc,in1[MN],in2[MN],sum[MN],col[MN],colw[MN];
vector<int> adj[MN],g1[MN],g2[MN];
vector<Edge> g3[MN],g4[MN];

namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            template<typename type>inline void write(type *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch;read(ch),x.clear();do x+=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
            template<typename type>
            inline void put(const type &x,bool flag=1){write(x),flag?putchar('\n'):putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;

struct Hash{
    unordered_map<int,int> ump;
    int tot;

    void clear(){
        ump.clear();
        tot=0;
    }

    int getid(int x){
        if(!ump[x]) ump[x]=++tot;
        return ump[x];
    }  

}H;

struct Tarjan{ //adj->DAG(g1)
    int s[MN],top,dfn[MN],low[MN],tot;
    bool vis[MN];
    void tarjan(int u){
        low[u]=dfn[u]=++tot;
        s[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            int p;
            vdcc++;
            //cerr<<"NEW VDCC:";
            do{
                p=s[top--];
                //cerr<<p<<" ";
                col[p]=vdcc;
                colw[vdcc]++;
                vis[p]=0;
            }while(p!=u);
            //cerr<<"\nCOLW:"<<colw[vdcc];
            //cerr<<'\n';
        }
    }

    void getg2(){
        //cerr<<"BEGIN OF G1\n";
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i);
        }
        for(int i=1;i<=n;i++){
            for(auto v:adj[i]){
                if(col[i]!=col[v]){
                    g1[col[i]].push_back(col[v]);
                    in1[col[v]]++;
                    //cerr<<col[i]<<" "<<col[v]<<'\n';
                }
            }
        }
        //cerr<<"END OF G1\n";
    }

}tj;

struct Tree{// Just For G2(Tree)
    int dfn[MN],siz[MN],dep[MN],fa[MN],htop[MN],hson[MN],rt,tot;
    
    void getrt(){
        for(int i=1;i<=vdcc;i++){
            if(!in2[i]) rt=i;
        }
    }

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        dfn[u]=++tot;
        sum[u]=sum[pre]+colw[u];
        siz[u]=1;
        for(auto v:g2[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:g2[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}t;

struct SOLVE{
    int h[MN],val[MV],s[MN],top,tot3,tot4;
    bool vis[MV],vis2[MV],vp[MV];

    void clear(){
        top=0;
        tot3=tot4=0;
        H.clear();
        for(int i=1;i<=vdcc;i++){
            g3[i].clear();
            g4[i].clear();
        }
    }

    void getvt(){
        sort(h+1,h+(K+1)*2+1,[&](int x,int y){
            return t.dfn[x]<t.dfn[y];
        });
        int tot=unique(h+1,h+(K+1)*2+1)-h-1;
        //cerr<<"H:";
        for(int i=1;i<=tot;i++){
            val[H.getid(h[i])]=colw[h[i]];
            //cerr<<h[i]<<" ";
        }
        //cerr<<'\n';
        s[++top]=h[1];
        for(int i=2;i<=tot;i++){
            int qlca=t.lca(h[i],s[top]);
            val[H.getid(qlca)]=colw[qlca];
            while(1){
                if(t.dep[qlca]>=t.dep[s[top-1]]){
                    if(qlca!=s[top]){
                        g3[H.getid(qlca)].push_back({H.getid(s[top]),sum[t.fa[s[top]]]-sum[qlca],++tot3});
                        g4[H.getid(s[top])].push_back({H.getid(qlca),sum[t.fa[s[top]]]-sum[qlca],++tot4});
                        if(qlca!=s[top-1]) s[top]=qlca;
                        else top--;
                    }
                    break;
                }else{
                    g3[H.getid(s[top-1])].push_back({H.getid(s[top]),sum[t.fa[s[top]]]-sum[s[top-1]],++tot3});
                    g4[H.getid(s[top])].push_back({H.getid(s[top-1]),sum[t.fa[s[top]]]-sum[s[top-1]],++tot4});
                    top--;
                }
            }
            s[++top]=h[i];
        }
        while(top-1){
            g3[H.getid(s[top-1])].push_back({H.getid(s[top]),sum[t.fa[s[top]]]-sum[s[top-1]],++tot3});
            g4[H.getid(s[top])].push_back({H.getid(s[top-1]),sum[t.fa[s[top]]]-sum[s[top-1]],++tot4});
            top--;
        }
    }

    int work(){
        memset(vis,0,sizeof(vis));
        memset(vp,0,sizeof(vp));
        memset(vis2,0,sizeof(vis2));
        queue<int> q;
        q.push(H.getid(S));
        //cerr<<"IDS:"<<H.getid(S)<<" IDT:"<<H.getid(T)<<'\n';
        //cerr<<"VALS:"<<val[H.getid(S)]<<" VALT:"<<val[H.getid(T)]<<'\n';
        while(!q.empty()){ // g3
            int u=q.front();
            q.pop();
            vp[u]=1;
            for(auto e:g3[u]){
                if(!vis[e.id]){
                    vis[e.id]=1;
                    q.push(e.v);
                }
            }
        }
        int ans=0;
        q.push(H.getid(T));
        while(!q.empty()){
            int u=q.front();
            q.pop();
            if(vp[u]){
                ans+=val[u];
                vp[u]=0;
            }
            for(auto e:g4[u]){
                if(!vis2[e.id]){
                    vis2[e.id]=1;
                    if(vis[e.id]){
                        ans+=e.w;
                        vis[e.id]=0;
                    }
                    q.push(e.v);
                }
            }
        }
        memset(val,0,sizeof(val));
        return ans;
    }

    void solve(){
        //cerr<<"BEGIN OF SOLVE\n";
        clear();
        read(S),read(T);
        S=col[S];
        T=col[T];
        h[1]=S;
        h[2]=T;
        for(int i=1;i<=K;i++){
            int u,v;
            read(u),read(v);
            u=col[u];
            v=col[v];
            g3[H.getid(u)].push_back({H.getid(v),0,++tot3});   
            g4[H.getid(v)].push_back({H.getid(u),0,++tot4});
            //cerr<<col[u]<<" "<<col[v]<<" "<<0<<'\n';
            h[i*2+1]=u;
            h[i*2+2]=v;
        }
        //cerr<<"BEGIN OF VT\n";
        getvt();
        //cerr<<"END OF VT,NEXT IF OUTPUT WORK\n";
        put(work());
        //cerr<<"END OF SOLVE\n";
    }
    
}sol;

void toposort(){ // g1->Tree(topo g2)
    //cerr<<"BEGIN OF G2,BELOW ARE SDCC's ID\n";
    queue<int> q;
    for(int i=1;i<=vdcc;i++){
        if(!in1[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:g1[u]){
            in1[v]--;
            if(!in1[v]){
                g2[u].push_back(v);
                in2[v]++;
                //cerr<<u<<" "<<v<<'\n';
                q.push(v);
            }
        }
    }
    ////cerr<<"END OF G2\n";
}


int main(){
    read(n);
    read(m);
    read(q);
    read(K);
    for(int i=1;i<=m;i++){
        int u,v;
        read(u),read(v);
        adj[u].push_back(v);
    }
    tj.getg2();
    toposort();
    t.getrt();
    t.dfs1(t.rt,0);
    t.dfs2(t.rt,t.rt);
    //cerr<<"TEST LCA:"<<t.lca(1,2)<<'\n';
    while(q--){
        sol.solve();
    }
    return 0;
}