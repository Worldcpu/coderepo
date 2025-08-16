#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=170,MP=1e6+15,MOD=998244353;
struct Node{
    int x,y,z,sum;
}nd[MN];
int T,m,n,K,pw[MP],inv[MP],pos[MN][MN][MN],dtot;

struct Matrix{
    int mat[MN][MN];

    Matrix(){
        clear();
    }

    void clear(){
        memset(mat,0,sizeof(mat));
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=1;i<=dtot+1;i++){
            for(int j=1;j<=dtot+1;j++){
                for(int k=1;k<=dtot+1;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+x.mat[i][k]*y.mat[k][j]%MOD)%MOD;
                }
            }
        }
        return ret;
    }

}mpw[64];

struct Vector{
    int mt[MN];

    Vector(){
        clear();
    }

    void clear(){
        memset(mt,0,sizeof(mt));
    }

    friend Vector operator*(const Vector &x,const Matrix &y){
        Vector ret;
        for(int i=1;i<=dtot+1;i++){
            for(int j=1;j<=dtot+1;j++){
                ret.mt[j]=(ret.mt[j]+x.mt[i]*y.mat[i][j]%MOD)%MOD;
            }
        }
        return ret;
    }

}A,B;

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

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    for(int i=0;i<=520;i++) inv[i]=ksm(i,MOD-2);

}

void initmt(){
    auto *p=mpw[0].mat;
    for(int i=0;i<=K;i++){
        for(int j=0;j<=(m>=2?K-i:0);j++){
            for(int k=0;k<=(m>=3?K-i-j:0);k++){
                nd[++dtot]={i,j,k,i+j+k};
                pos[i][j][k]=dtot;
            }
        }
    }
    for(int i=1;i<=dtot;i++){
        int ret=0;
        p[i][i]=inv[nd[i].sum+1];
        p[dtot+1][i]=inv[nd[i].sum+1];
        if(nd[i].x){
            ret=pos[nd[i].x-1][nd[i].y][nd[i].z];
            p[ret][i]=nd[i].x*inv[nd[i].sum+1]%MOD;
        }
        if(nd[i].y){
            int nx=nd[i].x+1,ny=nd[i].y-1,nz=nd[i].z;
            if(nd[i].sum<K){
                if(m==1) nx++;
                else if(m==2) ny++;
                else nz++;
            }
            ret=pos[nx][ny][nz];
            p[ret][i]=nd[i].y*inv[nd[i].sum+1]%MOD;
        }
        if(nd[i].z){
            int nx=nd[i].x,ny=nd[i].y+1,nz=nd[i].z-1;
            if(nd[i].sum<K){
                if(m==1) nx++;
                else if(m==2) ny++;
                else nz++;
            }
            ret=pos[nx][ny][nz];
            p[ret][i]=nd[i].z*inv[nd[i].sum+1]%MOD;
        }
    }
    p[dtot+1][dtot+1]=1;
    for(int i=1;i<=63;i++) mpw[i]=mpw[i-1]*mpw[i-1];
}


signed main(){
    freopen("y.in","r",stdin);
    freopen("y.out","w",stdout);
    initpw();
    read(T,m,K);
    initmt();
    A.mt[dtot+1]=1;
    while(T--){
        read(n);
        B=A;
        for(int i=0;i<=63;i++){
            if(n&(1ll<<i)) B=B*mpw[i];
        }
        put(B.mt[pos[m==1][m==2][m==3]]);
    }
    // https://cdn.luogu.com.cn/upload/image_hosting/z98aei12.png
    return 0;
}

