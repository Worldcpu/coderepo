#include<iostream>
#include<algorithm>
#define ls p<<1
#define rs p<<1|1
#define ll long long
using namespace std;
const int MN=1e5+15;
template<typename type>
void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
struct scanline
{
    ll l,r,h;
    int dat;
    bool operator<(const scanline&s)const{
        if(h==s.h) return dat>s.dat;
        return h<s.h;
    }
}line[MN<<1];
struct segtreee
{
    int l,r,c;
    ll sum,len;
    bool lc,rc;
//  sum: 被完全覆盖的次数；
//  len: 区间内被截的长度。
    // lc rc 表示左右端点是否被覆盖 c表示区间内线段条数
}t[MN<<2];

int n;
ll x1,y1,x2,y2,x[MN<<1];

void pushup(int p){
    int l=t[p].l,r=t[p].r;
    if(t[p].sum){
        t[p].len=x[r+1]-x[l];
        t[p].lc=t[p].rc=1;
        t[p].c=1;
    }else{
        t[p].len=t[ls].len+t[rs].len;
        t[p].lc=t[ls].lc,t[p].rc=t[rs].rc;
        t[p].c=t[ls].c+t[rs].c;
//      如果左儿子左端点被覆盖，那么自己的左端点也肯定被覆盖；右儿子同理
        if(t[ls].rc&&t[rs].lc){
            t[p].c-=1;
//      如果左儿子右端点和右儿子左端点都被覆盖，
//      那么中间就是连续的一段，所以要 -= 1
        }
    }
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    t[p].lc=t[p].rc=t[p].sum=t[p].len=t[p].c=0;
    if(l==r) return;
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

void edittree(int p,int fl,int fr,int c){
    int l=t[p].l,r=t[p].r;
    if(x[l]>=fr||x[r+1]<=fl) return;
    if(x[l]>=fl&&x[r+1]<=fr){
        t[p].sum+=c;
        pushup(p);
        return;
    }
    edittree(ls,fl,fr,c);
    edittree(rs,fl,fr,c);
    pushup(p);
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        cin>>x1>>y1>>x2>>y2;
        line[i*2-1]={x1,x2,y1,1};
        line[i*2]={x1,x2,y2,-1};
        x[i*2-1]=x1,x[i*2]=x2;
    }
    n<<=1;
    sort(line+1,line+1+n);
    sort(x+1,x+1+n);
    int tot=unique(x+1,x+1+n)-x-1;
    build(1,1,tot-1);
    ll ans=0,pre=0;
    for(int i=1;i<n;i++){
        edittree(1,line[i].l,line[i].r,line[i].dat);
        ans+=abs(pre-t[1].len);
        pre=t[1].len;
        ans+=2*t[1].c*(line[i+1].h-line[i].h);
    }
    ans+=line[n].r-line[n].l;
    cout<<ans;
    return 0;
}