#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=15,MOD=1e9+7;
int n,m,a,b,c,d,base0,base1;
string sn,sm;

struct Matrix{
    int mat[MN][MN];

    // INIT THE MATRIX
    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j];
                    ret.mat[i][j]%=MOD;
                }
            }
        }
        return ret;
    }

}M1,M2;

Matrix ksm(Matrix A,int B){

    Matrix ret(1);
    while(B>0){
        if(B&1) ret=ret*A;
        A=A*A;
        B>>=1;
    }
    return ret;
}

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
    read(sn,sm,a,b,c,d);
    base0=(a==1?MOD:MOD-1);
    for(auto p:sm){
        m=((m<<3)+(m<<1)+(p^48))%(base0);
    }
    Matrix ans;
    M1.mat[0][0]=a,M1.mat[0][1]=b,M1.mat[1][1]=1;
    M2.mat[0][0]=c,M2.mat[0][1]=d,M2.mat[1][1]=1;
    ans.mat[0][0]=ans.mat[1][0]=1;
    Matrix d=ksm(M1,(m+base0-1)%base0)*M2;
    int base1;
    if(d.mat[0][0]==1) base1=MOD;
    else base1=MOD-1;
    for(auto p:sn){
        n=((n<<3)+(n<<1)+(p^48))%(base1);
    }
    ans=ksm(d,(n+base1-1)%base1)*ksm(M1,(m+base0-1)%base0)*ans;
    put(ans.mat[0][0]);
    return 0;
}
