#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=150;
int n,m,k,lgk,tot,idx[MN][5];

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        if(!x) return;
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j];
                }
            }
        }
        return ret;
    }

}a,G,pw[70];

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

void initG(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=3;j++) idx[i][j]=++tot;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<3;j++){
            G.mat[idx[i][j]][idx[i][j+1]]++;

        }
        G.mat[idx[i][1]][0]++;
        a.mat[0][idx[i][1]]++;
    }
    G.mat[0][0]++;
}

signed main(){
    read(n,m,k);
    initG();
    for(int i=1;i<=m;i++){
        int u,v,c;
        read(u,v,c);
        G.mat[idx[u][c]][idx[v][1]]++;
    }
    int i;
    pw[0]=G;
    for(i=1;;i++){
        pw[i]=pw[i-1]*pw[i-1];
        Matrix ret=a*pw[i];
        if(ret.mat[0][0]-n>=k) break;
        if(i>62){
            cout<<-1;
            return 0;
        }
    }
    int ans=0;
    for(;i>=0;i--){
        Matrix ret=a*pw[i];
        if(ret.mat[0][0]-n<k){
            a=ret;
            if(ret.mat[0][0]-n<k) ans+=(1ll<<i);
        }
    }
    put(ans);
    return 0;
}
