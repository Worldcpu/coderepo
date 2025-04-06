#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int t,n,ans,m;
const int MN=6125;
int pre[MN],sz[MN];
struct edge
{
    int u,v,w;
}e[MN];
bool cmp(edge x,edge y){
    return x.w<y.w;
}
int root(int x){
    if(pre[x]==x){
        return x;
    }else return pre[x]=root(pre[x]);
}
void initpre(){
    for(int i=1;i<=n;i++){
        pre[i]=i;
        sz[i]=1;
    }
}
void kru(){
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            pre[rv]=ru;
            ans+=(sz[ru]*sz[rv]-1)*(e[i].w+1);
            sz[ru]+=sz[rv];
        }
    }
}
int solve(){
    m=ans=0;
    cin>>n;
    initpre();
    for(int i=1;i<n;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
        m++;
    }
    sort(e+1,e+1+m,cmp);
    kru();
    return ans;
}
int main(){
    cin>>t;
    while (t--)
    {
        cout<<solve()<<'\n';
    }
    
    return 0;
}