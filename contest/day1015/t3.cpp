// #include<bits/stdc++.h>
// #define int long long
// using namespace std;
// constexpr int B=20,MV=(1<<B),V=(1<<B)-1,MN=1e6+15;
// int n,q;
// string st;

// namespace FK{
//     int pre[MV],suf[MV],sum[MV],tag[MN],pos[MN],blen;
//     int f[MV];

//     int getst(int l,int r){
//         return ((1<<r)-1)-((1<<l)-1);
//     }

//     void init(){
//         blen=(n+B-1)/B;
//         for(int i=0;i<MV;i++){
//             for(int j=0;j<B;j++){
//                 if((i>>j)&1){
//                     pre[i]++;
//                 }else break;
//             }
//             for(int j=B-1;j>=0;j--){
//                 if((i>>j)&1){
//                     suf[i]++;
//                 }else break;
//             }
//             int lst=0;
//             for(int j=0;j<B;j++){
//                 if((i>>j)&1){
//                     lst++;
//                     sum[i]+=lst;
//                 }else lst=0;
//             }
//         }
//         for(int i=1;i<=n;i++){
//             pos[i]=(i-1)/B;
//         }

//         for(int i=1;i<=n;i++){
//             if(st[i]=='1'){
//                 int p=(i-1)%B;
//                 f[pos[i]]|=(1<<p);
//             }
//         }
//     }

//     void pushdown(){
//         for(int i=0,rev=0;i<=blen;i++){
//             rev^=tag[i];
//             tag[i]=0;
//             if(rev) f[i]^=getst(0,B);
//         }
//     }

//     void dorev(int fl,int fr){
//         int ql=pos[fl],qr=pos[fr];
//         int pfl=(fl-1)%B,pfr=(fr-1)%B;
//         if(ql==qr){
//             f[ql]^=getst(pfl,pfr+1);
//             return;
//         }
//         f[ql]^=getst(pfl,B);
//         f[qr]^=getst(0,pfr+1);
//         tag[ql+1]^=1;
//         tag[qr]^=1;
//     }

//     int getst(int id,int k,int len){
//         int ret=0;
//         if(len==B){
//             if(k==0) return f[id];
//             else{
//                 return (((f[id]&getst(k,B))>>k)+((f[id+1]&(getst(0,k)))<<(B-k)));
//             }
//         }
//         for (int i = id * B + k, it = 0; it < len; ++i, ++it) {
//             ret|=((f[i/B]>>(i%B))&1)<<it;
//         }


//         return ret;
//     }

//     int query(int len,int a,int b){
//         int ans=0,lst=0;
//         pushdown();
//         int qa=pos[a],qb=pos[b],pa=(a-1)%B,pb=(b-1)%B;
//         while(len>0){
//             int now=min(B,len);
//             int st=getst(qa,pa,now)^getst(qb,pb,now)^getst(0,now);
//             ans+=sum[st]+lst*pre[st];
//             lst=(pre[st]==B?lst+B:suf[st]);

//             qa++,qb++;
//             len-=now;
//         }
//         return ans;
//     }

// }using namespace FK;

// signed main(){
//     cin>>n>>q>>st;
//     st=" "+st;
//     init();
//     while(q--){
//         int op,l,r,a,b;
//         cin>>op;
//         if(op==1){
//             cin>>l>>r;
//             dorev(l,r);
//         }else{
//             cin>>l>>a>>b;
//             cout<<query(l,a,b)<<'\n';
//         }
//     }
    


//     return 0;
// }
#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,q,a[MN],b[MN];

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
    int n, q;
    read(n,q);
    for (int i = 1; i <= n; i++) {
        char x;
        read(x);
        a[i]=x-'0';
    }
    for(int i=n;i>=1;i--){
        a[i]^=a[i-1];
    }
    while (q--) {
        int op,l,r,x,y;
        read(op);
        if (op == 1) {
            read(l,r);
            a[l]^=1;
            a[r+1]^=1;
        }else{
            read(l,x,y);
            long long cnt=0,ret=0;
            for(int i=1;i<=n;i++){
                b[i]=b[i-1]^a[i];
            }
            for(int i=0;i<l;i++){
                if(b[x+i]==b[y+i]){
                    cnt++;
                    ret+=cnt;
                }else cnt=0;
            }
            put(ret);
        }
    }
}