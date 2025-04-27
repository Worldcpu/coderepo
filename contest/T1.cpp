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

signed main()
{
    int a,b;
    read(a),read(b);
    write(a,0),write(b);
    return 0;
}