#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1500;
int phi[MN],p[MN],cnt;
bool vis[MN];
void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) p[++cnt]=i,phi[i]=i-1;//质数只有自身与自己不互质

        for(int j=1;p[j]&&i*p[j]<=n;j++)

        {

            vis[i*p[j]]=1;

            if(!(i%p[j]))

            {

                phi[i*p[j]]=phi[i]*p[j];

                //这里是平方因子了，不要减1

                break;

            }

            else phi[i*p[j]]=phi[i]*(p[j]-1);//第一次出现因子，乘p-1

        }

    }
}

int main(){
    int n;
    cin>>n;
    if(n==1){
        cout<<0;
        return 0;
    }
    euler(n+1);
    int ans=0;
    for(int i=1;i<n;i++) ans+=phi[i];
    cout<<(ans<<1|1);
}