/*
激辣数独扯掉了牢大露点巨大裤子！

说明开裆裤勒口考上了魔王窟联赛！

看似简单的莫队没脾气面向hdkk！

间谍剧场偷税漏税伟大腰间盘突出！

近日，河北石家庄七亩地遗址又出土了一批 Aqz 语古籍文物。
据调查，该批文物应当来自于奶龙星球，这进一步佐证了 Aqz 奶龙皇族——黑暗爆炸奶龙族的身份。
出土时，这批文物已残缺不全，但幸而，有四句话完整保存了。就让我们通过这四句话，重新走进那一段可歌可泣的英雄史诗吧。

### 激辣数独扯掉了牢大露点巨大裤子！
这句话实际上讲述了奶龙星球第一次星球大战的起源：鹰郡枪声。
首先，我们要对牢大这个人有着充分的了解，才能看懂这段话的内涵。
牢大，姓牢名大，字柯比，是肘击星球的先锋，受命前往奶龙星球刺探情报。
但是牢大这个人，极为好色，在敌国卧底期间仍没能克制住自己内心的欲望。
有一天，牢大在鹰郡刺探情报，恰巧看到了奶龙国的公主。
牢大没忍住。
哪怕牢大早就特意穿了特制的巨大裤子，也无法遮掩他的雄风。
于是，奶龙公主的贴身侍卫，有着激辣数独之称的骑士，敏锐地察觉了这一点，立即上前扯掉了牢大的裤子，揭穿了他的真面目。
这一事件，便是 **激辣数独扯掉了牢大露点巨大裤子** 。而这一事件也成为了两星球间战争的导火索，史称 **鹰郡枪声**。

### 说明开裆裤勒口考上了魔王窟联赛！
作为奶龙星球驸马的 Aqz 知道敌人对着自己的未婚妻立了后，直接红温了。
Aqz 本来想将牢大直接斩首示众，但他想到了更加恶毒的办法来惩罚牢大。
牢大对着奶龙公主雄风不倒，直冲云霄，于是 Aqz 就命人给牢大换上了开裆裤，并将裆口勒紧，使得牢大难受不已。
为了让他更加痛苦，Aqz 还让人驾驶着直升飞机，拴住牢大的裤裆口，在奶龙星球上空不断盘旋。
于是每 8 天，老大就能撑坏一个开裆裤；每 24 天，牢大就会坠机 3 次。
然而这样还不足以让 Aqz 满足。他强迫牢大去参加有着“魔王窟联赛”之称的 NOIP 联赛，并且承诺牢大 AK 后就放他离开。
于是，牢大就考上了“魔王窟联赛”。

### 看似简单的莫队没脾气面向hdkk！
这一句较为容易理解，在牢大第 7 次挑战 NOIP 联赛时，他遇到了一道看似简单的莫队题，而他完全不会莫队，于是再一次失败了。
而再一次面对给予他 7 次“有偿帮助”的联赛主席hdkk时，他也就没脾气、没有勇气提出要离开的要求了。

### 间谍剧场偷税漏税伟大腰间盘突出！
在牢大被迫参加 NOIP 模拟赛(魔王窟联赛) 的这 24 年之间，肘击星球与奶龙星球战火连天，双方都损失惨重，大部分的奶龙公民智力水平都产生了不同程度的下降。
于是，两个星球进行了谈判，决定进行间谍战以代替大型战争。
而这次计划被称为 $\lfloor间谍剧场\rceil$。
身为黑暗爆炸奶龙的 Aqz 同时也是一名优秀的间谍，所以他当仁不让，接下了这个任务，潜入了肘击星球。
他在肘击星球明面上贩卖新型食品，广受好评。
背地里却研发了能加速肘击的肘部护具，让肘击星球的人们能够不间断快速肘击别人。
肘击星球的人们时常互相肘击，并以肘击别人的速度来区分实力的强弱。
他的产品越卖越火，遍及了全球。
于是，在某一次新型产品推出时，Aqz 没加暂停键……
那天后的一年内，肘击星球内的人们再也无法停止高速肘击，许多人因日夜连续肘击而患上了腰间盘突出。
而我们的英雄，黑暗爆炸奶龙 Aqz，大赚了一笔后偷税漏税逃回了奶龙星球。
而这场战争自此也就以奶龙星球的胜利而告终。
我们的英雄 Aqz 顺利迎娶了奶龙公主，在奶龙星球的英雄碑上留下了自己的名字。
史称 **伟大腰间盘突出胜利** 。
*/