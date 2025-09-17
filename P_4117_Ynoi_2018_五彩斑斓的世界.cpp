#include<bits/stdc++.h>
#define il inline
using namespace std;
constexpr int MN=1e6+15,MV=1e5+15,MQ=5e5+15,INF=2e9;
struct Query{
    int op,l,r,x;
}qry[MN];
int n,m,a[MN],ans[MN],b[MN],pos[MQ];
vector<int> pz;

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


namespace DSU{
    int pre[MN],siz[MQ];

    il int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
    
    il void merge(int x,int y){ // merge x -> y on |V|
        if(!pos[x]) return;
        if(!pos[y]){
            pos[y]=pos[x];
            b[pos[y]]=y;
            siz[y]+=siz[x];
        }else{
            pre[pos[x]]=pos[y];
            siz[y]+=siz[x];
        }
        pos[x]=siz[x]=0;
    }

    il void cleardsu(int l,int r){
        for(int i=l;i<=r;i++){
            pre[i]=i;
        }
    }

}using namespace DSU;

namespace FKOP{
    int blen,bcnt,bmx,tag;

    il void initk(int n){
        blen=bcnt=sqrt(n);
        if(blen*blen!=n){
            bcnt++;
        }
    }

    il void init(int id,int L,int R,bool ck=1){
        cleardsu(L,R);
        bmx=-INF;
        tag=0;
        if(ck){
            memset(pos,0,sizeof(pos));
            memset(siz,0,sizeof(siz));
        }
        for(int i=L;i<=R;i++) b[i]=0;
        for(int i=L;i<=R;i++){
            bmx=max(bmx,a[i]);
            if(!pos[a[i]]){
                pos[a[i]]=i;
                b[i]=a[i];
                siz[a[i]]=1;
                pre[i]=i;
            }else pre[i]=pos[a[i]],siz[a[i]]++;
        }
    }

    il void bj(int fl,int fr,int id,int x){
        int L=(id-1)*blen+1,R=min(id*blen,n);
        int l=max(fl,L),r=min(fr,R);
        for(int i=L;i<=R;i++){
            a[i]=b[root(i)];
            siz[a[i]]=0,pos[a[i]]=0;
            a[i]-=tag;
        }
        for(int i=L;i<=R;i++){
            b[i]=0;
        }
        for(int i=l;i<=r;i++){
            if(a[i]>x) a[i]-=x;
        }
        init(id,L,R,0);
    }

    il int query(int fl,int fr,int id,int x){
        int L=(id-1)*blen+1,R=min(id*blen,n);
        int l=max(fl,L),r=min(fr,R),ret=0;
        for(int i=l;i<=r;i++){
            if(b[root(i)]==x+tag) ret++;
        }
        return ret;
    }
}using namespace FKOP;

il void solve(int id){
    int L=(id-1)*blen+1,R=min(id*blen,n);
    init(id,L,R);
    for(int i=1;i<=m;i++){
        if(qry[i].l>R||qry[i].r<L||(qry[i].op==2&&!qry[i].x)) continue;
        if(qry[i].op==1){
            if(L>=qry[i].l&&R<=qry[i].r){
                if(qry[i].x>((bmx-tag)>>1)){
                    for(int j=qry[i].x+tag+1;j<=bmx;j++){
                        if(pos[j]) merge(j,j-qry[i].x);
                    }
                    bmx=min(bmx,qry[i].x+tag);
                }else{
                    for(int j=tag;j<=qry[i].x+tag;j++){
                        if(pos[j]) merge(j,j+qry[i].x);
                    }
                    tag+=qry[i].x;
                }
            }else{
                bj(qry[i].l,qry[i].r,id,qry[i].x);
            }
        }else{
            if(qry[i].x+tag>1e5+1) continue;
            if(L>=qry[i].l&&R<=qry[i].r){
                ans[i]+=siz[qry[i].x+tag];
            }else{
                ans[i]+=query(qry[i].l,qry[i].r,id,qry[i].x);
            }
        }
    }
}

signed main(){
    read(n,m);
    initk(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        if(!a[i]) pz.push_back(i);
    }
    for(int i=1;i<=m;i++){
        read(qry[i].op,qry[i].l,qry[i].r,qry[i].x);
        if(qry[i].op==2&&!qry[i].x){
            ans[i]=upper_bound(pz.begin(),pz.end(),qry[i].r)-lower_bound(pz.begin(),pz.end(),qry[i].l);
        }
    }
    for(int i=1;i<=bcnt;i++){
        solve(i);
    }
    for(int i=1;i<=m;i++){
        if(qry[i].op==2){
            put(ans[i]);
        }
    }
    return 0;
}