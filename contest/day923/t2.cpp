#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+15,MQ=5e5+15;
int a[MN],n,q,ans;
bool in[MN];
vector<int> vct;
multiset<ll> st;
unordered_map<int,ll> mp[MQ];

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
	freopen("more.in","r",stdin) ; 
	freopen("more.out","w",stdout) ;
    read(n,q);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    for(int i=1;i<n;i++){
        if(n%i==0){
            in[i]=1;
        }
    }
    for(int i=1;i<n;i++){
        for(int j=i+i;j<n;j+=i){
            in[i]&=!in[j];
        }
    }
    for(int i=1;i<n;i++){
        if(in[i]){
            vct.push_back(i);
        }
    }
    ans=0;
    for(auto gd:vct){
        for(int j=1;j<=n;j++){
            mp[gd][(j)%gd]+=a[j];
        }
        for(auto p:mp[gd]){
            st.insert(p.second*gd);
        }
    }
    put((*st.rbegin()));
    while(q--){
        int x,y;
        read(x,y);
        for(auto gd:vct){
            st.erase(st.find(mp[gd][x%gd]*gd));
            mp[gd][x%gd]+=y-a[x];
            st.insert(mp[gd][x%gd]*gd);
        }
        a[x]=y;
        put((*st.rbegin()));
    }


    return 0;
}