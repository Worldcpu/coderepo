#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,a[MN],res;
bitset<5000001> mp;
vector<int> clr;

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

namespace Prime{
    bitset<2241> vis;
    vector<int> prime;

    void initp(int n){
        prime.reserve(2240);
        vis[0]=vis[1]=1;
        for(int i=2;i<=n;i++){
            if(!vis[i]){
                prime.push_back(i);
            }
            for(auto p:prime){
                if(i*p>n) break;
                vis[i*p]=1;
                if(i%p==0) break;
            }
        }
    }
}using namespace Prime;

void init(){
    for(auto p:clr){
        mp[p]=0;
    }
    clr.clear();
    res=0;
}

void solve(){
    read(n);
    init();
    for(int i=1;i<=n;i++){
        read(a[i]);
    }    
    if((n&1)||n==1){
        put("Yes");
        return;
    }
    if(n==2){
        if(a[1]==a[2]) put("Yes");
        else put("No");
        return;
    }
    for(int i=1;i<=n;i++){
        for(auto p:prime){
            if(a[i]<=1) break;
            int st=0;
            while(a[i]%p==0){
                st^=1;
                a[i]/=p;
            }
            if(st){
                if(!mp[p]){
                    clr.push_back(p);
                    mp[p]=1;
                    res++;
                }else{
                    res--;
                    mp[p]=0;
                }
            }
        }
        if(a[i]>1){
            if(!mp[a[i]]){
                res++;
                clr.push_back(a[i]);
                mp[a[i]]=1;
            }else{
                res--;
                mp[a[i]]=0;
            }
        }
    }
    if(res){
        put("No");
    }
    else put("Yes");
}


int main(){
    int T;
    initp(2300);
    read(T);
    while(T--){
        solve();
    }
    return 0;
}

