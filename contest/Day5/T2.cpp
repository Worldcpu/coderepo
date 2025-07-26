#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define lint unsigned long long
using namespace std;
constexpr int MN=1e6+15;
constexpr ull base=13131;
int n;
string s,t0;
ull pw[MN];

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

namespace Sub1{
    constexpr int MM=15;
    string t[MN];
    ull hsh[MM][MM];

    ull gethsh(ull* hsh,int l,int r){
        return hsh[r]-hsh[l-1]*pw[r-l+1];
    }

    void dohsh(ull *hsh,string s){
        for(int i=0;i<s.length();i++){
            hsh[i+1]=hsh[i]*base+s[i];
        }
    }

    ull getfhsh(string s){
        ull ret=0;
        for(int i=0;i<s.length();i++){
            ret=ret*base+s[i];
        }
        return ret;
    }

    void solve(){
        t[0]=t0;
        for(int i=1;i<=n;i++){
            int K;
            string qwq,d;
            cin>>K;
            for(int j=1;j<=K;j++){
                int x;
                cin>>x;
                qwq=qwq+t[x];
            }
            cin>>d;
            qwq=qwq+d;
            t[i]=qwq;
        }
        for(int i=0;i<=n;i++){
            dohsh(hsh[i],t[i]);
        }
        ull hs=getfhsh(s);
        for(int i=1;i<=n;i++){
            int cnt=0;
            for(int j=s.length();j<=t[i].length();j++){
                if(gethsh(hsh[i],j-s.length()+1,j)==hs){
                    cnt++;
                }
            }
            cout<<cnt<<'\n';
        }
    }
}

namespace Sub2{
    lint len[MN];

    void solve(){
        lint lens=s.length();
        len[0]=t0.length();
        for(int i=1;i<=n;i++){
            int K;
            string d;
            cin>>K;
            for(int j=1,x;j<=K;j++){
                cin>>x;
                len[i]+=len[x];
            }
            cin>>d;
            len[i]+=d.length();
        }
        for(int i=1;i<=n;i++){
            put(len[i]-lens+1);
        }

    }

}

namespace Sub3{
    constexpr int MM=1520;

    // 维护长为 S 的后缀哈希
    ull hsh[MM][MM],hs,tmp[MM],ans[MN];
    int lens;

    ull gethsh(ull* hsh,int l,int r){
        return hsh[r]-hsh[l-1]*pw[r-l+1];
    }

    void dohsh(ull *hsh,string s){
        for(int i=0;i<s.length();i++){
            hsh[i+1]=hsh[i]*base+s[i];
        }
    }

    // 整个哈希
    ull getfhsh(string s){
        ull ret=0;
        for(int i=0;i<s.length();i++){
            ret=ret*base+s[i];
        }
        return ret;
    }
    
    // 反向的长度哈希
    void dofhshlen(ull *hsh,string s,int len){
        cerr<<"DOING: "<<s<<'\n';
        for(int i=0;i<len;i++){
            cerr<<s[n-len+i]<<" ";
            hsh[i+1]=hsh[i]*base+s[n-len+i];
        }
        cerr<<'\n';
    }
    
    void solve(){
        lens=s.length();
        hs=getfhsh(s);
        dofhshlen(hsh[0],t0,s.length());
        for(int i=1;i<=n;i++){
            int k,pos,lend,ret=0;
            string d;
            cin>>k>>pos>>d;
            dohsh(tmp,d);
            lend=d.length();
            for(int j=lens+1;j<=lend;j++){
                if(gethsh(tmp,j-lens,j)==hs){
                    ret++;
                }
            }
            for(int j=lens;j>=1;j--){
                if(gethsh(hsh[pos],j,lens)*pw[lens-j+1]+tmp[j-1]==hs){
                    ret++;
                }
            }
            ret+=ans[pos];
            ans[i]=ret;
            cout<<ret<<'\n';
            if(lend>=lens){
                for(int j=1;j<=lens;j++){
                    hsh[i][j]=tmp[j];
                }
            }else{
                for(int j=lend;j<=lens;j++){
                    hsh[i][j-lend+1]=gethsh(hsh[pos],lend,j);
                }
                for(int j=1,lst=lens-lend+2;j<=lens;j++,lst++){
                    hsh[i][lst]=hsh[i][lst-1]*base+tmp[j];
                }
            }
        }
    }

}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*base;
    }
}


signed main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    initpw();
    cin>>n>>s>>t0;
    if(n<=10&&s.length()<=10&&t0.length()<=10){
        Sub1::solve();
        return 0;
    }
    bool isz=1;
    for(auto c:s){
        if(c!='0'){
            isz=0;
            break;
        }
    }
    for(auto c:t0){
        if(c!='0'){
            isz=0;
            break;
        }
    }
    if(isz){
        Sub2::solve();
    }else Sub1::solve();


    return 0;
}