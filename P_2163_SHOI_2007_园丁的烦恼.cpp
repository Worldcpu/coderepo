#include <bits/stdc++.h>
using namespace std;
const int MN = 2e5 + 15, MP = 1e7 + 15;
struct node
{
    int x, y, id;
} a[MN], b[MN];
int ans[MN];
int t[MP],n,m,cnt;
int lowbit(int x)
{
    return x & -x;
}

void add(int x,int k){
    x++;
    while (x<=MP)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}

int query(int x){
    x++;
    int ret=0;
    while (x)
    {
        ret+=t[x];
        x-=lowbit(x);
    }
    return ret;
}

bool cmp(node x,node y){
    return x.x<y.x;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }

    for(int i=1;i<=m;i++){
        int xa,xb,ya,yb;
        cin>>xa>>ya>>xb>>yb;
        b[++cnt]={xb,yb,cnt};
        b[++cnt]={xa-1,yb,cnt};
        b[++cnt]={xb,ya-1,cnt};
        b[++cnt]={xa-1,ya-1,cnt};
    }

    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+cnt,cmp);

    for(int i=1,p=1;i<=cnt;i++){
        while (a[p].x<=b[i].x&&p<=n)
        {
            add(a[p].y,1);
            p++;
        }
        ans[b[i].id]+=query(b[i].y);
    }
    for(int i=1;i<=cnt;i+=4){
        cout<<ans[i]+ans[i+3]-ans[i+1]-ans[i+2]<<'\n';
    }
    return 0;
}