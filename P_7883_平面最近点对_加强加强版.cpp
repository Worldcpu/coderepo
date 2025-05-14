#include<bits/stdc++.h>
#define ll long long
#define PF(x) (1ll*x*x)
#define Dis(x,y) (ll)(PF(a[x].x-a[y].x)+PF(a[x].y-a[y].y))
#define Pf(x) (x*x)
using namespace std;
constexpr int MN=4e5+15;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;
struct Node{
    int x,y;
}a[MN];
int lc[MN],rc[MN],lx[MN],rx[MN],ly[MN],ry[MN],nowt,id[MN],n,rt;
ll ans;
double px,py,fx,fy;

using namespace std;
namespace fastr
{
    namespace IO
    {
        #define SIZE (1<<20)
        char in[SIZE],out[SIZE],*p1=in,*p2=in,*p3=out;
        #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,SIZE,stdin),p1==p2)?EOF:*p1++)
        #define flush() (fwrite(p3=out,1,SIZE,stdout))
        #define putchar(ch) (p3==out+SIZE&&flush(),*p3++=(ch))
        class Flush{public:~Flush(){flush();}}_;
        template<typename type>
        inline void read(type &x)
        {
            x=0;bool flag(0);char ch=getchar();
            while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
            while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
            flag?x=-x:0;
        }
        template<typename type>
        inline void write(type x,bool flag=1)
        {
            x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
            do Stack[++top]=x%10,x/=10;while(x);
            while(top) putchar(Stack[top--]|48);
            flag?putchar('\n'):putchar(' ');
        }
        #undef SIZE
        #undef getchar
        #undef putchar
        #undef flush
    }
}using namespace fastr::IO;

bool cmpx(int x,int y){
    return a[x].x<a[y].x;
}

bool cmpy(int x,int y){
    return a[x].y<a[y].y;
}


void pushup(int x){
    lx[x]=rx[x]=a[x].x;
    ly[x]=ry[x]=a[x].y;
    if(lc[x]){
        lx[x]=min(lx[x],lx[lc[x]]);
        rx[x]=max(rx[x],rx[lc[x]]);
        ly[x]=min(ly[x],ly[lc[x]]);
        ry[x]=max(ry[x],ry[lc[x]]);
    }
    if(rc[x]){
        lx[x]=min(lx[x],lx[rc[x]]);
        rx[x]=max(rx[x],rx[rc[x]]);
        ly[x]=min(ly[x],ly[rc[x]]);
        ry[x]=max(ry[x],ry[rc[x]]);
    }
}

int optbuild(int l,int r){
    if(r<l) return 0;
    int mid=l+((r-l)>>1),x;
    px=fx=py=fy=0;
    for(int i=l;i<=r;i++){
        px+=a[id[i]].x;
        py+=a[id[i]].y;
    }
    px/=(r-l+1),py/=(r-l+1);
    for(int i=l;i<=r;i++){
        fx+=Pf(px-a[id[i]].x);
        fy+=Pf(py-a[id[i]].y);
    }
    if(fx>fy) nth_element(id+l,id+mid,id+r+1,cmpx);
    else nth_element(id+l,id+mid,id+r+1,cmpy);
    x=id[mid];
    lc[x]=optbuild(l,mid-1);
    rc[x]=optbuild(mid+1,r);
    pushup(x);
    return x;
}

ll fac(int x){
    if(!x) return INF+114;
    ll ret=0;
    if(lx[x]>a[nowt].x) ret+=PF(lx[x]-a[nowt].x);
    if(rx[x]<a[nowt].x) ret+=PF(a[nowt].x-rx[x]);
    if(ly[x]>a[nowt].y) ret+=PF(ly[x]-a[nowt].y);
    if(ry[x]<a[nowt].y) ret+=PF(a[nowt].y-ry[x]);
    return ret;
}

void query(int x){
    if(x!=nowt) ans=min(ans,(PF(a[x].x-a[nowt].x)+PF(a[x].y-a[nowt].y)));
    ll fl=fac(lc[x]),fr=fac(rc[x]);
    if(fl<fr){
        if(fl<ans) query(lc[x]);
        if(fr<ans) query(rc[x]);
    }else{
        if(fr<ans) query(rc[x]);
        if(fl<ans) query(lc[x]);
    }
}

int main(){
    read(n);
    ans=INF;
    for(int i=1;i<=n;i++){
        //cin>>a[i].x>>a[i].y;
        read(a[i].x);
        read(a[i].y);
        id[i]=i;
    }
    rt=optbuild(1,n);
    for(int i=1;i<=n;++i){
        //if (clock() * 1.0 / CLOCKS_PER_SEC >= 0.345) break;
        nowt=id[i];
        query(rt);
    }
    write(ans);
    // flush();
    return 0;
}