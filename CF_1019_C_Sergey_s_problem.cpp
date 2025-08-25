#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int in[MN],dg[MN],n,m;
bool vis[MN],vis2[MN];
vector<int> adj[MN],ans;
queue<int> q;

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


void toposort(){
    for(int i=1;i<=n;i++){
        if(in[i]&&!dg[i]){
            q.push(i);
        }
    }   
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(!vis2[u]) ans.push_back(u);
        for(auto v:adj[u]){
            if(!in[v]) continue;
            dg[v]--;
            vis2[v]|=(vis2[u]^1);
            if(!dg[v]){
                q.push(v);
            }
        }
    }
}

int main(){
    read(n,m);
    for(int i=1;i<=m;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=in[i]=1;
            for(auto v:adj[i]){
                vis[v]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(in[i]){
            for(auto v:adj[i]){
                if(in[v]){
                    dg[v]++;
                }
            }
        }
    }
    toposort();
    put(ans.size());
    for(auto p:ans) put(p,0);
    return 0;
}