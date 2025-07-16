#include<bits/stdc++.h>
#define pos(x) ((x-1)/BL+1)
using namespace std;
constexpr int MN=2e5+5,MOD=1e9+7,BL=128;
int n,m,bl,a[MN],sum[MN],L[MN],R[MN],pre[BL+15][BL+15],suf[BL+15][BL+15];

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

inline void upd(int &x){x+=x>>31&MOD;}

void init(){
    bl=(n-1)/BL+1;
    for(int i=1;i<=bl;i++){
        L[i]=(i-1)*BL+1;
        R[i]=i*BL;
    }
    R[bl]=n;
    for(int i=1;i<=bl;i++){
        sum[i]=0;
        for(int j=L[i];j<=R[i];j++){
            sum[i]+=a[j];
            upd(sum[i]-=MOD);
        }
    }
}

int query(int l,int r){
    int ql=pos(l),qr=pos(r),ret=0;
    if(ql==qr){
        for(int i=l;i<=r;i++){ret+=a[i];upd(ret-=MOD);}
        return ret;
    }
    for(int i=l;i<=R[ql];i++){ret+=a[i];upd(ret-=MOD);}
    for(int i=ql+1;i<qr;i++){ret+=sum[i];upd(ret-=MOD);}
    for(int i=L[qr];i<=r;i++){ret+=a[i];upd(ret-=MOD);}
    return ret;
}

void add(int x,int y,int z){
    z-=MOD;upd(z);
    if(x>=BL){
        for(int i=y;i<=n;i+=x){
            a[i]+=z;upd(a[i]-=MOD);
            sum[pos(i)]+=z;upd(sum[pos(i)]-=MOD);
        }
    }else{
        for(int i=x;i>=y;i--){pre[x][i]+=z;upd(pre[x][i]-=MOD);}
        for(int i=1;i<=y;i++){suf[x][i]+=z;upd(suf[x][i]-=MOD);}
    }
}

signed main(){
    read(n);read(m);
    for(int i=1;i<=n;i++)read(a[i]);
    init();
    while(m--){
        int op,x,y,z,l,r;
        read(op);
        if(op==1){
            read(x);read(y);read(z);
            add(x,y,z);
        }else{
            read(l);read(r);
            int ret=query(l,r);
            for(int i=1;i<BL;i++){
                int blkL=(l-1)/i+1,blkR=(r-1)/i+1;
                if(blkL==blkR){
                    ret+=pre[i][(r-1)%i+1];upd(ret-=MOD);
                    ret-=pre[i][(l-1)%i];upd(ret);
                }else{
                    ret+=(blkR-blkL-1LL)*pre[i][i]%MOD;upd(ret-=MOD);
                    ret+=pre[i][(r-1)%i+1];upd(ret-=MOD);
                    ret+=suf[i][(l-1)%i+1];upd(ret-=MOD);
                }
            }
            put(ret);
        }
    }
    return 0;
}
