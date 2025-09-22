#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,m,ql[MN],qr[MN],a[MN],ans[MN],pre[MN],suf[MN];
vector<int> qry;

void solve(int l,int r,const vector<int> &q){
    if(q.empty()) return;
    if(l==r){
        for(auto p:q){
            ans[p]=a[l];
        }
        return;
    }
    int mid=(l+r)>>1;
    for(int i=l;i<=r;i++) pre[i]=suf[i]=-1e9;
    for(int i=mid;i>=l;i--){
        suf[i]=max(suf[i+1],a[i]);
    }
    for(int i=mid+1;i<=r;i++) pre[i]=max(pre[i-1],a[i]);
    vector<int> qryl,qryr;
    for(auto p:q){
        if(qr[p]<=mid) qryl.push_back(p);
        else if(ql[p]>mid) qryr.push_back(p);
        else{
            ans[p]=max(suf[ql[p]],pre[qr[p]]);
        }
    }
    solve(l,mid,qryl),solve(mid+1,r,qryr);
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

int main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    for(int i=1;i<=m;i++){
        read(ql[i],qr[i]);
        qry.push_back(i);
    }
    solve(1,n,qry);
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';

    return 0;
}