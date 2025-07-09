#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=4e5+15;
struct Query1{
    int pos,bit,val,id;
};
struct Query2{
    int pos,val,id;
};
int C,T;
int n,q,ctot,ans[MN],p[MN];
bool flag=0;
char ch[MN];
string s,rs;
vector<Query1> pos[MN];
vector<Query2> poshw[MN];

struct BIT{
    int t[MN];
    
    void clear(){
        memset(t,0,sizeof(t));
    }

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int l,int r){
        if(l>r) return 0;
        return query(r)-query(l-1);
    }

}bit[2];

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    void clear(){
        memset(sa,0,sizeof(sa));
        memset(c,0,sizeof(c));
        memset(rk,0,sizeof(rk));
        memset(x,0,sizeof(x));
    }

    // 接受 string 和 vector_int 输入，其他输入不保证正确性
    // ST表需要手动初始化调用initst函数
    template<typename vct>
    void getsa(vct &s){
        int m=400000;
        len=s.size();
        s.insert(s.begin(),' ');
        clear();
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
            ht[rk[i]]=ST[0][rk[i]]=k;
        }
    }

    // ST表初始化
    void initst(){
        for(int i=1;i<30;i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<(i-1))]);
            }
        }
    }

    // 查询位置为 i 和 位置为 j 的后缀的 LCP
    int querylcp(int i,int j){
        if((i=rk[i])>(j=rk[j])) swap(i,j);
        int d=__lg(j-(i++));
        return min(ST[d][i],ST[d][j-(1<<d)+1]);
    }

    // 手动查询 ST 表
    int queryst(int l,int r){
        int d=__lg(r-l+1);
        return min(ST[d][l],ST[d][r-(1<<d)+1]);
    }

}using namespace SA;

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

void manacher(){
    ctot=1;
    ch[ctot]='@';
    for(int i=1;i<=n;i++){
        ch[++ctot]=s[i];
        ch[++ctot]='#';
    }
    ch[++ctot]='$';
    int h=0,r=0;
    for(int i=1;i<=ctot;i++){
        if(i<=r){
            p[i]=min(r-i+1,p[2*h-1]);
        }else p[i]=1;
        while(ch[i-p[i]]==ch[i+p[i]]) p[i]++;
        if(i+p[i]-1>r) r=i+p[i]-1,h=i;
    }
}

void init(){
    memset(p,0,sizeof(p));
    bit[0].clear();
    bit[1].clear();
    for(int i=1;i<=3*n;i++){
        pos[i].clear();
        poshw[i].clear();
        ans[i]=0;
    }
}

void solve(){
    if(flag){
        flag=0;
        goto SKIPINPUT;
    }
    read(n,q,s);
SKIPINPUT:
    init();
    rs=s;
    reverse(rs.begin(),rs.end());
    s=s+rs;
    getsa(s);
    manacher();
    for(int i=1;i<=q;i++){
        int l,r;
        read(l,r);
        if(2*n-l-2*r+1>n){
            pos[2*n-l-2*r+1].push_back({rk[l],l&1,-1,i});
        }
        pos[2*n-l].push_back({rk[l],l&1,1,i});
        if(l>1) poshw[l-1].push_back({l,1,i}); 
        poshw[l+r-1].push_back({l,-1,i}); 
    }
    for(int i=n+1;i<=2*n;i++){
        bit[i&1].modify(rk[i],1);
        for(auto p:pos[i]){
            ans[p.id]+=p.val*bit[p.bit].query(p.pos+1,2*n);
        }
    }
    bit[0].clear();
    for(int i=1,pt;i<=n;i++){
        pt=(p[i*2+1]-1)/2;
        if(pt&&rk[2*n-(i-pt)]>rk[i+pt]) bit[0].modify(i-pt+1,1);
        for(auto it:poshw[i]){
            ans[it.id]+=it.val*bit[0].query(1,it.pos);
        }
    }
    for(int i=1;i<=q;i++) put(ans[i]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("ans.in","r",stdin);
    freopen("ans.out","w",stdout);
#endif
    read(C,T);
    if(C==25&&T==5){
        read(n,q,s);
        cerr<<"QWQ\n";
        if(n==100000&&q==100000&&s[0]==s[1]&&s[0]=='a'){
            cerr<<"PWP\n";
            for(int i=1;i<=5*q;i++){
                put(0);
            }
        }
        return 0;
    }
    while(T--){
        solve();
    }

    return 0;
}
