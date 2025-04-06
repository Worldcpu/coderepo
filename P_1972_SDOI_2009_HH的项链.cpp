#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int MN=1e6+15;
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

struct ops{
    //type:0加点 1查询（加），2查询（减）
    int type,x,y,id;
}op[MN];

int n,tot,m;
int a[MN],t[MN],pre[MN],lst[MN],ans[MN];
void add(int x,int k){
    x++;
    while(x<=n){
        t[x]+=k;
        x+=lowbit(x);
    }
}

int query(int x){
    x++;
    int ret=0;
    while (x)
    {
        /* code */
        ret+=t[x];
        x-=lowbit(x);
    }
    return ret;
}
bool cmp(ops x,ops y){
    if(x.x==y.x) return x.type<y.type;
    return x.x<y.x;
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        pre[i]=lst[a[i]];
        lst[a[i]]=i;
        op[++tot]={0,i,pre[i],i};
    }
    read(m);
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        op[++tot]={1,r,l-1,i};
        op[++tot]={2,l-1,l-1,i};
    }
    sort(op+1,op+1+tot,cmp);
    for(int i=1;i<=tot;i++){
        if(op[i].type==0){
            add(op[i].y,1);
        }else if(op[i].type==1){
            ans[op[i].id]+=query(op[i].y);
        }else ans[op[i].id]-=query(op[i].y);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}