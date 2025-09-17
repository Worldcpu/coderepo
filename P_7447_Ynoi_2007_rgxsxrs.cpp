#include<bits/stdc++.h>
#define LOCAL // Remeber to Remove !
#define ll long long
using namespace std;
constexpr int MN=5e5+1,INF=2e9,MK=2e4+15,B=32;
int n,m,a[MN],bel[MN],pw[40],rt[40],mxv,mxb;

struct FKSegment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int mn,mx,len,tag;
        ll sum;
        int lson,rson;
        Node(){ mn=INF; mx=-INF; len=0; tag=0; sum=0; lson=rson=0; }
    }t[MN<<2];
    int tot;

    inline int getid(int x){
        if(x<=0) return 0;
        int id=0;
        while(id+1<=mxb && pw[id+1] <= x) ++id;
        return id;
    }

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
        t[p].mx=max(t[ls].mx,t[rs].mx);
        t[p].len=t[ls].len+t[rs].len;
        t[p].sum=t[ls].sum+t[rs].sum;
    }

    void rebuild(int p,int l,int r,int id){
        t[p].mn=INF,t[p].mx=-INF,t[p].len=0,t[p].sum=0;
        for(int i=l;i<=r;i++){
            if(bel[i]!=id) continue;
            t[p].mx=max(t[p].mx,a[i]);
            t[p].mn=min(t[p].mn,a[i]);
            t[p].len++;
            t[p].sum+=a[i];
        }
    }

    void doadd(int p,int k){
        if(!t[p].len) return;
        t[p].mn+=k;
        t[p].mx+=k;
        t[p].sum+=1ll*t[p].len*k;
        t[p].tag+=k;
    }

    void pushdown(int p,int l,int r,int id){
        if(t[p].tag){
            if(r-l < B){ 
                for(int i=l;i<=r;i++){
                    if(bel[i]==id) a[i]+=t[p].tag;
                }
            }
            else{
                doadd(ls,t[p].tag);
                doadd(rs,t[p].tag);
            }
            t[p].tag=0;
        }
    }

    void build(int &p,int l,int r,int id){
        p=++tot;
        if(r-l < B){
            rebuild(p,l,r,id);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid,id);
        build(rs,mid+1,r,id);
        pushup(p);
    }

    void insert(int p,int l,int r,int pos,int k,int id){
        if(r-l < B){ 
            pushdown(p,l,r,id);
            bel[pos]=id;
            t[p].mn=min(t[p].mn,k);
            t[p].mx=max(t[p].mx,k);
            t[p].sum+=k;
            t[p].len++;
            return;
        }
        pushdown(p,l,r,id);
        int mid=(l+r)>>1;
        if(mid>=pos) insert(ls,l,mid,pos,k,id);
        else insert(rs,mid+1,r,pos,k,id);
        pushup(p);
    }

    void update(int p,int l,int r,int fl,int fr,int k,int id){
        if(t[p].mx<=k||!t[p].len) return;
        if(l>=fl&&r<=fr&&t[p].mn-k>=pw[id]){
            doadd(p,-k);
            return;
        }
        if(r-l < B){ 
            pushdown(p,l,r,id);
            int L=max(l,fl),R=min(r,fr);
            for(int i=L;i<=R;i++){
                if(bel[i]!=id||a[i]<=k) continue;
                a[i] -= k;
                if(a[i] >= pw[id]) continue;
                int newid = getid(a[i]);
                insert(rt[newid],1,n,i,a[i],newid);
            }
            rebuild(p,l,r,id);
            return;
        }
        pushdown(p,l,r,id);
        int mid=(l+r)>>1;
        if(mid>=fl) update(ls,l,mid,fl,fr,k,id);
        if(mid<fr) update(rs,mid+1,r,fl,fr,k,id);
        pushup(p);
    }

    ll querysum(int p,int l,int r,int fl,int fr,int id){
        if(l>=fl&&r<=fr){
            return t[p].sum;
        }else if(r-l < B){ 
            ll ret=0; 
            int L=max(l,fl),R=min(r,fr);
            for(int i=L;i<=R;i++){
                if(bel[i]==id){
                    ret+=a[i]+t[p].tag;
                }
            }
            return ret;
        }
        pushdown(p,l,r,id);
        int mid=(l+r)>>1; 
        ll ret=0;
        if(mid>=fl) ret+=querysum(ls,l,mid,fl,fr,id);
        if(mid<fr) ret+=querysum(rs,mid+1,r,fl,fr,id);
        return ret;
    }

    int querymn(int p,int l,int r,int fl,int fr,int id){
        if(!t[p].len) return INF; 
        if(l>=fl&&r<=fr){
            return t[p].mn;
        }else if(r-l < B){
            int ret=INF,L=max(l,fl),R=min(r,fr);
            for(int i=L;i<=R;i++){
                if(bel[i]==id){
                    ret=min(ret,(int)(a[i]+t[p].tag));
                }
            }
            return ret;
        }
        pushdown(p,l,r,id);
        int mid=(l+r)>>1; int ret=INF;
        if(mid>=fl) ret=min(ret,querymn(ls,l,mid,fl,fr,id));
        if(mid<fr) ret=min(ret,querymn(rs,mid+1,r,fl,fr,id));
        return ret;
    }

    int querymx(int p,int l,int r,int fl,int fr,int id){
        if(!t[p].len) return -INF; 
        if(l>=fl&&r<=fr){
            return t[p].mx;
        }else if(r-l < B){ 
            int ret=-INF,L=max(l,fl),R=min(r,fr);
            for(int i=L;i<=R;i++){
                if(bel[i]==id){
                    ret=max(ret,(int)(a[i]+t[p].tag));
                }
            }
            return ret;
        }
        pushdown(p,l,r,id);
        int mid=(l+r)>>1,ret=-INF;
        if(mid>=fl) ret=max(ret,querymx(ls,l,mid,fl,fr,id));
        if(mid<fr) ret=max(ret,querymx(rs,mid+1,r,fl,fr,id));
        return ret;
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

namespace FK{
    void initpw(int n){
        pw[0]=1;
        for(int i=1;i<=n;i++) pw[i]=pw[i-1]*B;
    }

    void initfk(){
        mxv=0;
        for(int i=1;i<=n;i++){
            mxv=max(mxv,a[i]);
        }
        mxb = 0;
        if(mxv>0){
            int tmp = mxv;
            while(tmp >= B){
                tmp /= B;
                ++mxb;
            }
        }
        initpw(mxb);
        for(int i=1;i<=n;i++){
            bel[i]=sg.getid(a[i]);
        }
        for(int i=0;i<=mxb;i++){
            sg.build(rt[i],1,n,i);
        }
    }

    void modify(int fl,int fr,int k){
        for(int i=min(mxb, sg.getid(k));i<=mxb;i++){
            sg.update(rt[i],1,n,fl,fr,k,i);
        }
    }

    ll querysum(int fl,int fr){
        ll ret=0;
        for(int i=0;i<=mxb;i++){
            ret+=sg.querysum(rt[i],1,n,fl,fr,i);
        }
        return ret;
    }

    int querymn(int fl,int fr){
        int ret=INF;
        for(int i=0;i<=mxb;i++){
            ret=min(ret,sg.querymn(rt[i],1,n,fl,fr,i));
        }
        return ret;
    }

    int querymx(int fl,int fr){
        int ret=-INF;
        for(int i=0;i<=mxb;i++){
            ret=max(ret,sg.querymx(rt[i],1,n,fl,fr,i));
        }
        return ret;
    }
}

signed main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    FK::initfk();
    for(ll i=1,lstans=0;i<=m;i++){
        int op,l,r,x;
        read(op,l,r);
        l^=lstans; r^=lstans;
        if(op==1){
            read(x);
            x^=lstans;
            FK::modify(l,r,x);
        }else{
            put((lstans=FK::querysum(l,r)),0);
            put(FK::querymn(l,r),0);
            put(FK::querymx(l,r));
            lstans&=((1<<20)-1);
        }
    }
    return 0;
}
