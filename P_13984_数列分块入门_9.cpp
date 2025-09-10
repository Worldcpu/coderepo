#include<iostream>
#include<unordered_map>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int MN=3e5+15,MQ=620;
unordered_map<int,int> um,fum;//存离散化后的值，通过离散化的值找原数
int ls=0;
//zs数字表示从第i个块到第j个块的众数编号
int n,zs[MQ][MQ],l[MQ],r[MQ],pos[MN],a[MN],len,bok[MN];
int tong[MN]{};
vector<int> numpos[MN];

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

void build(){
    len=sqrt(n);
    for(int i=1;i<=len;i++){
        l[i]=r[i-1]+1;
        r[i]=i*len;
    }
    r[len]=n;
    for(int i=1;i<=len;i++){
        for(int j=l[i];j<=r[i];j++){
            pos[j]=i;
        }
    }
    for(int i=1;i<=len;i++){//找众数，用桶计数
        int zsnum=0,maxx=0;
        for(int j=l[i];j<=n;j++){
            tong[a[j]]++;
            if(maxx<tong[a[j]]||(maxx==tong[a[j]]&&zsnum>a[j])){//第一个是找到一个出现次数更多的，第二个是要求众数编号最小
                zsnum=a[j];
                maxx=tong[a[j]];
            }
            zs[i][pos[j]]=zsnum;
        }
        for(int j=l[i];j<=n;j++){
            tong[a[j]]--;
        }
    }
}
//获取这个数在[l,r]区间内出现次数（即众数），使用二分
int getcishu(int fl,int fr,int k){
    auto start=lower_bound(numpos[k].begin(),numpos[k].end(),fl);
    auto end=upper_bound(numpos[k].begin(),numpos[k].end(),fr);
    return end-start;
}
int query(int fl,int fr){
    int ql=pos[fl],qr=pos[fr];
    int zsnum=0,maxx=0;
    if(ql==qr){
        //暴力找
        for(int i=fl;i<=fr;i++){
            tong[a[i]]++;
            if(maxx<tong[a[i]]||(maxx==tong[a[i]]&&zsnum>a[i])){
                zsnum=a[i];
                maxx=tong[zsnum];
            }
        }
        for(int j=fl;j<=fr;j++) tong[a[j]]--;
        return bok[zsnum];//反向查找直接返回答案
    }
    //先把答案设置在中间的块
    //显然答案只能在中间块或左右两个块中（如果左中或右中合并最终答案还是中间的众数）
    zsnum=zs[ql+1][qr-1];
    maxx=getcishu(fl,fr,zsnum);
    for(int i=fl;i<=r[ql];i++){
        int ret=getcishu(fl,fr,a[i]);
        if(maxx<ret||(maxx==ret&&zsnum>a[i])){
            zsnum=a[i];
            maxx=ret;
        }
    }
    for(int i=l[qr];i<=fr;i++){
        int ret=getcishu(fl,fr,a[i]);
        if(maxx<ret||(maxx==ret&&zsnum>a[i])){
            zsnum=a[i];
            maxx=ret;
        }
    }
    return bok[zsnum];
}
int main(){
    read(n);
    // for(int i=1;i<=n;i++){
    //     int p;
    //     cin>>p;
    //     if(um.find(p)==um.end()){
    //         um[p]=++ls;
    //         fum[ls]=p;
    //     }
    //     a[i]=um[p];
    //     numpos[a[i]].push_back(i);//1~n保证内部单调递增不用sort降级nlogn（?）
    // }
    for(int i=1;i<=n;i++){
        read(a[i]);
        bok[i]=a[i];
    }
    sort(bok+1,bok+1+n);
    int num=unique(bok+1,bok+1+n)-bok-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(bok+1,bok+1+num,a[i])-bok;
        numpos[a[i]].push_back(i);
    }
    build();
    int bef=0;
    for(int i=1;i<=n;i++){
        int fl,fr;
        read(fl,fr);
        bef=query(fl,fr);
        put(bef);
        // cout<<query(fl,fr)<<endl;
    }
    // len=sqrt(n);
    return 0;
}