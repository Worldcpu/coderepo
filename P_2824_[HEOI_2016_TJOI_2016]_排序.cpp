#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,m,q,rt[MN];

struct Segment{
#define ls t[p].son[0]
#define rs t[p].son[1]
    
    struct{
        int son[2];
        int val;
    }t[MN<<5];
    int tot=0,top=0,s[MN];

    int newnode(){
        return (top?s[top--]:++tot);
    }

    void gc(int p){
        memset(&t[p],0,sizeof(t[p]));
        s[++top]=p;
    }

    void modify(int &p,int l,int r,int pos){
        if(!p) p=newnode();
        t[p].val=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
    }

    int queryl(int p,int l,int r){
        if(l==r) return l;
        int mid=(l+r)>>1;
        return ls?queryl(ls,l,mid):queryl(rs,mid+1,r);
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        t[x].val+=t[y].val;
        t[x].son[0]=merge(t[x].son[0],t[y].son[0]);
        t[x].son[1]=merge(t[x].son[1],t[y].son[1]);
        gc(y);
        return x;
    }

    void split(int &x,int y,int v,int op){
        if(t[y].val==v) return;
        x=newnode();
        t[x].val=t[y].val-v;
        t[y].val=v;
        if(v<=t[t[y].son[op]].val){
            split(t[x].son[op],t[y].son[op],v,op);
            t[x].son[!op]=t[y].son[!op];
            t[y].son[!op]=0;
        }else{
            split(t[x].son[!op],t[y].son[!op],v-t[t[y].son[op]].val,op);
        }
    }

#undef ls
#undef rs
}sg;

struct ODTNode{
    int l,r;
    mutable int v;
    
    ODTNode(int L,int R=-1,int val=0){
        l=L,r=R,v=val;
    }
    
    bool operator<(const ODTNode &x)const{
        return l<x.l;
    }
};
struct ODT{
    set<ODTNode> s;

    auto split(int pos){
        auto it=s.lower_bound(ODTNode(pos));
        if(it!=s.end()&&it->l==pos) return it;
        it--;
        int l=it->l,r=it->r,v=it->v;
        s.erase(it);
        sg.split(rt[pos],rt[l],pos-l,v);
        s.insert(ODTNode(l,pos-1,v));
        return s.insert(ODTNode(pos,r,v)).first;
    }

    void merge(int l,int r,int val){
        auto R=split(r+1),L=split(l);
        L->v=val;
        for(auto i=++L;i!=R;i++) sg.merge(rt[l],rt[i->l]);
        s.erase(L,R);
    }

}odt;

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

signed main(){
    read(n,m);
    odt.s.insert(ODTNode(n+1,n+1,0));
    for(int i=1;i<=n;i++){
        int x;
        read(x);
        sg.modify(rt[i],0,n,x);
        odt.s.insert(ODTNode(i,i,0));
    }
    while(m--){
        int op,l,r;
        read(op,l,r);
        odt.merge(l,r,op);
    }
    read(q);
    odt.split(q+1);
    odt.split(q);
    cout<<sg.queryl(rt[q],0,n);
    return 0;
}
