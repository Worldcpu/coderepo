#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN=2e5+15;
constexpr int MAXB=1520;
constexpr int MAXNODE = 1800000;
int n, q, p[MAXN], L[MAXB], R[MAXB], pos[MAXN], rt[MAXB],len;

struct Segment{
    struct Node{
        int lson, rson, cnt;
        ll sum, add;
    }t[MAXNODE];
    int tot = 0;

    void pushup(int p){
        if(!p) return;
        t[p].sum = t[t[p].lson].sum + t[t[p].rson].sum;
        t[p].cnt = t[t[p].lson].cnt + t[t[p].rson].cnt;
    }

    void doadd(int p, ll k){
        if(!p) return;
        t[p].sum+=(ll)t[p].cnt * k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(!p) return;
        ll v=t[p].add;
        if(v){
            if(t[p].lson) doadd(t[p].lson,v);
            if(t[p].rson) doadd(t[p].rson,v);
            t[p].add=0;
        }
    }

    ll querysum(int p, int l, int r, int fl, int fr){
        if(!p||l>fr||r<fl) return 0;
        if(l>=fl&&r<=fr) return t[p].sum;
        pushdown(p);
        int mid = (l+r)>>1;
        ll res=0;
        if(mid>=fl) res+=querysum(t[p].lson,l,mid,fl,fr);
        if(mid<fr) res+=querysum(t[p].rson,mid+1,r,fl,fr);
        return res;
    }

    void updatecnt(int &p,int l,int r,int posv){
        if(!p) p=++tot;
        t[p].cnt++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(posv<=mid) updatecnt(t[p].lson,l,mid,posv);
        else updatecnt(t[p].rson,mid+1,r,posv);
        pushup(p);
    }

    void updatesum(int p,int l,int r,int fl,int fr,ll k){
        if(!p||l>fr||r<fl) return;
        if(l>=fl&&r<=fr){ doadd(p,k); return;}
        pushdown(p);
        int mid=(l+r)>>1;
        if(mid>=fl) updatesum(t[p].lson,l,mid,fl,fr,k);
        if(mid<fr) updatesum(t[p].rson,mid+1,r,fl,fr,k);
        pushup(p);
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

void init_blocks(){
    len=sqrt(n);
    for(int i=1;i<=len;i++){
        L[i]=R[i-1]+1;
        R[i]=i*len;
        for(int j=L[i];j<=R[i];j++) pos[j]=i;
    }
    if(R[len]<n){
        R[++len]=n;
        L[len]=R[len-1]+1;
        for(int j=L[len];j<=R[len];j++) pos[j]=len;
    }
    for(int i=1;i<=len;i++){
        for(int j=L[i];j<=R[i];j++) sg.updatecnt(rt[i],1,n,p[j]);
    }
}

void solveop1(int fl,int fr,ll k){
    for(int i=1;i<=len;i++) sg.updatesum(rt[i],1,n,fl,fr,k);
}

ll solveop2(int fl,int fr){
    int ql=pos[fl],qr=pos[fr];
    ll ret=0;
    if(ql==qr){
        for(int i=fl;i<=fr;i++) ret+=sg.querysum(rt[ql],1,n,p[i],p[i]);
        return ret;
    }
    for(int i=fl;i<=R[ql];i++) ret+=sg.querysum(rt[ql],1,n,p[i],p[i]);
    for(int b=ql+1;b<=qr-1;b++) if(rt[b]) ret+=sg.t[rt[b]].sum;
    for(int i=L[qr];i<=fr;i++) ret+=sg.querysum(rt[qr],1,n,p[i],p[i]);
    return ret;
}

int main(){
    read(n,q);
    for(int i=1;i<=n;i++) read(p[i]);
    init_blocks();
    ll ans=0;
    while(q--){
        int op,l,r;
        read(op,l,r);
        l^=ans; r^=ans;
        if(l>r) swap(l,r);
        if(op==1){
            ll k;
            read(k);
            k^=ans;
            solveop1(l,r,k);
        }else{
            ans=solveop2(l,r);
            put(ans);
        }
    }
    return 0;
}
