#include<bits/stdc++.h>
#include"../../testlib.h"
using namespace std;
int n,cx,cy,mx[500001],my[500001],color[500001],res[5];
vector<int>ox[500001],oy[500001];
map<pair<int,int>,int>mo;
bool vis[2000001];
const int dx[]={0,-1,0,1},dy[]={-1,0,1,0};
struct obstacle
{
    int x,y;
    bool dir;
}o[500001];
int encode(int x,bool type)
{
    if(type)return lower_bound(my+1,my+cy+1,x)-my;
    return lower_bound(mx+1,mx+cx+1,x)-mx;
}
void search(int s)
{
    if(vis[s])return;
    vis[s]=true;
    memset(res,0,sizeof(res));
    int pos=(s>>2)+1,d=s&3;
    do
    {
        ++res[color[pos]];
        int x=encode(o[pos].x,false),y=encode(o[pos].y,true),p;
        vis[((pos-1)<<2)+d]=true;
        if(d&1)
        {
            p=lower_bound(ox[x].begin(),ox[x].end(),y)-ox[x].begin()+(d==1?1:-1);
            if(p==-1||p==ox[x].size())return;
            pos=mo[make_pair(x,ox[x][p])];
            d=((d==1)==bool(o[pos].dir))?2:0;
        }
        else
        {
            p=lower_bound(oy[y].begin(),oy[y].end(),x)-oy[y].begin()+(d==2?1:-1);
            if(p==-1||p==oy[y].size())return;
            pos=mo[make_pair(oy[y][p],y)];
            d=(bool(d)==bool(o[pos].dir))?1:3;
        }
    }while(!vis[((pos-1)<<2)+d]);
    if(pos!=s)return;
    for(int i=1;i<=4;++i)
    {
        if(res[i]&1)quitf(_wa,"Number of colors should be even");
        if(i>1&&res[i]!=res[i-1])quitf(_wa,"Number of colors isn't equivalent");
    }
}
int main(int argc,char *argv[])
{
    registerTestlibCmd(argc,argv);
    quitif(ans.readInt()==-1,~(color[1]=ouf.readInt(-1,4))?_wa:_ok,"No existence");
    if(!color[1])quitf(_fail,"Integer 0 violates the range [1, 4]");
    n=inf.readInt();
    for(int i=2;i<=n;++i)
    {
        ouf.readSpace();
        color[i]=ouf.readInt(1,4);
    }
    if(!ouf.seekEof())quitf(_pe,"Extra content found");
    for(int i=1;i<=n;++i)
    {
        mx[++cx]=o[i].x=inf.readInt();
        my[++cy]=o[i].y=inf.readInt();
        o[i].dir=(inf.readToken()=="/");
    }
    sort(mx+1,mx+cx+1);
    sort(my+1,my+cy+1);
    cx=unique(mx+1,mx+cx+1)-mx-1;
    cy=unique(my+1,my+cy+1)-my-1;
    for(int i=1;i<=n;++i)
    {
        int nx=encode(o[i].x,false),ny=encode(o[i].y,true);
        ox[nx].push_back(ny);
        oy[ny].push_back(nx);
        mo[make_pair(nx,ny)]=i;
    }
    for(int i=1;i<=n;++i)
    {
        sort(ox[i].begin(),ox[i].end());
        sort(oy[i].begin(),oy[i].end());
    }
    for(int i=0;i<(n<<2);++i)search(i);
    quitf(_ok,"%d obstacle(s)",n);
    return 0;
}