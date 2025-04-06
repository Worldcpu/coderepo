#include<bits/stdc++.h>
#define ill __int128
using namespace std;
const int MN=1e5+15;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x,bool mode=1)//0为空格，1为换行
{
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    mode?putchar('\n'):putchar(' ');
}

ill lcm(ill x,ill y){
    return x/(__gcd(x,y))*y;
}

vector<int> adj[MN];
int in[MN],out[MN];

struct fenshu{
    ill a,b;
    fenshu(ill xa=0,ill xb=1){
        a=xa;
        b=xb;
    }
    fenshu operator+(const fenshu &x) const{
        fenshu ret;
        ill fm=lcm(b,x.b);
        ret.b=fm;
        ret.a=(a*(fm/b))+(x.a*(fm/x.b));
        ill fgcd=__gcd(ret.a,ret.b);
        ret.a/=fgcd;
        ret.b/=fgcd;
        return ret;
    }
    fenshu operator*(const fenshu &x) const{
        fenshu ret;
        ret.a=a*x.a;
        ret.b=b*x.b;
        ill fgcd=__gcd(ret.a,ret.b);
        ret.a/=fgcd;
        ret.b/=fgcd;
        return ret;
    }
}fs[MN];

int n,m;
vector<int> ans;

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!out[i]){
            ans.push_back(i);
        }
        if(!in[i]){
            fs[i].a=fs[i].b=1;
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        // int fa=fs[u].a,fb=fs[u].b;
        int siz=adj[u].size();
        fenshu chu(1,siz);
        fenshu plus=fs[u]*chu;
        for(auto v:adj[u]){
            in[v]--;
            fs[v]=fs[v]+plus;
            if(!in[v]) q.push(v);
        }
    }
}

int main(){
    read(n);
    read(m);
    for(int i=1;i<=n;i++){
        int d,v;
        read(d);
        while (d--)
        {
            read(v);
            adj[i].push_back(v);
            out[i]++;
            in[v]++;
        }
    }
    toposort();
    for(auto v:ans){
        write(fs[v].a,0);
        write(fs[v].b);
    }
    // for(int i=1;i<=n;i++){
    //     if(!out[i]) ans.push_back(i);
        
    // }
    return 0;
}