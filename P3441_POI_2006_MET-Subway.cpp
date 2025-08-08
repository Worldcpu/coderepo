#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+2;
int n,L,rt,ftot,ans;
pir lvf[MN];
bool vis[MN];
int hd[MN],nxt[MN<<1],to[MN<<1],tot;
void add(int u,int v){to[++tot]=v,nxt[tot]=hd[u],hd[u]=tot;}

namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<18;
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

namespace ZJTree{
    struct Node{int u,fa,len;};
    int bfs(int st){
        queue<Node> q;
        int ans1=-1e9,ans2=1;
        q.push({st,0,0});
        while(!q.empty()){
            auto [u,fa,w]=q.front();q.pop();
            if(w>ans1) ans1=w,ans2=u;
            for(int i=hd[u];i;i=nxt[i]){
                int v=to[i];
                if(v==fa) continue;
                q.push({v,u,w+1});
            }
        }
        return ans2;
    }
}

namespace Tree{
    int dep[MN],fa[MN],mxdep[MN],htop[MN],len[MN],hson[MN];
    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=mxdep[u]=dep[pre]+1;
        for(int i=hd[u];i;i=nxt[i]){
            int v=to[i];
            if(v==pre) continue;
            dfs1(v,u);
            if(mxdep[u]<mxdep[v]) mxdep[u]=mxdep[v],hson[u]=v;
        }
        len[u]=mxdep[u]-dep[u]+1;
    }
    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]){lvf[++ftot]=pir(len[htop[u]],u);return;}
        dfs2(hson[u],ltop);
        for(int i=hd[u];i;i=nxt[i]){
            int v=to[i];
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }
}using namespace Tree;

bool cmp(pir x,pir y){return x.first>y.first;}

int main(){
    read(n,L);
    for(int i=1,u,v;i<n;i++) read(u,v),add(u,v),add(v,u);
    rt=ZJTree::bfs(1);
    dfs1(rt,0);
    dfs2(rt,rt);
    sort(lvf+1,lvf+1+ftot,cmp);
    for(int i=1;i<=(L<<1)-1;i++){
        if(i==1) vis[rt]=1,ans+=len[rt];
        else{
            int p=lvf[i].second;
            while(!vis[htop[p]]) vis[htop[p]]=1,ans+=len[htop[p]],p=fa[htop[p]];
        }
    }
    put(ans);
    return 0;
}
