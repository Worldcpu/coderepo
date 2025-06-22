#include<bits/stdc++.h>
#define lint __int128
using namespace std;
constexpr int MN=13500,MB=72;
int n,to[MN][10],mn[MN],tot;
lint f[25][MN][11],a[MN],top,K;
map<lint,int> mp;


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

int getst(lint now){
    if(mp[now]) return mp[now];
    int id=mp[now]=++tot;
    for(lint i=0;i<=MB;i++){
        if((now>>i)&1){
            mn[id]=i;
            break;
        }
    }
    for(int i=0;i<10;i++){
        lint nxt=0;
        for(lint j=0;j<=72;j++){
            if((now>>j)&1){
                if((now>>j)&1){
                    if(i+j<=MB) nxt|=((lint)1<<(i+j));
                    if(j>=i) nxt|=((lint)1<<(j-i));
                    else nxt|=((lint)1<<(i-j));
                }
            }
        }
        to[id][i]=getst(nxt);
    }
    return id;
}

lint dfs(int pos,bool lim,int sta){
    if((!lim)&&(f[pos][sta][K]!=-1)) return f[pos][sta][K];
    if(!pos) return f[0][sta][K]=(mn[sta]<=K);
    if(lim){
        lint ret=0;
        for(int i=0;i<a[pos];i++) ret+=dfs(pos-1,0,to[sta][i]);
        ret+=dfs(pos-1,1,to[sta][a[pos]]);
        return ret;
    }
    lint ret=0;
    for(int i=0;i<10;i++) ret+=dfs(pos-1,0,to[sta][i]);
    return f[pos][sta][K]=ret;
}

lint solve(lint x){
    top=0;
    while(x){
        a[++top]=x%10;
        x/=10;
    }
    return dfs(top,1,1);
}

int main(){
    memset(f,-1,sizeof(f));
    getst(1);
    cerr<<tot;
    int T;
    cin>>T;
    while(T--){
       long long l,r;
       read(l,r,K);
       put(solve(r)-solve(l-1));
    }
    return 0;
}
