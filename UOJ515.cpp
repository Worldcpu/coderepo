#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,q,a[MN],ans[MN];
vector<int> qry[MN];
vector<pir> chg[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx,cmx,cnt;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
        if(t[ls].mx==t[rs].mx){
            t[p].cmx=max(t[ls].cmx,t[rs].cmx);
        }
        else if(t[p].mx==t[ls].mx){
            t[p].cmx=max(t[ls].cmx,t[rs].mx);
        }
        else if(t[p].mx==t[rs].mx){
            t[p].cmx=max(t[ls].mx,t[rs].cmx);
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mx=1e9;
            t[p].cmx=-1e9;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void domn(int p,int k,int cnt){
        if(t[p].mx>k){
            t[p].mx=k;
            t[p].cnt+=cnt;
        }
    }

    void pushdown(int p){
        if(t[p].cnt){
            domn(ls,t[p].mx,t[p].cnt);
            domn(rs,t[p].mx,t[p].cnt);
            t[p].cnt=0;
        }
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].mx<=k) return;
        if(t[p].l>=fl&&t[p].r<=fr&&t[p].cmx<k){
            t[p].mx=k;
            t[p].cnt++;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].cnt;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

}sg;

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
    read(n,q);
    for(int i=1;i<=n;i++){
        read(a[i]);
        chg[i].push_back(pir(0,a[i]));
    }
    sg.build(1,1,q);
    for(int i=1;i<=q;i++){
        int op,x,y;
        read(op,x);
        if(op==1){
            read(y);
            chg[x].push_back(pir(i,y));
        }else qry[x].push_back(i);
    }
    for(int i=1;i<=n;i++){
        chg[i].push_back(pir(q,0));
    }
    memset(ans,-1,sizeof(ans));
    for(int i=n;i>=1;i--){
        for(int j=0;j<chg[i].size()-1;j++){
            auto p=chg[i][j];
            sg.modify(1,chg[i][j].first+1,chg[i][j+1].first,chg[i][j].second);
        }
        for(auto p:qry[i]){
            ans[p]=sg.query(1,p);
        }
    }
    for(int i=1;i<=q;i++){
        if(~ans[i]){
            put(ans[i]);
        }
    }
    return 0;
}