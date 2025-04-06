#include <bits/stdc++.h>
#define ll long long
#define lint __int128
using namespace std;
constexpr int MN = 1e5 + 15;
lint n, m;
ll phi[MN + 15];
vector<bool> vis(MN + 15);
vector<ll> prm;

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

void getphi()
{
    vis[0] = vis[1] = 1;
    phi[1] = 1;
    for (ll i = 2; i <= MN; i++)
    {
        if (!vis[i])
        {
            prm.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prm)
        {
            if (p * i > MN)
                break;
            vis[p * i] = 1;
            if (i % p == 0)
            {
                phi[i * p] = phi[i] * p;
                break;
            }
            else
                phi[i * p] = phi[i] * (p - 1);
        }
    }
}

int main()
{
    read(n);
    m=n;
    getphi();
    lint ans=0;
    for(lint i=1;i<=n;i++){
        ans+=phi[i]*(n/i)*(n/i);
    }
    write(ans);
    return 0;
}