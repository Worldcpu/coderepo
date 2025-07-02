#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,m;

struct ACAuto{
    int t[MN][26],tot,end[MN],dep[MN],fail[MN],st[MN];

    void insert(string s,int id){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]=id;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t[0][i]){
                q.push(t[0][i]);
                dep[t[0][i]]=1;
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            st[u]=st[fail[u]];
            if(end[u]){
                st[u]|=1<<(dep[u]);
            }
            for(int i=0;i<26;i++){
                int v=t[u][i];
                if(v){
                    fail[v]=t[fail[u]][i];
                    dep[v]=dep[u]+1;
                    q.push(v);
                }else t[u][i]=t[fail[u]][i];
            }
        }
    }

    int query(string s){
        int p=0,mx=0;
        unsigned now=1;
        for(int i=0;i<s.length();i++){
            int k=s[i]-'a';
            p=t[p][k];
            now<<=1;
            if(st[p]&now) now|=1,mx=i+1;
        }
        return mx;
    }

}t;

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

int main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        string s;
        read(s);
        t.insert(s,i);
    }
    t.build();
    for(int i=1;i<=m;i++){
        string s;
        read(s);
        put(t.query(s));
    }
    return 0;
}
