#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3005,INF=0x3f3f3f3f;
struct Node{
    int x,y;
};
int n,m,Q,ans,x[MN],y[MN],K,dis[MN][MN],own[MN][MN];
int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
bool mp[MN][MN];
queue<Node> q;

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

void bfs(){
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nx=f.x+fx[i],ny=f.y+fy[i];
            if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]) continue;
            if(dis[nx][ny]>dis[f.x][f.y]+1&&dis[nx][ny]==INF){
                dis[nx][ny]=dis[f.x][f.y]+1;
                own[nx][ny]=own[f.x][f.y];
                q.push({nx,ny});
            }else if(dis[nx][ny]==dis[f.x][f.y]+1){
                if(own[nx][ny]!=own[f.x][f.y]){
                    own[nx][ny]=-1;
                }  
            }
        }
    }
}

int main(){
    memset(dis,0x3f,sizeof(dis));
    read(n,m,K);
    for(int i=1;i<=K;i++){
        read(x[i],y[i]);
    }
    for(int i=1;i<=K;i++){
            dis[x[i]][y[i]]=0;
            own[x[i]][y[i]]=i;
        q.push({x[i],y[i]});
    }
    read(Q);
    while(Q--){
        int x,y;
        read(x,y);
        mp[x][y]=1;
    }
    bfs();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]||dis[i][j]>=INF) continue;
            if(own[i][j]==-1) ans++;
        }
    }
    put(ans);
    return 0;
}