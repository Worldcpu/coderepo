#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,q,a[MN];
pir st[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    //Maintain the values and the range in which those values lie.
    struct VNode{
        int l,r,v;

        VNode(int ll=0,int rr=0,int vv=0){
            l=ll,r=rr,v=vv;
        }

        friend bool operator<(const VNode &x,const VNode &y){
            return x.v<y.v;
        }

        friend VNode operator*(const VNode &x,int y){
            return VNode(x.l,x.r,x.v*y);
        }

        friend VNode operator+(const VNode &x,const VNode &y){
            return VNode(x.l,y.r,x.v+y.v);
        }
    };

    struct Node{
        VNode smx,smn,lmx,rmx,lmn,rmn,sum;

        Node(){
            // do nothing QWQ.
        }
        
        // Only used on Segment's Leaves Node
        Node(int pos,int v){
            smx=VNode(pos,pos,v);
            smn=VNode(pos,pos,v);
            lmx=VNode(pos,pos,v);
            rmx=VNode(pos,pos,v);
            lmn=VNode(pos,pos,v);
            rmn=VNode(pos,pos,v);
            sum=VNode(pos,pos,v);
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.smx=max({x.smx,y.smx,x.rmx+y.lmx});
            ret.smn=min({x.smn,y.smn,x.rmn+y.lmn});

            ret.lmx=max(x.lmx,x.sum+y.lmx);
            ret.rmx=max(y.rmx,x.rmx+y.sum);

            ret.lmn=min(x.lmn,x.sum+y.lmn);
            ret.rmn=min(y.rmn,x.rmn+y.sum);

            ret.sum=x.sum+y.sum;

            return ret;
        }

        void flip(){
            swap(smx,smn);
            swap(lmx,lmn);
            swap(rmx,rmn);
            smx=smx*-1;
            smn=smn*-1;
            lmx=lmx*-1;
            rmx=rmx*-1;
            lmn=lmn*-1;
            rmn=rmn*-1;
            sum=sum*-1;
        }
    };

    struct SNode{
        int l,r,rev;
        Node val;   
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void dorev(int p){
        t[p].val.flip();
        t[p].rev^=1;
    }

    void pushdown(int p){
        if(t[p].rev){
            dorev(ls);
            dorev(rs);
            t[p].rev^=1;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].rev=0;
        if(l==r){
            t[p].val=Node(l,a[l]);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void rev(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            dorev(p);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) rev(ls,fl,fr);
        if(mid<fr) rev(rs,fl,fr);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=Node(pos,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }
    #undef ls
    #undef rs
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
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    sg.build(1,1,n);
    read(q);
    while(q--){
        int op,l,r,x;
        read(op,l,r);
        if(op==0){
            sg.modify(1,l,r);
        }else{
            read(x);
            int ret=0,top=0;
            while(x--){
                auto qwq=sg.query(1,l,r).smx;
                if(qwq.v<=0) break;
                ret+=qwq.v;
                sg.rev(1,qwq.l,qwq.r);
                st[++top]=pir(qwq.l,qwq.r);
            }
            put(ret);
            for(int i=1;i<=top;i++){
                sg.rev(1,st[i].first,st[i].second);
            }
        }
    }
    return 0;
}