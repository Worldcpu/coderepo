#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=420,base=13131;
int n,ans;
unordered_map<ull,int> mp;

namespace PPM{
    #ifndef LOCAL
        constexpr int BUF=1<<21;
        char in[BUF],out[BUF],*p1=in,*p2=in,*p3=out;
        #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,BUF,stdin),p1==p2)?EOF:*p1++)
        #define flush() (fwrite(out,1,p3-out,stdout))
        #define putchar(x) (p3==out+BUF&&(flush(),p3=out),*p3++=(x))
        class Flush{public:~Flush(){flush();}}_;
    #endif


    #ifdef LOCL
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
}using namespace PPM::usr;


struct Node{
    int c0,c1,c2,c3;

    Node(int c00=0,int c11=0,int c22=0,int c33=0){
        c0=c00,c1=c11,c2=c22,c3=c33;
    }

    ull hsh(){
        ull pre=0;
        pre=pre*base+c0;
        pre=pre*base+c1;
        pre=pre*base+c2;
        pre=pre*base+c3;
        return pre;
    }

    Node trans(int x){
        if(x==0){
            return *this;
        }else if(x==1){
            return Node(c1,c2,c3,c0);
        }else if(x==2){
            return Node(c2,c3,c0,c1);
        }else{
            return Node(c3,c0,c1,c2);
        }
    }
}a[MN];

void change(Node x,int k){
    for(int i=0;i<4;i++){
        mp[x.trans(i).hsh()]+=k;
    }
}

signed main(){
    read(n);
    for(int i=1;i<=n;i++){
        // cin>>a[i].c0>>a[i].c1>>a[i].c2>>a[i].c3;
        read(a[i].c0,a[i].c1,a[i].c2,a[i].c3);
        change(a[i],1);
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=0;k<=3;k++){
                Node x=a[i],y=a[j].trans(k);   
                change(x,-1),change(y,-1);
                Node p1=Node(x.c3,x.c2,y.c2,y.c1);
                Node p2=Node(x.c2,x.c1,y.c3,y.c2);
                Node p3=Node(x.c1,x.c0,y.c0,y.c3);
                Node p4=Node(x.c0,x.c3,y.c1,y.c0);

                int cp1,cp2,cp3,cp4;
                cp1=mp[p1.hsh()];
                change(p1,-1);
                cp2=mp[p2.hsh()];
                change(p2,-1);
                cp3=mp[p3.hsh()];
                change(p3,-1);
                cp4=mp[p4.hsh()];
                change(p4,-1);

                ans+=cp1*cp2*cp3*cp4;

                change(p1,1),change(p2,1),change(p3,1),change(p4,1);
                change(x,1),change(y,1);
            }
        }
    }
    put(ans/3);
    return 0;
}