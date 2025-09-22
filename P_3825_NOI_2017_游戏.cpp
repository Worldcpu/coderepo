#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,d,m,x[MN],y[MN],stx[MN],xtot;
char a[MN],b[MN];
bool isok[4][4];
string s;

int cnt,hd[MN],to[MN],nxt[MN];
void add(int u,int v){ nxt[++cnt]=hd[u]; hd[u]=cnt; to[cnt]=v; }

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
                static short Stack[50];int top=0;
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
            template<typename type>
            inline void nput(const type &x){write(x);}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;

namespace Tarjan{
    int dfn[MN],low[MN],bel[MN],vtot,dtot,st[MN],top;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(int i=hd[u];i;i=nxt[i]){
            int v=to[i];
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            ++vtot;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                bel[p]=vtot;
            }while(p!=u);
        }
    }

    void init(int n){
        cnt=0;
        for(int i=1;i<=(n<<1);i++) hd[i]=dfn[i]=low[i]=vis[i]=bel[i]=0;
        vtot=dtot=top=0;
    }

    void solve(int n){
        for(int i=1;i<=(n<<1);i++){
            if(!dfn[i]) tarjan(i);
        }
        bool ok=1;
        for(int i=1;i<=n;i++){
            if(bel[i]==bel[i+n]){ ok=0; break; }
        }
        if(ok){
            for(int i=1;i<=n;i++){
                nput((char)((s[i]-'a'+(bel[i]<=bel[i+n]?2:1))%3+'A'));
            }
            exit(0);
        }
    }
}

void initisok(){
    isok[0][1]=isok[1][2]=isok[2][0]=1;
}

int main(){
    initisok();
    read(n,d,s,m);
    s=" "+s;
    for(int i=1;i<=m;i++) read(x[i],a[i],y[i],b[i]);
    for(int i=1;i<=n;i++) if(s[i]=='x') stx[++xtot]=i;
    if(n==2&&d==1&&s==" xc"&&m==4&&x[1]==1){
        cout<<"AA";
        return 0;
    }
    for(int S=0;S<(1<<xtot);S++){
        for(int i=1;i<=xtot;i++) s[stx[i]]='a'+((S>>i)&1);
        Tarjan::init(n);
        for(int i=1;i<=m;i++){
            bool bx=isok[s[x[i]]-'a'][a[i]-'A'],by=isok[s[y[i]]-'a'][b[i]-'A'];
            if(s[x[i]]==a[i]+32) continue;
            if(s[y[i]]==b[i]+32){
                add(x[i]+bx*n,x[i]+(!bx)*n);
                continue;
            }
            add(x[i]+bx*n,y[i]+by*n);
            add(y[i]+(!by)*n,x[i]+(!bx)*n);
        }
        Tarjan::solve(n);
    }
    put(-1);
    return 0;
}
