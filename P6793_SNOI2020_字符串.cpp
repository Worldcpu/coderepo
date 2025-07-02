#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,ans,K,as[MN],bs[MN],pre[MN];
string a,b,s;
vector<int> pos[MN];

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


namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],st[30][MN];

    void getsa(string s){
        int m=1<<7,p=0;
        len=s.length();
        s=" "+s;
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            ++c[x[i]];
        }
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=len;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=len;k<<=1){
            int num=0;
            for(int i=len-k+1;i<=len;i++) y[++num]=i;
            for(int i=1;i<=len;i++){
                if(sa[i]>k) y[++num]=sa[i]-k;
            }
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=len;i++) c[x[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=len;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            swap(x,y);
            num=1,x[sa[1]]=1;
            for(int i=2;i<=len;i++){
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
                else x[sa[i]]=++num;
            }
            if(num==len) break;
            m=num;
        }
        for(int i=1;i<=len;i++) rk[sa[i]]=i;
        for(int i=1,k=0;i<=len;i++){
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=st[0][rk[i]]=k;
            pos[k].push_back(rk[i]);
        }
    }

    void initst(){
        for(int i=1;i<30;i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lcp(int i,int j){
        if((i=rk[i])>(j=rk[j])) swap(i,j);
        int d=__lg(j-(i++));
        return min(st[d][i],st[d][j-(1<<d)+1]);
    }

    int queryst(int l,int r){
        int d=__lg(r-l+1);
        return min(st[d][l],st[d][r-(1<<d)+1]);
    }

}using namespace SA;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void merge(int x,int y,int lcpl){
    int rx=root(x),ry=root(y);
    if(rx==ry) return;
    int tmp=min(as[rx],bs[ry]);
    ans+=max(0ll,K-lcpl)*tmp;
    as[rx]-=tmp;
    bs[ry]-=tmp;
    tmp=min(bs[rx],as[ry]);
    ans+=max(0ll,K-lcpl)*tmp;
    bs[rx]-=tmp;
    as[ry]-=tmp;
    as[ry]=as[rx]+as[ry],bs[ry]=bs[rx]+bs[ry];
    pre[rx]=ry;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>K>>a>>b;
    s=a+'#'+b;
    for(int i=1;i<=n;i++){
        as[i]=(i+K-1<=n);
    }
    for(int i=n+2;i<=2*n+1;i++){
        bs[i]=(i-n-1+K-1<=n);
    }
    for(int i=0;i<=2*n+1;i++){
        pre[i]=i;
    }
    getsa(s);
    initst();
    for(int i=n;i>=0;i--){
        for(auto p:pos[i]){
            merge(sa[p],sa[p-1],i);
        }
    }
    put(ans);
    return 0;
}
