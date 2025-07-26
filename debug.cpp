#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3004,INF=1e9;
int n,K,q,a[MN],p[MN],pos[MN],sum0[MN],suma[MN],num[MN];

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

struct Matrix{
    int mat[MN][MN];

    friend Matrix operator *(const Matrix &x,const Matrix &y){
        Matrix c,ret;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                c.mat[i][j]=i==j?i:0;
                ret.mat[i][j]=i==j?0:INF;
            }
        }
        for(int len=2;len<=n;len++){
            for(int l=1,r=len;r<=n;l++,r++){
                for(int k=c.mat[l][r-1];k<=c.mat[l+1][r];k++){
                    int t=x.mat[l][k]+y.mat[k][r];
                    if(ret.mat[l][r]>t){
                        ret.mat[l][r]=t;
                        c.mat[l][r]=k;
                    }
                }
            }
        }
        return ret;
    }

}A,B,ans[2];

inline int w1(int l,int r){
    if(l>r) return 0;
    int fl=a[l]==1?pos[l]:pos[l]+1,fr=pos[r];
    int mid=(fl+fr)>>1;
    return sum0[num[mid]]*(mid-fl+1)-(suma[num[mid]]-suma[l-1])+(suma[r]-suma[num[mid]])-sum0[num[mid]]*(fr-mid);
}

inline int w2(int l,int r){
    if(l>r) return 0;
    int fl=a[l]==1?pos[l]:pos[l]+1,fr=pos[r];
    int mid=(fl+fr)>>1;
    return sum0[r]*(fr-fl+1)-(suma[r]-suma[l-1]);
}

inline Matrix solve(){
    int tot=0,k=K/2-1;
    for(int i=1;i<=n;i++){
        sum0[i]=sum0[i-1]+(a[i]==0);
        suma[i]=suma[i-1]+sum0[i]*a[i];
        if(a[i]==1){
            pos[i]=++tot;
            num[tot]=i;
        }else pos[i]=pos[i-1];
    }
    if(K==1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                A.mat[i][j]=w2(i,j);
            }
        }
        return A;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            A.mat[i][j]=w1(i,j);
            B.mat[i][j]=w1(i+1,j);
        }
    }
    for(int i=1;i<=k;i<<=1,B=B*B)if(k&i) A=A*B;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            B.mat[i][j]=w2(i+1,j);
        }
    }
    if(K&1) A=A*B;
    return A;
}

int main(){
    read(n,K,q);
    for(int i=1,x;i<=n;i++){
        read(x);
        a[i]=a[i-1]^x;
    }
    
    for(int i=1;i<=n;i++){
        a[i]^=1;
    }
    ans[1]=solve();
    for(int i=1;i<=n;i++){
        a[i]^=1;
    }
    ans[0]=solve();
    int l,r;
    while(q--){
        read(l,r);
        cout<<ans[a[l-1]].mat[l][r]<<'\n';
    }
    return 0;
}