#include <bits/stdc++.h>
using namespace std;
namespace IO {char Is[(1<<21)+10],Os[(1<<21)+10];int Ipt,Opt;char gc() {if(Ipt==1<<21)Ipt=0;if(!Ipt)Is[fread(Is,1,1<<21,stdin)]=0;return Is[Ipt++];}void flush() {fwrite(Os,1,Opt,stdout);Opt=0;}void pc(char x) {if(Opt==1<<21)flush();Os[Opt++]=x;}int read() {int x=0,f=1;char ch=gc();while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=gc();}while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+ch-'0',ch=gc();return x*f;}int t[100];void write(int x) {if(x<0)pc('-'),x=-x;if(!x) {pc('0');return;}int len=0;while(x)t[++len]=x%10,x/=10;for(int i=len;i>=1;--i)pc(t[i]+48);}}
using namespace IO;

vector<int>a[25];
int ordered[25];

int main()
{
    int n,m,q;
    n=read(),m=read(),q=read();

    for(int i=1;i<=m;i++)
    {
        a[i].resize(n);
        for(int j=0;j<n;j++)a[i][j]=read();
    }
    int t,x,y;
    while(q--)
    {
        t=read(),x=read(),y=read();
        if(t==1)
        {
            vector<int>tmp(2*n);
            if(!ordered[x])sort(a[x].begin(),a[x].end()),ordered[x]=1;
            if(!ordered[y])sort(a[y].begin(),a[y].end()),ordered[y]=1;
            if(a[x][n-1]<=a[y][0])continue;
            else if(a[y][n-1]<=a[x][0])a[x].swap(a[y]);//这里
            else
            {
                merge(a[x].begin(),a[x].end(),a[y].begin(),a[y].end(),tmp.begin());
                for(int i=0;i<n;i++)a[x][i]=tmp[i];
                for(int i=n;i<2*n;i++)a[y][i-n]=tmp[i];
            }
            
        }
        else write(a[x][y-1]),pc('\n');
    }
    flush();

    return 0;
}
