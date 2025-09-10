#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int q,op,x,y;
string st;
bitset<MN> bit[10],b1,b2,ret;

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
    read(q);
    while(q--){
        read(op,x);
        if(!op){
            read(st);
            for(int i=0;i<10;i++){
                b1=(bit[i]>>x)<<x;
                bit[i]^=b1;
                bit[i]|=(b1<<st.length());
            }
            for(int i=0;i<st.length();i++){
                bit[st[i]-'0'][i+x]=1;
            }
        }else if(op==1){
            read(y);
            for(int i=0;i<10;i++){
                b1=(bit[i]>>x)<<x;
                bit[i]^=b1;
                b1=(b1>>y)<<x;
                bit[i]|=b1;
            }
        }else{
            read(y,st);
            if(st.length()>y-x){
                put(0);
                continue;
            }
            ret.set();
            for(int i=0;i<st.length();i++){
                ret=ret&(bit[st[i]-'0']>>i);
            }
            put(((ret>>x).count()-(ret>>(y-st.size()+1)).count()));
        }
    }

    return 0;
}