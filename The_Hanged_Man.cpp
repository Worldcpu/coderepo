#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=210,MM=5010;
int T,n,m,cntRev;
int a[MN],bval[MN];
int siz[MN],fa[MN],son[MN],top[MN],revv[MN];
vector<int> t[MN];
struct edge{int to,nxt;}E[MN*2];
int head[MN],edge_cnt;

struct Node{int v; long long cnt;}f[2][MN][MM],ans[MM];
Node operator +(const Node &x,const int &val){return {x.v+val,x.cnt};}
void mx(Node &x,Node y){if(x.v<y.v)x=y;else if(x.v==y.v)x.cnt+=y.cnt;}

void add(int u,int v){E[++edge_cnt]={v,head[u]};head[u]=edge_cnt;}
void dfs_son(int x,int fath){fa[x]=fath;siz[x]=1;son[x]=0;for(int i=head[x];i;i=E[i].nxt){int y=E[i].to;if(y==fath)continue;dfs_son(y,x);siz[x]+=siz[y];if(siz[y]>siz[son[x]])son[x]=y;}}
void dfs_chain(int x,int tp){top[x]=tp;revv[++cntRev]=x;for(int i=head[x];i;i=E[i].nxt){int y=E[i].to;if(y==fa[x]||y==son[x])continue;dfs_chain(y,y);}if(son[x])dfs_chain(son[x],tp);}
void clear_all(){edge_cnt=cntRev=0;memset(head,0,sizeof(head));for(int i=1;i<=n;i++){t[i].clear();}}

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>T;for(int cs=1;cs<=T;cs++){
        cin>>n>>m;
        clear_all();
        for(int i=1;i<=n;i++)cin>>a[i]>>bval[i];
        for(int i=1;i<n;i++){int u,v;cin>>u>>v;add(u,v);add(v,u);}
        dfs_son(1,0);dfs_chain(1,1);
        for(int i=1;i<=n;i++){int p=i;t[i].push_back(i);while(fa[top[p]]){p=fa[top[p]];t[i].push_back(p);}}
        for(int layer=0;layer<2;layer++)for(int s=0;s<MN;s++)for(int j=0;j<=m;j++)f[layer][s][j]={0,0};
        for(int i=0;i<=m;i++)ans[i]={0,0};
        f[0][0][0]={0,1};
        int now=1;
        for(int idx=1;idx<=n;idx++){
            int node=revv[idx],szCur=(int)t[node].size();
            int szPrev=(idx==1?1:(int)t[revv[idx-1]].size());
            for(int s=0;s<(1<<szCur);s++)for(int j=0;j<=m;j++)f[now][s][j]={0,0};
            vector<int> id(szPrev,-1);int fath=20;
            if(idx>1)for(int j=0;j<szPrev;j++){int p=t[revv[idx-1]][j];if(fa[node]==p)fath=j;id[j]=-1;for(int k=0;k<szCur;k++)if(p==t[node][k]){id[j]=k;break;}}
            for(int s=0;s<(idx==1?1:(1<<szPrev));s++){
                int S=0;if(idx>1)for(int j=0;j<szPrev;j++)if((s&(1<<j))&&id[j]!=-1)S|=1<<id[j];
                for(int j=0;j<=m;j++){
                    Node cur=f[now^1][s][j];if(!cur.cnt)continue;
                    mx(f[now][S][j],cur);
                    if((idx>1&&(s&(1<<fath)))||j+a[node]>m)continue;
                    mx(f[now][S|1][j+a[node]],cur+bval[node]);
                }
            }
            now^=1;
        }
        int finalLayer=now^1,szLast=(int)t[revv[n]].size();
        for(int s=0;s<(1<<szLast);s++)for(int j=1;j<=m;j++)mx(ans[j],f[finalLayer][s][j]);
        cout<<"Case "<<cs<<":\n";
        for(int i=1;i<=m;i++)cout<<ans[i].cnt<<(i==m?'\n':' ');
    }
    return 0;
}
