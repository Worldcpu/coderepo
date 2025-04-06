#include<iostream>
using namespace std;
constexpr int MN=1e5+1;
#include<iostream>
#include<cstdio>

using namespace std;
namespace ly
{
    namespace IO
    {
        #define SIZE (1<<20)
        char in[SIZE],out[SIZE],*p1=in,*p2=in,*p3=out;
        #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,SIZE,stdin),p1==p2)?EOF:*p1++)
        #define flush() (fwrite(p3=out,1,SIZE,stdout))
        #define putchar(ch) (p3==out+SIZE&&flush(),*p3++=(ch))
        class Flush{public:~Flush(){flush();}}_;
        template<typename type>
        inline void read(type &x)
        {
            x=0;bool flag(0);char ch=getchar();
            while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
            while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
            flag?x=-x:0;
        }
        template<typename type>
        inline void write(type x,bool flag=1)
        {
            x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
            do Stack[++top]=x%10,x/=10;while(x);
            while(top) putchar(Stack[top--]|48);
            flag?putchar('\n'):putchar(' ');
        }
        #undef SIZE
        #undef getchar
        #undef putchar
        #undef flush
    }
}using namespace ly::IO;

static int n,a[MN],f[MN],g[MN];
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        f[i]=a[i];
        g[i]=1;
    }
    for(int i=n;i>=1;i--){
        if(f[i]<f[i+1]){
            for(int j=i+1;j<=n;j++){
                f[i]+=a[j];
                g[i]=g[j+1]+1;
                if(f[i]>=f[j+1]){
                    break;
                }
            }
        }else g[i]+=g[i+1];
    }
    write(g[1]);
    return 0;
}