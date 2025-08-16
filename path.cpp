#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15;
struct Edge{
    int v,w;

    friend bool operator<(const Edge &x,const Edge &y){
        return x.w<y.w;
    }
};
struct Node{
    int len,u,id;

    friend bool operator>(const Node &x,const Node &y){
        return x.len>y.len;
    }

};
int n,m,q,mxk,qry[MN],ans[MN];
vector<Edge> adj[MN];

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

void init(){
    mxk=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        qry[i]=ans[i]=0;
    }
}

void solve(){
    read(n,m,q);
priority_queue<Node,vector<Node>,greater<Node>> pq;
    init();
    for(int i=1;i<=m;i++){
        int u,v,w;
        read(u,v,w);
        adj[u].push_back({v,w});
    }
    for(int i=1;i<=n;i++) sort(adj[i].begin(),adj[i].end());
    for(int i=1;i<=q;i++){
        read(qry[i]);
        mxk=max(mxk,qry[i]);
    }
    for(int i=1;i<=n;i++){
        if(adj[i].size()){
            pq.push({adj[i][0].w,i,0});
        }
    }
    int cnt=0;
    while(!pq.empty()){
        auto tp=pq.top();
        pq.pop();
        ans[++cnt]=tp.len;
        if(cnt==mxk) break;
        if(tp.id<(adj[tp.u].size()-1)) pq.push({tp.len-adj[tp.u][tp.id].w+adj[tp.u][tp.id+1].w,tp.u,tp.id+1});
        int v=adj[tp.u][tp.id].v;
        if(adj[v].size()){
            pq.push({tp.len+adj[v][0].w,v,0});
        }
    }
    for(int i=1;i<=q;i++){
        put(ans[qry[i]]);
    }
}

int main(){
    int T;
    read(T);
    while(T--){
        solve();

    }


    return 0;
}