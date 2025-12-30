#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=114514;
int n,s[MN],pre[MN],suf[30][MN],ans;
string st;


namespace FASTIO{
    #ifndef LOCAL
        constexpr auto maxn=1<<20;
        char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
        #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
        #define flush() (fwrite(out,1,p3-out,stdout))
        #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
        class Flush{public:~Flush(){flush();}}_;
    #endif
    #ifdef LOCAL
        #define getchar getchar_unlocked
        #define putchar putchar_unlocked
    #endif
    template<typename type>
    void read(type &x){
        x=0;bool flag(0);char ch=getchar();
        while(!isdigit(ch)) flag=ch=='-',ch=getchar();
        while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
        flag?x=-x:0;
    }
    void read(char &x){do{x=getchar();}while(isspace(x));}
    void read(char x[]){static char ch;ch=getchar();do{*(x++)=ch;}while(!isspace(ch=getchar())&&~ch);}
    void read(string &st){st.clear();static char ch;ch=getchar();do{st+=ch;}while(!isspace(ch=getchar())&&~ch);}
    template<typename type,typename... T>
    void read(type& x,T&... t){
        read(x);
        read(t...);
    }
    
    template<typename type>
    void write(type x){
        x<0?x=-x,putchar('-'):0;
        static short st[50],top(0);
        do{st[++top]=x%10,x/=10;}while(x);
        while(top) putchar(st[top--]|48);
    }
    void write(const char &x){putchar(x);}
    void write(const char ch[]){while(*ch) putchar(*(ch++));}
    void write(string &st){for(auto p:st) putchar(p);}
    template<typename type>
    void put(type x,bool flag=1){
        write(x);
        flag?putchar('\n'):putchar(' ');
    }
    #undef getchar
    #undef putchar
}using namespace FASTIO;

signed main(){
    read(st);
    n=st.length();
    st=" "+st;
    for(int i=0;i<26;i++){
        for(int j=n;j>=1;j--){
            suf[i][j]=suf[i][j+1]+(st[j]-'a'==i);
        }
    }
    for(int i=0;i<26;i++){
        for(int j=1;j<=n;j++){
            pre[j]=pre[j-1]+(st[j]-'a'==i);
        }
        for(int j=0;j<26;j++){
            if(i==j) continue;
            int s1=0,s2=0;
            for(int k=1;k<=n;k++){
                if(st[k]-'a'==i){
                    ans=(ans+s1*suf[j][k+1])%MOD;
                }else if(st[k]-'a'==j){
                    s2=(s2+pre[k-1]*(pre[k-1]-1)/2)%MOD;
                }else{
                    s1=(s1+s2);
                }
            }
        }
    }
    cout<<ans;

    return 0;
}